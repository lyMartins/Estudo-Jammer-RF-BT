/*
 * ESP32-BlueJammer - Reconstructed Source Code
 * Original by @emensta (EmenstaNougat)
 * Decompiled via Ghidra Xtensa plugin from flash dump
 *
 * Hardware:
 *   - ESP32-D0WD-V3 rev3.1, 240MHz, 4MB flash
 *   - HSPI nRF24L01+: CE=GPIO16, CSN=GPIO15, SCK=GPIO14, MOSI=GPIO13, MISO=GPIO12
 *   - VSPI nRF24L01+: CE=GPIO22, CSN=GPIO21, SCK=GPIO18, MOSI=GPIO23, MISO=GPIO19
 *   - OLED SSD1306 I2C: SCL=GPIO5, SDA=GPIO4
 *   - Status LED: GPIO27 (via 4.7k resistor)
 *   - Boot button: GPIO0 (built-in)
 *   - Battery ADC with voltage divider
 */

// ============================================================
// GLOBAL STATE
// ============================================================

static int   g_currentMode    = 0;   // 0=Idle, 1=BT, 2=BLE, 3=WiFi, 4=RC
static int   g_savedMode      = 0;
static char  g_buttonPressed  = 0;
static char  g_buttonReleased = 0;
static char  g_longPress      = 0;
static uint  g_pressTime      = 0;
static int   g_ledBlink       = 0;   // blink counter for status LED
static int   g_loopCounter    = 0;

// ============================================================
// MODE SETTERS  (FUN_00022b24 / b6c / bb4 / bfc)
// Sets the jamming mode and updates OLED channel display
// ============================================================

// State 1: Bluetooth  (79 channels, 2.402-2.480 GHz)
int setMode_Bluetooth(void) {
    if (g_currentMode != 1) {
        g_currentMode = 1;
        oled_clearDisplay();
        oled_setChannel(g_channelBT, 0);
        g_pressTime   = millis();
        g_buttonPressed = 0;
        g_ledBlink = 1;
    }
    ledBlink_update();
    return g_currentMode;
}

// State 2: Bluetooth Low Energy  (40 channels, 2.400-2.4835 GHz)
int setMode_BLE(void) {
    if (g_currentMode != 2) {
        g_currentMode = 2;
        oled_clearDisplay();
        oled_setChannel(g_channelBLE, 0);
        g_pressTime   = millis();
        g_buttonPressed = 0;
        g_ledBlink = 2;
    }
    ledBlink_update();
    return g_currentMode;
}

// State 3: WiFi  (14 channels, 2.400-2.4835 GHz)
int setMode_WiFi(void) {
    if (g_currentMode != 3) {
        g_currentMode = 3;
        oled_clearDisplay();
        oled_setChannel(g_channelWiFi, 0);
        g_pressTime   = millis();
        g_buttonPressed = 0;
        g_ledBlink = 3;
    }
    ledBlink_update();
    return g_currentMode;
}

// State 4: RC (1-125 channels, 2.400-2.525 GHz)
int setMode_RC(void) {
    if (g_currentMode != 4) {
        g_currentMode = 4;
        oled_clearDisplay();
        oled_setChannel(g_channelRC, 0);
        g_pressTime   = millis();
        g_buttonPressed = 0;
        g_ledBlink = 4;
    }
    ledBlink_update();
    return g_currentMode;
}

// ============================================================
// CYCLE MODES  (FUN_00022a90)
// Called on short boot button press — cycles 1->2->3->4->1
// ============================================================

int cycleMode(void) {
    g_currentMode++;
    if (g_currentMode > 4) {
        g_currentMode = 1;
    }
    return g_currentMode;
}

// ============================================================
// MAIN LOOP  (FUN_0002309c)
// Handles button input and dispatches to active jammer
// ============================================================

char loop(void) {
    uint now;
    char buttonState;

    oled_update();

    buttonState = digitalRead(BOOT_BUTTON);  // GPIO0

    if (buttonState == LOW) {
        // Button pressed
        if (g_pressTime == 0) {
            g_pressTime = millis();
        } else if (!g_buttonPressed && !g_buttonReleased) {
            now = millis();
            if (now - g_pressTime > 500) {
                // Long press: save mode, go to idle
                g_savedMode     = g_currentMode;
                g_currentMode   = 0;
                g_buttonPressed = 1;
                g_buttonReleased = 1;
            }
        }
    } else if (g_pressTime != 0) {
        now = millis();
        if (now - g_pressTime < 500 && g_buttonPressed) {
            // Short press released: restore mode
            g_buttonReleased = 0;
            g_currentMode    = g_savedMode;
            g_longPress      = 1;
            g_currentMode    = 0;

            // Re-dispatch
            switch (g_currentMode) {
                case 1: setMode_Bluetooth(); break;
                case 2: setMode_BLE();       break;
                case 3: setMode_WiFi();      break;
                case 4: setMode_RC();        break;
            }
        }
        g_pressTime      = 0;
        g_buttonReleased = 0;
    }

    // Short press: cycle mode
    if (!g_buttonPressed) {
        buttonState = readButton();
        if (buttonState != 0) {
            if (!g_longPress) {
                cycleMode();
            } else {
                g_longPress = 0;
            }
        }
    }

    // Dispatch active mode
    switch (g_currentMode) {
        case 0: idleScreen();    break;
        case 1: setMode_Bluetooth(); break;
        case 2: setMode_BLE();       break;
        case 3: setMode_WiFi();      break;
        case 4: setMode_RC();        break;
    }

    return g_buttonPressed;
}

