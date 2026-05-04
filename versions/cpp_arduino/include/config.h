#pragma once

// ─── HSPI — nRF24L01+ módulo 1 ───────────────────────────────────────────────
#define HSPI_CE   16
#define HSPI_CSN  15
#define HSPI_SCK  14
#define HSPI_MOSI 13
#define HSPI_MISO 12

// ─── VSPI — nRF24L01+ módulo 2 ───────────────────────────────────────────────
#define VSPI_CE   22
#define VSPI_CSN  21
#define VSPI_SCK  18
#define VSPI_MOSI 23
#define VSPI_MISO 19

// ─── OLED SSD1306 I2C ────────────────────────────────────────────────────────
#define OLED_SDA  4
#define OLED_SCL  5
#define OLED_ADDR 0x3C
#define OLED_W    128
#define OLED_H    64

// ─── Outros pinos ────────────────────────────────────────────────────────────
#define PIN_LED    27   // LED de status (azul), via resistor 4.7k
#define PIN_BUTTON  0   // Botão BOOT do ESP32

// ─── ADC bateria ─────────────────────────────────────────────────────────────
#define PIN_BAT_ADC   34    // GPIO34 (input only)
#define ADC_SAMPLES   16    // amostras para média
#define VREF          3.3f
#define ADC_MAX       4095.0f
#define R_TOP         100000.0f   // 100k (top leg do divisor)
#define R_BOT         500000.0f   // 500k || impedância ADC

// ─── Modos de operação ───────────────────────────────────────────────────────
#define MODE_IDLE  0
#define MODE_BT    1   // Bluetooth     79ch  2.402–2.480 GHz
#define MODE_BLE   2   // BLE           40ch  2.400–2.4835 GHz
#define MODE_WIFI  3   // WiFi          14ch  2.400–2.4835 GHz
#define MODE_RC    4   // RC/Drones    125ch  2.400–2.525 GHz

// ─── Canais por modo ─────────────────────────────────────────────────────────
#define BT_CH_START   2    // 2.402 GHz
#define BT_CH_END     80   // 2.480 GHz
#define BLE_CH_START  0    // 2.400 GHz
#define BLE_CH_END    39
#define WIFI_CH_START 1
#define WIFI_CH_END   14
#define RC_CH_START   0
#define RC_CH_END     124

// ─── Temporização ────────────────────────────────────────────────────────────
#define BTN_DEBOUNCE_MS   50
#define BTN_LONGPRESS_MS  500
#define LED_BLINK_MS      200
#define OLED_REFRESH_MS   100
