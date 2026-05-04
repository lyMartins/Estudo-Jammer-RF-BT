/*
 * ESP32-BlueJammer — Reimplementação C++ (PlatformIO / Arduino)
 *
 * Baseado em reversing do firmware original de @emensta (EmenstaNougat)
 * https://github.com/EmenstaNougat/ESP32-BlueJammer
 *
 * Processo: flash dump → Ghidra (Xtensa plugin) → pseudo-C → C++ compilável
 *
 * ⚠️  Jamming de RF é ILEGAL. Apenas para fins educativos e laboratório próprio.
 */

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

// ─────────────────────────────────────────────────────────────────────────────
// Objectos globais
// ─────────────────────────────────────────────────────────────────────────────

// Dois barramentos SPI independentes
SPIClass spi_hspi(HSPI);
SPIClass spi_vspi(VSPI);

// Dois módulos nRF24L01+ (um por barramento)
RF24 radio1(HSPI_CE, HSPI_CSN);   // HSPI
RF24 radio2(VSPI_CE, VSPI_CSN);   // VSPI

// OLED
Adafruit_SSD1306 display(OLED_W, OLED_H, &Wire, -1);

// ─────────────────────────────────────────────────────────────────────────────
// Estado global
// ─────────────────────────────────────────────────────────────────────────────

struct State {
    uint8_t  mode         = MODE_BT;  // modo actual
    uint8_t  savedMode    = MODE_BT;  // guardado durante long-press
    bool     radio1_ok    = false;
    bool     radio2_ok    = false;
    float    batVoltage   = 0.0f;
    uint8_t  batPercent   = 0;
    uint32_t lastOled     = 0;
    uint32_t lastBlink    = 0;
    uint8_t  blinkCount   = 0;
    bool     ledState     = false;
} g;

// ─────────────────────────────────────────────────────────────────────────────
// Bateria
// ─────────────────────────────────────────────────────────────────────────────

float battery_readVoltage() {
    uint32_t sum = 0;
    for (int i = 0; i < ADC_SAMPLES; i++) {
        sum += analogRead(PIN_BAT_ADC);
    }
    float raw = (float)(sum / ADC_SAMPLES);
    // Tensão no pino ADC
    float vAdc = (raw / ADC_MAX) * VREF;
    // Compensar divisor de tensão
    float vBat = vAdc * ((R_TOP + R_BOT) / R_BOT);
    return vBat;
}

uint8_t battery_percent(float v) {
    if (v >= 4.2f) return 100;
    if (v <= 3.0f) return 0;
    return (uint8_t)((v - 3.0f) / 1.2f * 100.0f);
}

// ─────────────────────────────────────────────────────────────────────────────
// nRF24L01+ — inicialização e configuração para jamming
// ─────────────────────────────────────────────────────────────────────────────

bool radio_init(RF24 &radio, SPIClass &spi, uint8_t ce, uint8_t csn,
                const char *label) {
    spi.begin();
    if (!radio.begin(&spi)) {
        Serial.printf("!!! %s nRF24 could NOT be initialized!\n", label);
        return false;
    }
    // Configurações para máximo ruído / cobertura
    radio.setAutoAck(false);            // sem ACKs — envio puro
    radio.setPALevel(RF24_PA_MAX);      // potência máxima
    radio.setDataRate(RF24_2MBPS);      // 2 Mbps — largura de banda máxima
    radio.setCRCLength(RF24_CRC_DISABLED); // sem CRC — packets inválidos OK
    radio.setRetries(0, 0);             // sem retransmissões
    radio.setPayloadSize(32);           // payload máximo
    radio.openWritingPipe((uint8_t*)"JJJJJ"); // endereço qualquer
    radio.stopListening();              // modo transmissor

    Serial.printf("%s nRF24 initialized SUCCESSFULLY!\n", label);
    return true;
}

void radio_setChannel(RF24 &radio, uint8_t ch) {
    radio.setChannel(ch);
}

// Envia payload de lixo no canal actual — satura o meio
void radio_flood(RF24 &radio) {
    uint8_t payload[32];
    // payload aleatório — não importa o conteúdo, apenas o ruído RF
    for (int i = 0; i < 32; i++) payload[i] = random(0xFF);
    radio.write(payload, 32);
}

// ─────────────────────────────────────────────────────────────────────────────
// OLED — display
// ─────────────────────────────────────────────────────────────────────────────

const char* modeName(uint8_t mode) {
    switch (mode) {
        case MODE_IDLE: return "Idle & Status";
        case MODE_BT:   return "Bluetooth";
        case MODE_BLE:  return "Bluetooth LE";
        case MODE_WIFI: return "WiFi";
        case MODE_RC:   return "RC / Drones";
        default:        return "???";
    }
}

