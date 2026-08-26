#include "core/powerSave.h"
#include "core/utils.h"
#include <Arduino.h>
#include <globals.h>
#include <interface.h>

namespace {
constexpr uint32_t BUTTON_DEBOUNCE_MS = 25;
constexpr uint32_t ACTION_LONG_PRESS_MS = 800;
constexpr char HARDWARE_CONFIG_MARKER[] = "/.dilen-hw-r2";

struct DebouncedButton {
    uint8_t pin;
    bool rawDown = false;
    bool stableDown = false;
    uint32_t rawChangedAt = 0;

    bool update(uint32_t now) {
        bool readingDown = digitalRead(pin) == BTN_ACT;
        if (readingDown != rawDown) {
            rawDown = readingDown;
            rawChangedAt = now;
        }

        if (stableDown != rawDown && now - rawChangedAt >= BUTTON_DEBOUNCE_MS) {
            stableDown = rawDown;
            return true;
        }
        return false;
    }
};

DebouncedButton nextButton{NEXT_BTN};
DebouncedButton actionButton{ACTION_BTN};
uint32_t actionPressedAt = 0;
bool actionLongFired = false;
bool actionWakeConsumed = false;
} // namespace

/***************************************************************************************
** Initial board GPIO setup
***************************************************************************************/
void _setup_gpio() {
    pinMode(NEXT_BTN, INPUT_PULLUP);
    pinMode(ACTION_BTN, INPUT_PULLUP);

    pinMode(TFT_CS, OUTPUT);
    pinMode(TFT_DC, OUTPUT);
    pinMode(TFT_RST, OUTPUT);
    digitalWrite(TFT_CS, HIGH);
    digitalWrite(TFT_DC, HIGH);
    digitalWrite(TFT_RST, HIGH);

    pinMode(CC1101_SS_PIN, OUTPUT);
    pinMode(NRF24_SS_PIN, OUTPUT);
    pinMode(NRF24_CE_PIN, OUTPUT);
    digitalWrite(CC1101_SS_PIN, HIGH);
    digitalWrite(NRF24_SS_PIN, HIGH);
    digitalWrite(NRF24_CE_PIN, LOW);

    bruceConfig.colorInverted = 0;
    bruceConfigPins.rfModule = CC1101_SPI_MODULE;
}

/***************************************************************************************
** Apply the custom board's radio mapping once, after LittleFS settings are loaded.
** This migrates pin settings left by a previously installed CYD build while still
** allowing later changes made from Dev Mode to persist across reboots.
***************************************************************************************/
void _post_setup_gpio() {
    if (!bruceConfig.devMode) bruceConfig.setDevMode(1);

    if (!LittleFS.exists(HARDWARE_CONFIG_MARKER)) {
        bruceConfigPins.CC1101_bus = {
            (gpio_num_t)CC1101_SCK_PIN,
            (gpio_num_t)CC1101_MISO_PIN,
            (gpio_num_t)CC1101_MOSI_PIN,
            (gpio_num_t)CC1101_SS_PIN,
            (gpio_num_t)CC1101_GDO0_PIN,
            (gpio_num_t)CC1101_GDO2_PIN
        };
        bruceConfigPins.NRF24_bus = {
            (gpio_num_t)NRF24_SCK_PIN,
            (gpio_num_t)NRF24_MISO_PIN,
            (gpio_num_t)NRF24_MOSI_PIN,
            (gpio_num_t)NRF24_SS_PIN,
            (gpio_num_t)NRF24_CE_PIN,
            GPIO_NUM_NC
        };
        bruceConfigPins.rfModule = CC1101_SPI_MODULE;
        bruceConfigPins.saveFile();

        File marker = LittleFS.open(HARDWARE_CONFIG_MARKER, FILE_WRITE);
        if (marker) {
            marker.print(BRUCE_VERSION);
            marker.close();
        }
        Serial.println("Dilen radio pin configuration migrated to r2");
    }

    // Keep both devices deselected before either radio driver starts the shared bus.
    pinMode(CC1101_SS_PIN, OUTPUT);
    pinMode(NRF24_SS_PIN, OUTPUT);
    pinMode(NRF24_CE_PIN, OUTPUT);
    digitalWrite(CC1101_SS_PIN, HIGH);
    digitalWrite(NRF24_SS_PIN, HIGH);
    digitalWrite(NRF24_CE_PIN, LOW);

    Serial.printf(
        "CC1101 SPI: SCK=%d MISO=%d MOSI=%d CS=%d GDO0=%d\n",
        bruceConfigPins.CC1101_bus.sck,
        bruceConfigPins.CC1101_bus.miso,
        bruceConfigPins.CC1101_bus.mosi,
        bruceConfigPins.CC1101_bus.cs,
        bruceConfigPins.CC1101_bus.io0
    );
    Serial.printf(
        "nRF24 SPI: SCK=%d MISO=%d MOSI=%d CSN=%d CE=%d\n",
        bruceConfigPins.NRF24_bus.sck,
        bruceConfigPins.NRF24_bus.miso,
        bruceConfigPins.NRF24_bus.mosi,
        bruceConfigPins.NRF24_bus.cs,
        bruceConfigPins.NRF24_bus.io0
    );
}

/***************************************************************************************
** No battery monitor is connected
***************************************************************************************/
int getBattery() { return 0; }

bool isCharging() { return false; }

/***************************************************************************************
** Backlight is wired directly to 3.3 V, so firmware dimming is unavailable
***************************************************************************************/
void _setBrightness(uint8_t brightval) { (void)brightval; }

/***************************************************************************************
** GPIO38: Next
** GPIO39 short press: Select
** GPIO39 held for 800 ms: Back/Escape
***************************************************************************************/
void InputHandler(void) {
    const uint32_t now = millis();
    const bool nextChanged = nextButton.update(now);
    const bool actionChanged = actionButton.update(now);

    if (nextChanged && nextButton.stableDown) {
        if (wakeUpScreen()) return;
        NextPress = true;
        AnyKeyPress = true;
    }

    if (actionChanged && actionButton.stableDown) {
        actionPressedAt = now;
        actionLongFired = false;
        actionWakeConsumed = wakeUpScreen();
        if (actionWakeConsumed) return;
    }

    if (actionButton.stableDown && !actionLongFired && !actionWakeConsumed &&
        now - actionPressedAt >= ACTION_LONG_PRESS_MS) {
        actionLongFired = true;
        EscPress = true;
        AnyKeyPress = true;
    }

    if (actionChanged && !actionButton.stableDown) {
        if (!actionLongFired && !actionWakeConsumed) {
            SelPress = true;
            AnyKeyPress = true;
        }
        actionLongFired = false;
        actionWakeConsumed = false;
    }
}

void powerOff() {}

void checkReboot() {}
