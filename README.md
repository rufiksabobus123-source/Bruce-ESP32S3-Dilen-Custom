# Bruce ESP32-S3 Dilen Custom

A custom hardware target for [Bruce firmware](https://github.com/BruceDevices/firmware), based on Bruce 1.15 and adapted for a home-built ESP32-S3 N16R8 handheld multi-tool.

This repository does **not** claim authorship of Bruce. The original firmware, user interface, features, and most of the source code belong to the Bruce project and its contributors. This build adds a board target, fixed hardware pin mapping, two-button navigation, and configuration behavior for Dilen's device.

## Custom hardware

- ESP32-S3 N16R8
- ILI9341 240 x 320 display (touch not connected)
- CC1101 Sub-GHz transceiver
- nRF24L01 2.4 GHz transceiver
- PN532 NFC reader/writer in I2C mode
- NEO-M7 GPS receiver
- IR transmitter and receiver
- MicroSD storage
- Two physical navigation buttons

## Main customizations

- Dedicated PlatformIO environment: `esp32s3-dilen`
- Custom ESP32-S3 board definition
- Two-button navigation with software debounce
- Short press on GPIO39 selects; an 800 ms hold goes back
- Persistent custom radio mapping and one-time migration from older settings
- CC1101, nRF24L01, and MicroSD configured on one shared SPI bus
- Independent SPI bus for the ILI9341 display
- Fixed GPS, PN532, and infrared defaults

## Shared SPI architecture

The CC1101, nRF24L01, and MicroSD module share the same SCK, MOSI, and MISO wires. Each device has a separate chip-select line, so only one peripheral is selected at a time.

| SPI signal | ESP32-S3 |
| --- | ---: |
| SCK | GPIO12 |
| MOSI | GPIO11 |
| MISO | GPIO13 |

| Device | CS / CSN | Extra signal |
| --- | ---: | --- |
| CC1101 | GPIO10 | GDO0 = GPIO9 |
| nRF24L01 | GPIO17 | CE = GPIO16 |
| MicroSD | GPIO21 | — |

> Keep every inactive CS/CSN line HIGH. The nRF24L01 and CC1101 must be powered from 3.3 V.

## Complete pin map

### ILI9341 display

| Display pin | ESP32-S3 |
| --- | ---: |
| VCC | 3.3 V |
| GND | GND |
| CS | GPIO4 |
| RST | GPIO15 |
| DC | GPIO8 |
| MOSI | GPIO7 |
| SCK | GPIO6 |
| MISO | GPIO5 |
| LED / BL | 3.3 V |
| Touch | Not connected |

### CC1101

| CC1101 pin | ESP32-S3 |
| --- | ---: |
| VCC | 3.3 V |
| GND | GND |
| SCK | GPIO12 |
| MOSI | GPIO11 |
| MISO | GPIO13 |
| CSN | GPIO10 |
| GDO0 | GPIO9 |
| GDO2 | Not connected |

### nRF24L01

| nRF24L01 pin | ESP32-S3 |
| --- | ---: |
| VCC | 3.3 V |
| GND | GND |
| CE | GPIO16 |
| CSN | GPIO17 |
| SCK | GPIO12 |
| MOSI | GPIO11 |
| MISO | GPIO13 |
| IRQ | Not connected |

### MicroSD

| MicroSD pin | ESP32-S3 |
| --- | ---: |
| VCC | 3.3 V* |
| GND | GND |
| CS | GPIO21 |
| SCK / CLK | GPIO12 |
| MOSI / DI | GPIO11 |
| MISO / DO | GPIO13 |

\*Check the voltage requirements of the exact MicroSD breakout. Data signals must be safe for 3.3 V logic. FAT32 cards from 8 GB to 32 GB are recommended.

### PN532 (I2C mode)

| PN532 pin | ESP32-S3 |
| --- | ---: |
| VCC | 3.3 V |
| GND | GND |
| SDA | GPIO1 |
| SCL | GPIO2 |

Set the module switches or jumpers to I2C mode.

### NEO-M7 GPS

| GPS pin | ESP32-S3 |
| --- | ---: |
| VCC | 5 V |
| GND | GND |
| TXD | GPIO40 (ESP RX) |
| RXD | GPIO41 (ESP TX) |

Default baud rate: `9600`.

### Infrared

| Module pin | ESP32-S3 |
| --- | ---: |
| IR transmitter VCC | 5 V |
| IR transmitter DATA | GPIO18 |
| IR receiver VCC | 3.3 V |
| IR receiver OUT | GPIO42 |
| Grounds | GND |

The 5 V transmitter connection assumes a breakout with its own driver transistor and resistor. Do not drive a bare IR LED directly from a GPIO.

### Buttons

Both buttons connect between the GPIO and GND and use internal pull-ups.

| Action | Connection |
| --- | --- |
| Next | GPIO38 to button to GND |
| Select | Short press on GPIO39 |
| Back | Hold GPIO39 for 800 ms |

## Supported functions

The custom hardware provides the interfaces required by the corresponding Bruce menus:

- Wi-Fi and Bluetooth functions provided by the ESP32-S3
- CC1101 Sub-GHz scanning, receiving, transmitting, spectrum, and saved signals
- nRF24L01 tools and 2.4 GHz spectrum functions
- PN532 NFC tag reading and writing
- GPS tracking and location-based logging
- IR capture, replay, and supported protocol transmission
- LittleFS and MicroSD file storage

Availability can depend on the Bruce version, module variant, antenna, regional radio rules, and stored configuration.

## Build

1. Install [Visual Studio Code](https://code.visualstudio.com/) and [PlatformIO](https://platformio.org/).
2. Clone this repository.
3. Open the repository folder in VS Code.
4. Select the PlatformIO environment `esp32s3-dilen`.
5. Build the project.

```bash
pio run -e esp32s3-dilen
```

The project build scripts generate a merged firmware image named `Bruce-esp32s3-dilen.bin` in the repository root.

See [CUSTOM_HARDWARE.md](CUSTOM_HARDWARE.md) for the compact hardware reference and [FLASH_INSTRUCTIONS_HE.md](FLASH_INSTRUCTIONS_HE.md) for existing Hebrew flashing notes.

## Important release note

Do not use an older prebuilt binary after changing the GPS, IR, or MicroSD pin mapping. Build a fresh image from the current source and publish its SHA-256 checksum together with the release.

## Responsible use

Bruce contains security testing and radio tools. Use this firmware only on equipment, networks, signals, and systems you own or are explicitly authorized to test. Follow local radio, privacy, computer-security, and spectrum regulations.

## Upstream and credits

- Original project: [Bruce firmware](https://github.com/BruceDevices/firmware)
- Bruce website: [bruce.computer](https://bruce.computer/)
- Upstream authors and contributors retain credit for the original project and code.
- Custom board integration and physical build: Dilen Gershon

For the full upstream feature overview and contributor list, see [UPSTREAM_README.md](UPSTREAM_README.md).

## License

This modified source remains licensed under the [GNU Affero General Public License v3.0](LICENSE), consistent with the upstream Bruce project. When distributing binaries, provide the corresponding source and preserve the license and attribution notices.