void oled_drawBatBar(uint8_t pct) {
    // Contorno da bateria (canto superior direito)
    display.drawRect(104, 2, 20, 10, WHITE);
    display.drawRect(124, 4, 3, 6, WHITE);  // terminal +
    // Barra de nível
    uint8_t barW = (uint8_t)(18.0f * pct / 100.0f);
    display.fillRect(105, 3, barW, 8, WHITE);
}

void oled_drawStatusIcon(uint8_t x, uint8_t y, bool ok, const char *label) {
    display.setCursor(x, y);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print(label);
    display.print(ok ? " OK" : " --");
}

void oled_idle() {
    display.clearDisplay();

    // Título
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("ESP32-BlueJammer");

    // Bateria
    oled_drawBatBar(g.batPercent);
    display.setCursor(104, 14);
    display.printf("%d%%", g.batPercent);

    // Tensão
    display.setCursor(0, 14);
    display.printf("%.2fV", g.batVoltage);

    // Status dos módulos
    oled_drawStatusIcon(0, 26, g.radio1_ok, "HSPI");
    oled_drawStatusIcon(64, 26, g.radio2_ok, "VSPI");

    // Instrução
    display.setCursor(0, 50);
    display.println("BOOT: ciclar modo");

    display.display();
}

void oled_jamming(uint8_t ch1, uint8_t ch2) {
    display.clearDisplay();

    // Modo activo
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.printf("Mode: %s", modeName(g.mode));

    // Canal actual de cada rádio
    display.setCursor(0, 14);
    display.printf("R1 ch: %-3d  R2 ch: %-3d", ch1, ch2);

    // Barra de "actividade" (animação simples)
    static uint8_t anim = 0;
    anim = (anim + 1) % 16;
    for (int i = 0; i < anim; i++) {
        display.fillRect(i * 8, 40, 6, 10, WHITE);
    }

    // Bateria compacta
    oled_drawBatBar(g.batPercent);

    display.display();
}

// ─────────────────────────────────────────────────────────────────────────────
// LED de status — pisca N vezes conforme o modo
// ─────────────────────────────────────────────────────────────────────────────