// ============================================================
// IDLE SCREEN / STATUS  (FUN_00022c70)
// Shows battery, both nRF24 status, logo on OLED
// ============================================================

int idleScreen(void) {
    // Draw static UI elements
    oled_drawBitmap(LOGO_X, LOGO_Y, bitmapboot, LOGO_W, LOGO_H);
    oled_drawHSPI_status(hspi_ok);
    oled_drawVSPI_status(vspi_ok);

    // Battery bar (calls ADC, draws bar on OLED)
    int batPct = battery_getPercent();
    oled_drawBatteryBar(batPct);

    // Voltage readout
    float vBat = battery_getVoltage();
    oled_printVoltage(vBat);

    oled_display();
    return g_loopCounter;
}

// ============================================================
// BATTERY / ADC  (FUN_00023208, FUN_00023254)
// Reads ADC, converts raw counts to voltage/percentage
// Voltage divider: R_bottom = 100k || 500k (ADC input)
// ============================================================

float battery_getVoltage(void) {
    // Average 16 ADC samples
    uint64_t sum = 0;
    for (int i = 0; i < 16; i++) {
        sum += adc_read(ADC_BATTERY_PIN);
    }
    uint32_t avg = sum >> 4;
    // Convert with calibration factor
    float voltage = (float)avg / ADC_DIVIDER_FACTOR;
    return voltage;
}

int battery_getPercent(void) {
    float v = battery_getVoltage();
    // Clamp to 3.0V - 4.2V range
    if (v >= 4.2f) return 100;
    if (v <= 3.0f) return 0;
    return (int)((v - 3.0f) / 1.2f * 100.0f);
}

// ============================================================
// SETUP  (called once at boot)
// ============================================================

void setup(void) {
    Serial.begin(115200);

    // Init OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
    }
    display.clearDisplay();
    display.display();

    // Init battery ADC
    Serial.println("Initialized voltage readout...");
    float v = battery_getVoltage();
    int pct = battery_getPercent();
    Serial.printf("[BatStat] Initial voltage: %.3fV  (%d%%)\n", v, pct);

    // Print firmware banner
    Serial.println("Firmware : Official-Combo-Channel (BT-BLE-WiFi-RC)");
    Serial.println("https://github.com/EmenstaNougat/ESP32-BlueJammer");
    Serial.println("!Educational purposes only!");
    Serial.println("I'm not responsible for your actions!");

    // Init HSPI nRF24
    SPIClass hspi(HSPI);
    hspi.begin(SCK_HSPI, MISO_HSPI, MOSI_HSPI, CSN_HSPI);
    RF24 radio_hspi(CE_HSPI, CSN_HSPI);
    if (radio_hspi.begin(&hspi)) {
        Serial.println("HSPI nRF24 module initialized SUCCESSFULLY!");
        radio_hspi.setAutoAck(false);
        radio_hspi.setPALevel(RF24_PA_MAX);
        radio_hspi.setDataRate(RF24_2MBPS);
        radio_hspi.setCRCLength(RF24_CRC_DISABLED);
        radio_hspi.startConstantCarrier(RF24_PA_MAX, 0);
    } else {
        Serial.println("HSPI nRF24 module could NOT be initialized!");
    }

    // Init VSPI nRF24
    SPIClass vspi(VSPI);
    vspi.begin(SCK_VSPI, MISO_VSPI, MOSI_VSPI, CSN_VSPI);
    RF24 radio_vspi(CE_VSPI, CSN_VSPI);
    if (radio_vspi.begin(&vspi)) {
        Serial.println("VSPI nRF24 module initialized SUCCESSFULLY!");
        radio_vspi.setAutoAck(false);
        radio_vspi.setPALevel(RF24_PA_MAX);
        radio_vspi.setDataRate(RF24_2MBPS);
        radio_vspi.setCRCLength(RF24_CRC_DISABLED);
        radio_vspi.startConstantCarrier(RF24_PA_MAX, 0);
    } else {
        Serial.println("VSPI nRF24 module could NOT be initialized!");
    }

    // Status LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Boot button
    pinMode(BOOT_BUTTON, INPUT_PULLUP);

    // Default to Bluetooth mode
    setMode_Bluetooth();

    Serial.println("State 1: Bluetooth");
}
