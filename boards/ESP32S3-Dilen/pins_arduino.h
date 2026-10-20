#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

#define USB_VID 0x303A
#define USB_PID 0x1001
#define USB_as_HID 1

#define SERIAL_TX 48
#define SERIAL_RX 47
static const uint8_t TX = SERIAL_TX;
static const uint8_t RX = SERIAL_RX;

#define GROVE_SDA -1
#define GROVE_SCL -1
static const uint8_t SDA = GROVE_SDA;
static const uint8_t SCL = GROVE_SCL;

#define SPI_SCK_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SS_PIN 10
static const uint8_t SS = SPI_SS_PIN;
static const uint8_t MOSI = SPI_MOSI_PIN;
static const uint8_t MISO = SPI_MISO_PIN;
static const uint8_t SCK = SPI_SCK_PIN;

#define CC1101_GDO0_PIN 9
#define CC1101_GDO2_PIN -1
#define CC1101_SS_PIN 10
#define SDCARD_CS 21

// Настройки дисплея ILI9341
#define HAS_SCREEN 1
#define USER_SETUP_LOADED 1
#define ILI9341_DRIVER 1
#define TFT_WIDTH 240
#define TFT_HEIGHT 320
#define TFT_MISO 5
#define TFT_MOSI 7
#define TFT_SCLK 6
#define TFT_CS 4
#define TFT_DC 8
#define TFT_RST 15
#define TFT_BL -1
#define BACKLIGHT -1
#define TFT_BACKLIGHT_ON HIGH

// Настройки тачскрина XPT2046 на выбранных пинах
#define TOUCH_CS  39  // T_CS
#define TOUCH_CLK 38  // T_CLK
#define TOUCH_DO  40  // T_DO (MISO)
#define TOUCH_DIN 41  // T_DIN (MOSI)

#define SMOOTH_FONT 1
#define SPI_FREQUENCY 20000000
#define SPI_READ_FREQUENCY 10000000
#define ROTATION 1
#define MINBRIGHT 0

// Кнопки полностью отключены
#define BTN_NEXT_PIN  -1
#define BTN_PREV_PIN  -1
#define BTN_BACK_PIN  -1
#define BTN_OK_PIN    -1
#define BTN_ACT HIGH
#define DEEPSLEEP_WAKEUP_PIN -1

#define TXLED 18
#define RXLED 42
#define LED_ON HIGH
#define LED_OFF LOW

#define FONT_SMALL 1
#define FM 2
#define FG 3

#endif // Pins_Arduino_h
