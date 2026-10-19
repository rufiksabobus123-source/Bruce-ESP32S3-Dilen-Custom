#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

#define USB_VID 0x303A
#define USB_PID 0x1001
#define USB_as_HID 1

// Native UART pins used by the external NEO-M7 GPS
// GPS TXD -> ESP32-S3 RX (GPIO40)
// GPS RXD -> ESP32-S3 TX (GPIO41)
#define SERIAL_TX 41
#define SERIAL_RX 40
static const uint8_t TX = SERIAL_TX;
static const uint8_t RX = SERIAL_RX;

// Free expansion pins used as the default I2C/Grove bus
#define GROVE_SDA 1
#define GROVE_SCL 2
static const uint8_t SDA = GROVE_SDA;
static const uint8_t SCL = GROVE_SCL;

// Shared radio SPI bus (FSPI)
#define SPI_SCK_PIN 12
#define SPI_MOSI_PIN 11
#define SPI_MISO_PIN 13
#define SPI_SS_PIN 10
static const uint8_t SS = SPI_SS_PIN;
static const uint8_t MOSI = SPI_MOSI_PIN;
static const uint8_t MISO = SPI_MISO_PIN;
static const uint8_t SCK = SPI_SCK_PIN;

// CC1101
#define USE_CC1101_VIA_SPI
#define CC1101_GDO0_PIN 9
#define CC1101_GDO2_PIN -1
#define CC1101_SS_PIN 10
#define CC1101_MOSI_PIN SPI_MOSI_PIN
#define CC1101_SCK_PIN SPI_SCK_PIN
#define CC1101_MISO_PIN SPI_MISO_PIN

// nRF24L01
#define USE_NRF24_VIA_SPI
#define NRF24_CE_PIN 16
#define NRF24_SS_PIN 17
#define NRF24_MOSI_PIN SPI_MOSI_PIN
#define NRF24_SCK_PIN SPI_SCK_PIN
#define NRF24_MISO_PIN SPI_MISO_PIN

// MicroSD shares the radio SPI bus and uses its own chip-select
#define SDCARD_CS 21
#define SDCARD_SCK SPI_SCK_PIN
#define SDCARD_MISO SPI_MISO_PIN
#define SDCARD_MOSI SPI_MOSI_PIN

// ILI9341 display on the independent HSPI bus
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
#define TOUCH_CS -1
#define SMOOTH_FONT 1
#define SPI_FREQUENCY 20000000
#define SPI_READ_FREQUENCY 10000000
#define ROTATION 1
#define MINBRIGHT 0

// Two-button navigation
#define NEXT_BTN 38
#define ACTION_BTN 39
#define DW_BTN NEXT_BTN
#define SEL_BTN ACTION_BTN
#define BTN_ACT LOW
#define BTN_ALIAS "OK"
#define DEEPSLEEP_WAKEUP_PIN ACTION_BTN

// External infrared modules
#define TXLED 18
#define RXLED 42
#define IR_TX_PINS {{"IR TX GPIO18", 18}}
#define IR_RX_PINS {{"IR RX GPIO42", 42}}
#define LED_ON HIGH
#define LED_OFF LOW

// UI font sizes
#define FONT_SMALL 1
#define FM 2
#define FG 3

#endif // Pins_Arduino_h
