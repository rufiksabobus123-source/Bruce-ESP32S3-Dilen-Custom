# Dilen ESP32-S3 N16R8 custom Bruce 1.15-r2 target

PlatformIO environment: `esp32s3-dilen`

## Display (ILI9341, 240 x 320, no touch)

| Display pin | ESP32-S3 |
| --- | --- |
| VCC | 3V3 |
| GND | GND |
| CS | GPIO4 |
| RESET | GPIO15 |
| DC/RS | GPIO8 |
| MOSI/SDI | GPIO7 |
| SCK/CLK | GPIO6 |
| MISO/SDO | GPIO5 |
| LED/BL | 3V3 |

The XPT2046 touch pins are intentionally left disconnected.

## Buttons

Both buttons connect between the GPIO and GND. Internal pull-ups are enabled.

| Function | ESP32-S3 |
| --- | --- |
| Next | GPIO38 |
| Select (short press) / Back (800 ms hold) | GPIO39 |

## GPS (NEO-M7, UART at 9600 baud)

| GPS pin | ESP32-S3 |
| --- | --- |
| VCC | 5V |
| GND | GND |
| TXD | GPIO40 (ESP RX) |
| RXD | GPIO41 (ESP TX) |

## PN532 (I2C mode)

| PN532 pin | ESP32-S3 |
| --- | --- |
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO1 |
| SCL | GPIO2 |

Set the PN532 module switches or jumpers to I2C mode.

## Infrared

| Module signal | ESP32-S3 |
| --- | --- |
| IR transmitter DATA / IN / S | GPIO18 |
| IR transmitter VCC | 5V |
| IR receiver OUT / DATA | GPIO42 |
| IR receiver VCC | 3V3 |
| Both module grounds | GND |

## Shared SPI bus: CC1101 + nRF24L01 + MicroSD

All three peripherals share the same clock and data lines. Each peripheral has
its own chip-select, so firmware must keep the other two chip-select lines HIGH
while communicating with one device.

| Signal | ESP32-S3 |
| --- | --- |
| SCK | GPIO12 |
| MISO | GPIO13 |
| MOSI | GPIO11 |

### Chip-select lines

| Peripheral | Chip-select | Additional signal |
| --- | --- | --- |
| CC1101 | GPIO10 | GDO0 = GPIO9 |
| nRF24L01 | GPIO17 | CE = GPIO16 |
| MicroSD | GPIO21 | — |

### CC1101

| Signal | ESP32-S3 |
| --- | --- |
| CSN | GPIO10 |
| GDO0 | GPIO9 |
| VCC | 3V3 |
| GND | GND |

### nRF24L01

| Signal | ESP32-S3 |
| --- | --- |
| CSN | GPIO17 |
| CE | GPIO16 |
| VCC | 3V3 |
| GND | GND |

### MicroSD

| Signal | ESP32-S3 |
| --- | --- |
| CS | GPIO21 |
| SCK / CLK | GPIO12 |
| MOSI / DI / CMD | GPIO11 |
| MISO / DO / DAT0 | GPIO13 |
| VCC | 3V3 |
| GND | GND |

Use a FAT32-formatted card. An 8-32 GB card is recommended.

## Firmware behavior in r2

- The supplied full-flash image starts with `Config -> Dev Mode` enabled.
- The supplied image replaces the Bruce settings filesystem, removing radio-pin settings left by an older CYD installation.
- The custom source target also keeps `Config -> Dev Mode` visible, contains a one-time CYD radio-pin migration, and prints the active radio mapping on Serial for future rebuilds.
- Later pin changes made in Dev Mode are saved normally and are not overwritten on following boots.

## Build

Open the project in VS Code with PlatformIO and build the `esp32s3-dilen` environment.
The merged flash image is generated as `Bruce-esp32s3-dilen.bin` in the project root.
