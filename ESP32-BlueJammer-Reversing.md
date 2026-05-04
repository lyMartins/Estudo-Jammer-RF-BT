# ESP32-BlueJammer — Reverse Engineering

> **Data:** 2026-05-04
> **Hardware:** ESP32-D0WD-V3 rev3.1 via `/dev/ttyUSB0`
> **Firmware:** Official-Combo-Channel (BT-BLE-WiFi-RC)
> **Fonte:** https://github.com/EmenstaNougat/ESP32-BlueJammer (closed source)

---

## 1. Contexto

O ESP32-BlueJammer é um dispositivo de interferência 2.4GHz criado por **@emensta (EmenstaNougat)**. O código fonte não é público — o autor distribui apenas os binários compilados. O objetivo deste processo foi extrair e compreender o firmware para fins educativos.

> ⚠️ Jamming de RF é ilegal na maioria das jurisdições. Este documento é estritamente educativo.

---

## 2. Hardware Identificado

| Componente | Detalhe |
|---|---|
| MCU | ESP32-D0WD-V3, rev3.1, Dual Core, 240MHz |
| Flash | 4MB (Manufacturer: 0x68, Device: 0x4016) |
| MAC | `3c:8a:1f:a4:85:60` |
| Radio 1 | nRF24L01+ via **HSPI** |
| Radio 2 | nRF24L01+ via **VSPI** |
| Display | SSD1306 OLED 0.96" I2C |
| Bateria | Li-Ion 3.7V com ADC (divisor 100k \|\| 500k) |
| LED | GPIO27 (4.7k resistor) |
| Botão | BOOT (GPIO0, built-in) |

### Pinout nRF24L01+

| Pin | HSPI (ESP32) | VSPI (ESP32) |
|---|---|---|
| CE | GPIO16 | GPIO22 |
| CSN | GPIO15 | GPIO21 |
| SCK | GPIO14 | GPIO18 |
| MOSI | GPIO13 | GPIO23 |
| MISO | GPIO12 | GPIO19 |
| VCC | 3.3V | 3.3V |
| GND | GND | GND |

### OLED I2C

| Pin | ESP32 |
|---|---|
| SCL | GPIO5 |
| SDA | GPIO4 |

---

## 3. Processo de Extração

### 3.1 Identificação do chip

```bash
python3 ~/.platformio/packages/tool-esptoolpy/esptool.py \
  --port /dev/ttyUSB0 chip_id
```

Output relevante:
```
Chip is ESP32-D0WD-V3 (revision v3.1)
Features: WiFi, BT, Dual Core, 240MHz
MAC: 3c:8a:1f:a4:85:60
Flash size: 4MB
```

### 3.2 Verificação de criptografia

```bash
python3 ~/.platformio/packages/tool-esptoolpy/espefuse.py \
  --port /dev/ttyUSB0 summary
```

Resultado:
- `FLASH_CRYPT_CNT = 0` → **Flash Encryption DESATIVADA**
- `BLOCK1` (chave) = todos zeros → sem chave
- `ABS_DONE_0/1 = False` → Secure Boot desativado
- **Conclusão: firmware não está cifrado**

### 3.3 Dump completo do flash

```bash
python3 ~/.platformio/packages/tool-esptoolpy/esptool.py \
  --port /dev/ttyUSB0 \
  read_flash 0x0 0x400000 ~/esp32_dump/flash_dump.bin
```

- Tamanho: 4MB
- Tempo: ~3 minutos
- **O ESP32 não foi modificado — apenas leitura**

### 3.4 Mapeamento de partições (binwalk)

```bash
binwalk ~/esp32_dump/flash_dump.bin
```

| Partição | Offset | Tamanho | Conteúdo |
|---|---|---|---|
| bootloader | 0x1000 | 28KB | ESP-IDF v4.4.5 bootloader |
| partition table | 0x8000 | 3KB | Tabela de partições |
| nvs | 0x9000 | 20KB | Vazio (sem configs guardadas) |
| otadata | 0xE000 | 8KB | OTA metadata |
| **app0** | **0x10000** | **1.3MB** | **Firmware ativo** |
| app1 | 0x150000 | 1.3MB | Vazio (OTA não usado) |
| spiffs | 0x290000 | 1.4MB | Vazio (sem ficheiros) |
| coredump | 0x3F0000 | 64KB | Vazio |

### 3.5 Extração das partições

```bash
# app0 (firmware principal)
dd if=flash_dump.bin of=extracted/app0.bin \
   bs=1 skip=65536 count=1310720

# SPIFFS
dd if=flash_dump.bin of=extracted/spiffs.bin \
   bs=1 skip=2686976 count=1441792
```

### 3.6 Análise de strings

```bash
strings extracted/app0.bin | grep -E "State|nRF|Bluetooth|WiFi|RC|voltage"
```

