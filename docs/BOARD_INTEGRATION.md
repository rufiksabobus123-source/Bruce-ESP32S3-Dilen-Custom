# Custom board integration

## Source entry points

| File | Responsibility |
| --- | --- |
| `boards/ESP32S3-Dilen/ESP32S3-Dilen.ini` | PlatformIO environment, board selection, memory settings, build flags |
| `boards/ESP32S3-Dilen/pins_arduino.h` | Peripheral pins, display settings, and navigation aliases |
| `boards/ESP32S3-Dilen/interface.cpp` | Board initialization, button handling, and configuration migration |
| `boards/_boards_json/esp32s3-dilen.json` | N16R8 board definition |

The display bus uses SCK 6, MOSI 7, and MISO 5. The peripheral bus uses SCK 12, MOSI 11, and MISO 13. The two buses serve different device groups; the CC1101, nRF24L01, and MicroSD intentionally share the second bus.

Each shared-bus peripheral has its own selection line. The nRF24L01 CE pin controls radio operation and is separate from its CSN line. The CC1101 GDO0 pin is a separate signaling line.

## Configuration and navigation

The custom interface uses a persistent `/.dilen-hw-r2` marker for one-time hardware configuration migration. Later user changes should be checked against active settings instead of assuming compile-time defaults always override stored configuration.

The action button uses an 800 ms long-press threshold. A short press selects and a long press navigates back; the other button advances selection.

## Attribution boundary

The portfolio contribution is the physical build, hardware mapping, board target, configuration integration, and navigation adaptation. Bruce's menus, protocol implementations, and general firmware architecture remain upstream work. This repository preserves the upstream license and README.
