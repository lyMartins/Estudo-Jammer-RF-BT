# ESP32-BlueJammer — Guia Didático de Reverse Engineering

> **Para:** Obsidian | Estudo pessoal
> **Data:** 2026-05-04
> **Nível:** Intermediário — conhecimentos básicos de electrónica e programação

---

## O que vais aprender

- Como ler o firmware de um ESP32 sem alterar nada
- O que é flash encryption e como verificar se está ativa
- Como funciona a arquitetura de um firmware ESP-IDF/Arduino
- Como usar o Ghidra para descompilar código Xtensa (ESP32)
- Como reconstruir código C++ a partir de pseudo-C descompilado
- Como funciona tecnicamente um jammer 2.4GHz

---

## Índice

1. [[#1. Conceitos Base]]
2. [[#2. O Hardware]]
3. [[#3. Passo 1 — Ler o Flash]]
4. [[#4. Passo 2 — Verificar Criptografia]]
5. [[#5. Passo 3 — Mapear as Partições]]
6. [[#6. Passo 4 — Extrair e Analisar Strings]]
7. [[#7. Passo 5 — Descompilar com Ghidra]]
8. [[#8. Passo 6 — Reconstruir o Código]]
9. [[#9. Como Funciona o Jamming]]
10. [[#10. Estrutura do Projeto Final]]
11. [[#11. Compilar e Flashar]]

---

## 1. Conceitos Base

### O que é firmware?

Firmware é o programa que corre directamente no microcontrolador. No ESP32, fica guardado numa memória flash externa (chip separado). Quando ligas o dispositivo, o ESP32 lê esse programa e executa-o.

### O que é reverse engineering de firmware?

É o processo de ler o firmware compilado (binário) e tentar perceber o que faz, sem ter o código fonte. Como receber um bolo cozido e tentar descobrir a receita.

### Por que é difícil?

Quando o compilador transforma código C++ em binário, perde-se muita informação:
- Nomes de funções e variáveis (se o binário for "stripped")
- Estruturas de classes C++
- Comentários
- Lógica de alto nível

O que sobra são instruções máquina (assembly Xtensa no caso do ESP32).

### O que é o Xtensa?

É a arquitectura de CPU usada pelo ESP32. É diferente do x86 (PC) ou ARM (telemóveis). Por isso precisamos de ferramentas específicas para o descompilar.

---

## 2. O Hardware

```
┌─────────────────────────────────────────────┐
│              ESP32-BlueJammer               │
│                                             │
│  ┌──────────┐    ┌──────────────────────┐   │
│  │  nRF24   │    │                      │   │
│  │  HSPI    │◄──►│      ESP32           │   │
│  └──────────┘    │   D0WD-V3 rev3.1     │   │
│                  │   Dual Core 240MHz   │   │
│  ┌──────────┐    │   4MB Flash          │   │
│  │  nRF24   │◄──►│                      │   │
│  │  VSPI    │    └──────────────────────┘   │
│  └──────────┘         │         │           │
│                    ┌──┴──┐   ┌──┴──┐        │
│                    │OLED │   │ ADC │        │
│                    │SSD  │   │ Bat │        │
│                    │1306 │   └─────┘        │
│                    └─────┘                  │
└─────────────────────────────────────────────┘
```

### Porquê dois módulos nRF24L01+?

Cada nRF24L01+ só consegue estar num canal de cada vez. Com dois módulos, o firmware consegue varrer os canais a velocidade dobrada — um vai de baixo para cima, o outro de cima para baixo, cobrindo o espectro muito mais rápido.

### Porquê o ESP32 E os nRF24?

O ESP32 tem WiFi e Bluetooth embutidos. Mas os nRF24L01+ conseguem cobrir toda a banda 2.4GHz de forma mais directa (sem stack de protocolo). A combinação dos dois garante cobertura máxima:

- **nRF24L01+** → BT, BLE, RC, WiFi (via flooding raw)
- **ESP32 interno** → WiFi e BT com stacks completas

---

## 3. Passo 1 — Ler o Flash

### Ferramentas necessárias

- `esptool.py` (já vem com PlatformIO)
- Cabo USB com dados (não só carregamento!)
- O ESP32 ligado ao PC via USB

### Verificar que o dispositivo é detectado

```bash
ls /dev/ttyUSB*
# Deve aparecer /dev/ttyUSB0 ou similar
```

### Identificar o chip

```bash
python3 ~/.platformio/packages/tool-esptoolpy/esptool.py \
--port /dev/ttyUSB0 chip_id
```

Output esperado:
```
Chip is ESP32-D0WD-V3 (revision v3.1)
Features: WiFi, BT, Dual Core, 240MHz
MAC: 3c:8a:1f:a4:85:60
Detected flash size: 4MB
```

### Ler o flash completo

```bash
python3 ~/.platformio/packages/tool-esptoolpy/esptool.py \
--port /dev/ttyUSB0 \
read_flash 0x0 0x400000 flash_dump.bin
```

> 💡 `0x400000` = 4MB em hexadecimal. Este comando **só lê** — não modifica nada no ESP32.

Demora ~3 minutos. No final tens um ficheiro `flash_dump.bin` com uma cópia exacta da memória flash.

---

## 4. Passo 2 — Verificar Criptografia

O ESP32 tem uma funcionalidade chamada **Flash Encryption** que cifra o conteúdo da flash com uma chave AES guardada nos eFuses (memória permanente). Se estiver activa, o dump que fizemos seria ilegível.

### Verificar os eFuses

```bash
python3 ~/.platformio/packages/tool-esptoolpy/espefuse.py \
--port /dev/ttyUSB0 summary
```

### O que procurar

```
FLASH_CRYPT_CNT = 0   ← Flash Encryption DESACTIVADA (bits = 0, número par)
BLOCK1          = 00 00 00 00 ... ← sem chave gravada
ABS_DONE_0      = False  ← Secure Boot v1 desactivado
ABS_DONE_1      = False  ← Secure Boot v2 desactivado
```

> 💡 `FLASH_CRYPT_CNT` funciona por número de bits: se o número de bits a 1 for **ímpar**, a criptografia está **activa**. Valor 0 = sem bits = número par = **desactivada**.

### Como confirmar que não está cifrado

Se conseguires ler strings de texto no dump, não está cifrado:

```bash
strings flash_dump.bin | grep "State\|nRF\|WiFi\|Bluetooth"
```

Se aparecerem strings legíveis → **não cifrado** ✅

---

## 5. Passo 3 — Mapear as Partições

O ESP32 organiza a flash em partições, como pastas num disco. O `binwalk` analisa o binário e identifica cada secção.

```bash
binwalk flash_dump.bin
```

### Resultado e significado

| Partição | Offset | Tamanho | O que é |
|---|---|---|---|
| `bootloader` | 0x1000 | ~28KB | Primeiro código que corre ao ligar. Inicializa o hardware e carrega a app. |
| `partition table` | 0x8000 | 3KB | Mapa de onde fica cada partição (como uma tabela de índices). |
| `nvs` | 0x9000 | 20KB | Non-Volatile Storage — guarda configurações persistentes (WiFi SSIDs, etc.). Estava vazia. |
| `app0` | 0x10000 | 1.3MB | **O firmware activo** — o que nos interessa. |
| `app1` | 0x150000 | 1.3MB | Slot de OTA (Over-The-Air update). Vazio — nunca foi actualizado via OTA. |
| `spiffs` | 0x290000 | 1.4MB | Sistema de ficheiros para guardar ficheiros. Vazio. |
| `coredump` | 0x3F0000 | 64KB | Guarda dumps de crash. Vazio. |

### Extrair as partições com `dd`

```bash
# Firmware principal (app0)
dd if=flash_dump.bin of=extracted/app0.bin \
bs=1 skip=65536 count=1310720
#         ↑ 0x10000  ↑ 0x140000 bytes
```

> 💡 `dd` é uma ferramenta Unix para copiar bytes. `skip` é o offset de início, `count` é o número de bytes a copiar.

---

## 6. Passo 4 — Extrair e Analisar Strings

A forma mais rápida de perceber o que um firmware faz é ler as strings de texto que contém. Mensagens de log, nomes de funções, URLs — tudo isso pode estar em texto limpo.

```bash
strings extracted/app0.bin | grep -E "State|nRF|Firmware|voltage|OLED"
```

### O que encontrámos

```
Firmware : Official-Combo-Channel (BT-BLE-WiFi-RC)
https://github.com/EmenstaNougat/ESP32-BlueJammer
!Educational purposes only!
State 0: Idle & Status
State 1: Bluetooth
State 2: Bluetooth Low Energy
State 3: WiFi
State 4: RC
Hardware Serial Peripheral Interface started !!! HSPI nRF24 module initialized SUCCESSFULLY!
Variable Serial Peripheral Interface started !!! VSPI nRF24 module initialized SUCCESSFULLY!
[BatStat] Initial voltage: %.3fV  (%d%%)  source: %s
Initialized voltage readout...
SSD1306 allocation failed
```

Só com isto já sabemos:
- É o BlueJammer do GitHub
- Tem 4 modos (BT, BLE, WiFi, RC)
- Usa dois nRF24 (HSPI e VSPI)
- Tem OLED SSD1306
- Tem leitura de bateria
- O código fonte não é público (closed source)

---

## 7. Passo 5 — Descompilar com Ghidra

### O que é o Ghidra?

Ferramenta open-source da NSA para análise de binários. Consegue transformar código máquina em pseudo-C legível — não é o código original, mas é muito mais fácil de ler que assembly.

### Porquê precisamos de um plugin?

O Ghidra não suporta Xtensa (arquitectura do ESP32) por defeito. Precisamos do plugin `ghidra-xtensa`.

### Instalar o plugin (resumo)

```bash
# 1. Clonar o plugin
git clone https://github.com/Ebiroll/ghidra-xtensa

# 2. Compilar (requer Java 17 e Gradle)
cd ghidra-xtensa
JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64 \
GHIDRA_INSTALL_DIR=/usr/share/ghidra \
GHIDRA_DIR=/usr/share/ghidra \
./gradlew buildExtension

# 3. Compilar o ficheiro de linguagem SLEIGH
/usr/share/ghidra/support/sleigh \
/tmp/xtensa_lang/xtensa.slaspec

# 4. Instalar (requer sudo)
sudo cp -r dist/ghidra-xtensa /usr/share/ghidra/Ghidra/Processors/
sudo cp /tmp/xtensa_lang/xtensa.sla \
/usr/share/ghidra/Ghidra/Processors/ghidra-xtensa/data/languages/
sudo chmod 644 \
/usr/share/ghidra/Ghidra/Processors/ghidra-xtensa/data/languages/xtensa.sla
```

### Descompilar em modo headless (sem GUI)

```bash
JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64 \
/usr/share/ghidra/support/analyzeHeadless \
~/ghidra_project ESP32_BlueJammer \
-import app0.bin \
-processor Xtensa:LE:32:default \
-postScript decompile.py \
-overwrite
```

**Resultado:** 3838 funções descompiladas em pseudo-C.

### Por que o output é C e não C++?

O firmware foi escrito em **C++** (Arduino). Mas o compilador transforma C++ em instruções máquina, destruindo as abstrações:

| C++ original | O que o compilador gera | O que o Ghidra vê |
|---|---|---|
| `radio.setChannel(5)` | `call 0x400d2f4c` (endereço da vtable) | `(*_DAT_fff60198)(iVar4, 5)` |
| `class RF24 { ... }` | struct de dados + funções separadas | `FUN_000571f8(ptr, param)` |
| `Serial.println("x")` | `call uart_write_bytes` | `FUN_000d6628(...)` |

O Ghidra só consegue gerar pseudo-C porque não tem como saber que aquelas funções eram métodos de uma classe.

---

## 8. Passo 6 — Reconstruir o Código

### Estratégia

1. Identificar as funções importantes pelos nomes das strings que usam
2. Perceber a lógica de cada função
3. Reescrever em C++ limpo com as bibliotecas Arduino correctas

### Funções identificadas

| Endereço (Ghidra) | Nome reconstruído | O que faz |
|---|---|---|
| `0x22a90` | `cycleMode()` | Incrementa modo: 1→2→3→4→1 |
| `0x22ab4` | `ledBlink_update()` | Pisca LED N vezes (N = modo) |
| `0x22b24` | `setMode_Bluetooth()` | Activa modo BT, actualiza OLED |
| `0x22b6c` | `setMode_BLE()` | Activa modo BLE, actualiza OLED |
| `0x22bb4` | `setMode_WiFi()` | Activa modo WiFi, actualiza OLED |
| `0x22bfc` | `setMode_RC()` | Activa modo RC, actualiza OLED |
| `0x22c70` | `idleScreen()` | Ecrã idle: logo + bateria + status |
| `0x2309c` | `loop()` | Loop principal + gestão do botão |
| `0x23208` | `battery_getRaw()` | Média de 16 leituras ADC |
| `0x23254` | `battery_getVoltage()` | ADC → tensão (com divisor de tensão) |

### Como identificar funções sem nomes

Exemplo: a função `0x22b24` tem este padrão no pseudo-C do Ghidra:

```c
int FUN_00022b24(void) {
	if (*_DAT_fff6010c != 1) {
		*_DAT_fff6010c = 1;          // ← guarda o valor 1 (= BT mode)
		FUN_00026694(..., _DAT_fff60110);  // ← chama função com dados
		...
		*_DAT_fff60108 = 1;          // ← outro indicador com valor 1
	}
	FUN_00022ab4(...);  // ← chama ledBlink
	return 1;           // ← retorna 1 (= BT mode)
}
```

As funções `0x22b6c`, `0x22bb4`, `0x22bfc` têm exactamente o mesmo padrão mas com valores 2, 3, 4. Conclusão: estas 4 funções são os 4 setters de modo.

---

## 9. Como Funciona o Jamming

### O espectro 2.4GHz

```
2.400 GHz ←────────────────────────────────→ 2.525 GHz
│         │              │         │
BLE       BT           WiFi        RC
40ch       79ch          14ch      125ch
```

Todos estes protocolos partilham o mesmo espectro. Se o espaço estiver saturado com ruído, nenhum consegue comunicar.

### Como o nRF24L01+ gera ruído

O nRF24L01+ é um transceiver de 2.4GHz com 125 canais possíveis (canal 0 = 2.400GHz, canal 124 = 2.524GHz). Para saturar um canal:

```cpp
radio.setChannel(ch);          // seleccionar canal
radio.write(garbage, 32);      // enviar 32 bytes de lixo
```

Fazendo isto muito rapidamente em loop, o canal fica saturado e dispositivos legítimos não conseguem comunicar.

### Porquê dois rádios?

Um rádio só consegue estar num canal de cada vez. Com dois:

```
Radio 1: ch0 → ch1 → ch2 → ch3 → ... → ch79
Radio 2: ch79 → ch78 → ch77 → ...→ ch0
↑ começa do fim
```

Os dois cobrem o espectro em direcções opostas, duplicando a taxa de cobertura.

### Diferença entre os modos

| Modo | Canais | Estratégia |
|---|---|---|
| **Bluetooth** | 79 canais, 1MHz cada | Varre todos os canais BT em sequência |
| **BLE** | 40 canais, 2MHz cada | Inclui os 3 canais de advertising (37, 38, 39) |
| **WiFi** | 14 canais mas ~22MHz cada | Varre toda a sub-banda para cobrir canais sobrepostos |
| **RC** | 125 canais | Cobertura total 2.400–2.525GHz |

---

## 10. Estrutura do Projeto Final

```
versions/
├── c_decompiled/
│   └── bluejammer_ghidra.c      ← Pseudo-C do Ghidra (output directo)
│                                   Não compilável, mas fiel ao binário
└── cpp_arduino/
├── platformio.ini           ← Configuração PlatformIO
├── include/
│   └── config.h             ← Pinout, constantes, configuração
└── src/
└── main.cpp             ← Código C++ completo e compilável
```

### Diferenças entre as duas versões

| Aspecto | `c_decompiled` | `cpp_arduino` |
|---|---|---|
| Origem | Ghidra (automático) | Escrita à mão baseada no reversing |
| Fidelidade ao original | Alta (é o binário) | Alta (baseada na análise) |
| Compilável | Não | Sim |
| Legibilidade | Baixa | Alta |
| Nomes de funções | `FUN_00022b24` | `setMode_Bluetooth()` |
| Classes C++ | Não (tudo achatado em C) | Sim (`RF24`, `Button`, etc.) |

---

## 11. Compilar e Flashar

### Pré-requisitos

```bash
# PlatformIO já instalado em ~/.platformio
# Verificar:
~/.platformio/penv/bin/platformio --version
```

### Compilar

```bash
cd versions/cpp_arduino
~/.platformio/penv/bin/platformio run
```

### Flashar (com ESP32 ligado)

```bash
~/.platformio/penv/bin/platformio run --target upload --upload-port /dev/ttyUSB0
```

### Monitorizar output serial

```bash
~/.platformio/penv/bin/platformio device monitor --port /dev/ttyUSB0 --baud 115200
```

Output esperado ao ligar:
```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Firmware : Official-Combo-Channel (BT-BLE-WiFi-RC)
https://github.com/EmenstaNougat/ESP32-BlueJammer
!Educational purposes only!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Initialized voltage readout...
[BatStat] Initial voltage: 3.842V  (70%)
HSPI nRF24 initialized SUCCESSFULLY!
VSPI nRF24 initialized SUCCESSFULLY!
State 1: Bluetooth
```

---

## Resumo do Processo

```
ESP32 físico
│
▼ esptool.py read_flash
flash_dump.bin (4MB)
│
├─▶ binwalk → mapa de partições
├─▶ strings → contexto do firmware
└─▶ dd → app0.bin (firmware activo)
│
▼ Ghidra + plugin Xtensa
pseudo-C (3838 funções)
│
├─▶ c_decompiled/  ← versão fiel (não compilável)
└─▶ análise manual → reconstrução
│
▼
cpp_arduino/ ← versão C++ compilável
```

---

## Referências

- [Repositório original](https://github.com/EmenstaNougat/ESP32-BlueJammer)
- [esptool.py](https://github.com/espressif/esptool)
- [ghidra-xtensa plugin](https://github.com/Ebiroll/ghidra-xtensa)
- [Biblioteca RF24](https://github.com/nRF24/RF24)
- [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [nRF24L01+ Datasheet](https://www.nordicsemi.com/products/nrf24l01)

---

*Documento gerado a 2026-05-04 — para uso educativo pessoal*