Strings chave encontradas:
```
Firmware : Official-Combo-Channel (BT-BLE-WiFi-RC)
https://github.com/EmenstaNougat/ESP32-BlueJammer
State 0: Idle & Status
State 1: Bluetooth
State 2: Bluetooth Low Energy
State 3: WiFi
State 4: RC
!Educational purposes only!
Hardware Serial Peripheral Interface started !!! HSPI nRF24 module initialized SUCCESSFULLY!
Variable Serial Peripheral Interface started !!! VSPI nRF24 module initialized SUCCESSFULLY!
[BatStat] Initial voltage: %.3fV  (%d%%)  source: %s
Initialized voltage readout...
SSD1306 allocation failed
```

---

## 4. Decompilação com Ghidra

### 4.1 Setup do ambiente

**Ghidra:** v10.3.2 (instalado em `/usr/share/ghidra`)
**Plugin Xtensa:** compilado de https://github.com/Ebiroll/ghidra-xtensa

#### Compilar o plugin (requer Java 17 e Gradle)

```bash
git clone https://github.com/Ebiroll/ghidra-xtensa
cd ghidra-xtensa

# Compilar o plugin
JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64 \
GHIDRA_INSTALL_DIR=/usr/share/ghidra \
GHIDRA_DIR=/usr/share/ghidra \
./gradlew buildExtension

# Compilar o .sla (SLEIGH language spec)
/usr/share/ghidra/support/sleigh \
  /tmp/xtensa_lang/xtensa.slaspec

# Instalar
sudo cp dist/ghidra_10.3.2_DEV_*_ghidra-xtensa.zip \
  /usr/share/ghidra/Ghidra/Processors/
sudo cp /tmp/xtensa_lang/xtensa.sla \
  /usr/share/ghidra/Ghidra/Processors/ghidra-xtensa/data/languages/
sudo chmod 644 \
  /usr/share/ghidra/Ghidra/Processors/ghidra-xtensa/data/languages/xtensa.sla
```

### 4.2 Decompilação headless

```bash
JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64 \
/usr/share/ghidra/support/analyzeHeadless \
  ~/esp32_dump/ghidra_project ESP32_BlueJammer \
  -import ~/esp32_dump/extracted/app0.bin \
  -processor Xtensa:LE:32:default \
  -postScript /tmp/decompile_esp32.py \
  -overwrite
```

**Resultado:** 3838 funções descompiladas → `decompiled_full.c` (156k linhas, 3.8MB)

### 4.3 Por que o output é C e não C++?

O firmware original foi escrito em **C++ (Arduino .ino)**. O Ghidra gera sempre pseudo-C porque o compilador destrói as abstrações C++ ao compilar:
- Classes → structs + funções com ponteiro `this`
- Métodos → funções com primeiro argumento sendo o objeto
- Templates → código expandido inline
- Namespaces → prefixos no nome mangled (já removidos pelo strip)

---

## 5. Mapeamento de Segmentos do app0.bin

O ESP32 image tem 5 segmentos:

| Segmento | Tipo | Load Address | File Offset | Tamanho |
|---|---|---|---|---|
| 0 | DROM (dados/strings RO) | `0x3f400020` | `0x000020` | 0x1d6a0 |
| 1 | DRAM (dados inicializados) | `0x3ffbdb60` | `0x1d6c8` | 0x2950 |
| 2 | IROM (código flash) | `0x400d0020` | `0x020020` | 0x9a8ac |
| 3 | DRAM (mais dados) | `0x3ffc04b0` | `0x0ba8d4` | 0x3678 |
| 4 | IRAM (código em RAM) | `0x40080000` | `0x0bdf54` | 0x1a278 |

**Entry point:** `0x40082f0c` (em IRAM, segmento 4)

### Endereços das strings chave (runtime)

| String | Runtime Address |
|---|---|
| "State 1: Bluetooth" | `0x3f401681` |
| "State 2: BLE" | `0x3f40169c` |
| "State 3: WiFi" | `0x3f4016c2` |
| "State 4: RC" | `0x3f4016d8` |
| "Initialized voltage..." | `0x3f401658` |
| "HSPI nRF24..." | `0x3f4002c4` |
| "VSPI nRF24..." | `0x3f400608` |

---

## 6. Funções Identificadas

