#include "core/powerSave.h"
#include "core/utils.h"
#include <Arduino.h>
#include <globals.h>
#include <interface.h>

namespace {
constexpr char HARDWARE_CONFIG_MARKER[] = "/.dilen-hw-r2";

uint32_t touchDownTime = 0;
bool isTouching = false;
int startX = 0, startY = 0;
bool longPressTriggered = false;
} // namespace

void _setup_gpio() {
    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_DC, OUTPUT);
    pinMode(TFT_RST, OUTPUT);
    digitalWrite(TFT_CS, HIGH);
    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_RST, HIGH);

    if (TOUCH_CS != -1) {
        pinMode(TOUCH_CS, OUTPUT);
        digitalWrite(TOUCH_CS, HIGH);
    }

    pinMode(CC1101_SS_PIN, OUTPUT);
    pinMode(NRF24_SS_PIN, OUTPUT);
    pinMode(NRF24_CE_PIN, OUTPUT);
    digitalWrite(CC1101_SS_PIN, HIGH);
    digitalWrite(NRF24_SS_PIN, HIGH);
    digitalWrite(CC1101_CE_PIN, LOW);

    bruceConfig.colorInverted = 0;
    bruceConfigPins.rfModule = CC1101_SPI_MODULE;
}

void _post_setup_gpio() {
    if (!bruceConfig.devMode) bruceConfig.setDevMode(1);

    if (!LittleFS.exists(HARDWARE_CONFIG_MARKER)) {
        File marker = LittleFS.open(HARDWARE_CONFIG_MARKER, FILE_WRITE);
        if (marker) {
            marker.print(BRUCE_VERSION);
            marker.close();
        }
    }
}

int getBattery() { return 0; }
bool isCharging() { return false; }
void _setBrightness(uint8_t brightval) { (void)brightval; }

/***************************************************************************************
** Input Handler: Управление тачскрином (XPT2046)
***************************************************************************************/
void InputHandler(void) {
    uint16_t x = 0, y = 0;
    bool pressed = tft.getTouch(&x, &y);
    uint32_t now = millis();

    if (pressed) {
        if (!isTouching) {
            isTouching = true;
            touchDownTime = now;
            startX = x;
            startY = y;
            longPressTriggered = false;
        } else {
            // Долгое зажатие (> 600 мс) = Esc / Назад
            if (!longPressTriggered && (now - touchDownTime > 600)) {
                EscPress = true;
                AnyKeyPress = true;
                longPressTriggered = true;
            }
        }
    } else {
        if (isTouching) {
            if (!longPressTriggered) {
                uint32_t duration = now - touchDownTime;
                
                // Короткий тап (< 500 мс)
                if (duration < 500) {
                    if (startX < 80) {
                        UpPress = true;     // Левая часть ($X < 80$) = Влево / Прошлый
                    } else if (startX > 160) {
                        NextPress = true;   // Правая часть ($X > 160$) = Вправо / Следующий
                    } else {
                        SelPress = true;    // Центр ($80 \le X \le 160$) = ОК / Выбор
                    }
                    AnyKeyPress = true;
                }
            }
            isTouching = false;
            longPressTriggered = false;
        }
    }
}

void powerOff() {}
void checkReboot() {}