void led_update() {
    if (g.mode == MODE_IDLE) {
        digitalWrite(PIN_LED, LOW);
        return;
    }
    uint32_t now = millis();
    if (now - g.lastBlink < LED_BLINK_MS) return;
    g.lastBlink = now;

    if (g.blinkCount < g.mode * 2) {
        g.ledState = !g.ledState;
        digitalWrite(PIN_LED, g.ledState);
        g.blinkCount++;
    } else {
        // Pausa entre sequências
        digitalWrite(PIN_LED, LOW);
        if (g.blinkCount >= g.mode * 2 + 4) {
            g.blinkCount = 0;
        } else {
            g.blinkCount++;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Botão BOOT — gestão de press curto e longo
// ─────────────────────────────────────────────────────────────────────────────

class Button {
public:
    Button(uint8_t pin) : _pin(pin) {}

    void begin() {
        pinMode(_pin, INPUT_PULLUP);
    }

    // Retorna true no flanco de subida (soltar)
    bool wasShortPressed() {
        bool pressed = (digitalRead(_pin) == LOW);

        if (pressed && !_lastState) {
            // Início do press
            _pressStart = millis();
            _lastState  = true;
        } else if (!pressed && _lastState) {
            // Soltar
            _lastState = false;
            uint32_t dur = millis() - _pressStart;
            if (dur >= BTN_DEBOUNCE_MS && dur < BTN_LONGPRESS_MS) {
                return true;   // press curto
            }
        }
        return false;
    }

    bool isLongPressed() {
        if (!_lastState) return false;
        return (millis() - _pressStart) >= BTN_LONGPRESS_MS;
    }

private:
    uint8_t  _pin;
    bool     _lastState  = false;
    uint32_t _pressStart = 0;
};

Button btn(PIN_BUTTON);

// ─────────────────────────────────────────────────────────────────────────────
// Modos de jamming
// ─────────────────────────────────────────────────────────────────────────────

void jam_bluetooth() {
    // Varre 79 canais BT (2.402–2.480 GHz) com os 2 rádios intercalados
    for (uint8_t ch = BT_CH_START; ch <= BT_CH_END; ch++) {
        radio_setChannel(radio1, ch);
        radio_flood(radio1);

        uint8_t ch2 = BT_CH_END - (ch - BT_CH_START); // inverso no r2
        radio_setChannel(radio2, ch2);
        radio_flood(radio2);
    }
    oled_jamming(BT_CH_START, BT_CH_END);
}

void jam_ble() {
    // Varre 40 canais BLE (2.400–2.4835 GHz)
    for (uint8_t ch = BLE_CH_START; ch <= BLE_CH_END; ch++) {
        radio_setChannel(radio1, ch);
        radio_flood(radio1);

        radio_setChannel(radio2, BLE_CH_END - ch);
        radio_flood(radio2);
    }
    oled_jamming(BLE_CH_START, BLE_CH_END);
}

void jam_wifi() {
    // Varre 14 canais WiFi 2.4GHz
    // Cada canal WiFi tem ~22MHz de largura; nRF24 cobre 1MHz por canal
    // Varrer todo o espectro cobre os canais sobrepostos
    for (uint8_t ch = WIFI_CH_START; ch <= 83; ch++) {  // cobre todos os 14ch WiFi
        radio_setChannel(radio1, ch);
        radio_flood(radio1);

        radio_setChannel(radio2, 83 - ch + WIFI_CH_START);
        radio_flood(radio2);
    }
    oled_jamming(WIFI_CH_START, 83);
}

void jam_rc() {
    // Varre 125 canais RC/Drones (2.400–2.525 GHz)
    for (uint8_t ch = RC_CH_START; ch <= RC_CH_END; ch++) {
        radio_setChannel(radio1, ch);
        radio_flood(radio1);

        radio_setChannel(radio2, RC_CH_END - ch);
        radio_flood(radio2);
    }
    oled_jamming(RC_CH_START, RC_CH_END);
}

// ─────────────────────────────────────────────────────────────────────────────
// Cicla para o próximo modo (1 → 2 → 3 → 4 → 1)
// ─────────────────────────────────────────────────────────────────────────────

void nextMode() {
    g.mode = (g.mode % 4) + 1;  // 1→2→3→4→1
    g.blinkCount = 0;
    Serial.printf("State %d: %s\n", g.mode, modeName(g.mode));
}

// ─────────────────────────────────────────────────────────────────────────────
// setup()
// ─────────────────────────────────────────────────────────────────────────────

void setup() {
    Serial.begin(115200);
    delay(500);

    // Banner
    Serial.println();
    Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    Serial.println("     Firmware : Official-Combo-Channel (BT-BLE-WiFi-RC)");
    Serial.println("     https://github.com/EmenstaNougat/ESP32-BlueJammer");
    Serial.println("     !Educational purposes only!");
    Serial.println("     I'm not responsible for your actions!");
    Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    // LED e botão
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);
    btn.begin();

    // OLED
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("SSD1306 allocation failed");
    } else {
        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setCursor(0, 20);
        display.setTextSize(2);
        display.println("BlueJammer");
        display.display();
    }

    // Bateria
    Serial.println("Initialized voltage readout...");
    g.batVoltage  = battery_readVoltage();
    g.batPercent  = battery_percent(g.batVoltage);
    Serial.printf("[BatStat] Initial voltage: %.3fV  (%d%%)\n",
                  g.batVoltage, g.batPercent);

    // HSPI nRF24
    spi_hspi.begin(HSPI_SCK, HSPI_MISO, HSPI_MOSI, HSPI_CSN);
    g.radio1_ok = radio_init(radio1, spi_hspi, HSPI_CE, HSPI_CSN, "HSPI");

    // VSPI nRF24
    spi_vspi.begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI, VSPI_CSN);
    g.radio2_ok = radio_init(radio2, spi_vspi, VSPI_CE, VSPI_CSN, "VSPI");

    // Modo inicial
    g.mode = MODE_BT;
    Serial.printf("State %d: %s\n", g.mode, modeName(g.mode));

    delay(1000);
}

// ─────────────────────────────────────────────────────────────────────────────
// loop()
// ─────────────────────────────────────────────────────────────────────────────

void loop() {
    // Botão — press curto: próximo modo | long-press: ir para idle
    if (btn.wasShortPressed()) {
        if (g.mode == MODE_IDLE) {
            g.mode = g.savedMode;
        } else {
            nextMode();
        }
    }
    if (btn.isLongPressed() && g.mode != MODE_IDLE) {
        g.savedMode = g.mode;
        g.mode = MODE_IDLE;
        Serial.println("State 0: Idle & Status");
    }

    // Atualizar bateria periodicamente
    static uint32_t lastBat = 0;
    if (millis() - lastBat > 5000) {
        lastBat = millis();
        g.batVoltage = battery_readVoltage();
        g.batPercent = battery_percent(g.batVoltage);
    }

    // LED de status
    led_update();

    // Dispatch do modo activo
    switch (g.mode) {
        case MODE_IDLE:
            oled_idle();
            delay(OLED_REFRESH_MS);
            break;
        case MODE_BT:
            jam_bluetooth();
            break;
        case MODE_BLE:
            jam_ble();
            break;
        case MODE_WIFI:
            jam_wifi();
            break;
        case MODE_RC:
            jam_rc();
            break;
    }
}