| Endereço Ghidra | Função reconstruída | Descrição |
|---|---|---|
| `0x22a90` | `cycleMode()` | Incrementa modo 1→2→3→4→1 (press curto) |
| `0x22ab4` | `ledBlink_update()` | Controla piscar do LED de status |
| `0x22b24` | `setMode_Bluetooth()` | Ativa modo BT (State 1) |
| `0x22b6c` | `setMode_BLE()` | Ativa modo BLE (State 2) |
| `0x22bb4` | `setMode_WiFi()` | Ativa modo WiFi (State 3) |
| `0x22bfc` | `setMode_RC()` | Ativa modo RC (State 4) |
| `0x22c44` | `oled_drawStatus()` | Desenha indicadores HSPI/VSPI no OLED |
| `0x22c70` | `idleScreen()` | Ecrã idle com logo, bateria, status |
| `0x2309c` | `loop()` | Loop principal — botão + dispatch de modo |
| `0x23208` | `battery_getRaw()` | Lê ADC com média de 16 amostras |
| `0x23254` | `battery_getVoltage()` | Converte ADC em tensão (com calibração) |

---

## 7. Lógica do Firmware

### Fluxo de boot

```
setup()
  ├── Serial.begin(115200)
  ├── SSD1306.begin() → logo
  ├── ADC init → lê bateria inicial
  ├── Print banner (Firmware / GitHub / Educational)
  ├── HSPI nRF24 init → setAutoAck(false), PA_MAX, 2MBPS, CRC_DISABLED
  ├── VSPI nRF24 init → idem
  ├── pinMode(LED_PIN=27, OUTPUT)
  ├── pinMode(BOOT_BUTTON=0, INPUT_PULLUP)
  └── setMode_Bluetooth() → State 1 por defeito
```

### Loop principal

```
loop()
  ├── oled_update()
  ├── Ler GPIO0 (BOOT button)
  │   ├── Press curto (<500ms) → cycleMode() → 1→2→3→4→1
  │   └── Press longo (>500ms) → vai para Idle (State 0)
  └── Dispatch
      ├── State 0 → idleScreen()
      ├── State 1 → setMode_Bluetooth() → nRF24 varre 79ch BT
      ├── State 2 → setMode_BLE()       → nRF24 varre 40ch BLE
      ├── State 3 → setMode_WiFi()      → nRF24 varre 14ch WiFi
      └── State 4 → setMode_RC()        → nRF24 varre 125ch RC
```

### Mecanismo de jamming

O firmware usa **dois nRF24L01+** simultaneamente (HSPI + VSPI) para cobrir mais canais em paralelo. Para cada modo:

1. `setChannel(ch)` — define canal atual
2. `startConstantCarrier(PA_MAX, ch)` — emite portadora contínua no canal
3. Itera por todos os canais do modo em loop rápido

O ESP32 contribui também com o seu próprio rádio WiFi/BT interno para saturação adicional.

### LED de status

| Nº piscadas | Modo |
|---|---|
| 1 | Bluetooth |
| 2 | BLE |
| 3 | WiFi |
| 4 | RC |

---

## 8. Ficheiros Gerados

```
~/esp32_dump/
├── flash_dump.bin                    # Dump completo 4MB
├── extracted/
│   ├── bootloader.bin                # Bootloader (28KB)
│   ├── partition_table.bin           # Tabela de partições (3KB)
│   ├── app0.bin                      # Firmware ativo (1.3MB) ← principal
│   ├── app1.bin                      # OTA slot vazio
│   ├── spiffs.bin                    # Filesystem vazio
│   └── nvs.bin                       # NVS vazia
├── decompiled/
│   ├── decompiled_full.c             # 3838 funções Ghidra (156k linhas)
│   ├── jammer_main.c                 # Primeiras 50 funções (app code)
│   ├── jammer_functions.c            # Funções com refs às strings
│   └── bluejammer_reconstructed.c   # Código reconstruído legível
├── ghidra_project/                   # Projeto Ghidra
├── ghidra-xtensa/                    # Plugin Xtensa (source + built)
└── ESP32-BlueJammer/                 # Repo GitHub clonado (só .bin)
```

---

## 9. Próximos Passos

- [ ] **Versão C fiel** — limpar `jammer_main.c` e `decompiled_full.c`, renomear funções com nomes semânticos, remover código ESP-IDF irrelevante
- [ ] **Versão C++ adaptada** — reescrever usando classes Arduino (`RF24`, `Adafruit_SSD1306`, `Wire`, `SPI`), estrutura `.ino` compilável
- [ ] Testar compilação da versão C++ com PlatformIO (já instalado)
- [ ] Comparar binário gerado com o original via diff de strings

---

## 10. Ferramentas Usadas

| Ferramenta | Versão | Uso |
|---|---|---|
| esptool.py | v4.11.0 | Leitura do flash / info chip |
| espefuse.py | v4.11.0 | Verificação de criptografia |
| binwalk | — | Análise de partições |
| Ghidra | 10.3.2 | Decompilação |
| ghidra-xtensa | (Ebiroll) | Plugin Xtensa para Ghidra |
| PlatformIO | — | Toolchain ESP32 (objdump, esptool) |
| Java | 17 (OpenJDK) | Build do plugin Ghidra |

---

*Gerado automaticamente a partir do processo de reversing — 2026-05-04*
