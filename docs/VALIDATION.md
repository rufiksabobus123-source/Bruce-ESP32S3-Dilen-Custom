# Build and validation notes

## What this repository establishes

The source includes a custom environment and a matching pin header. The documentation's SPI, UART, I2C, button, and infrared assignments were compared with the custom board files during the maintenance review. The review is not a full firmware audit and does not validate all upstream modules.

## Build evidence to capture

Build with `pio run -e esp32s3-dilen`. Record the source commit, PlatformIO/core versions, build log, resulting binary size, and SHA-256 checksum. A successful compile is distinct from a hardware acceptance run.

No fresh full-firmware build or hardware acceptance was performed during this documentation update. Do not label a historical binary as the current release without matching its source revision.

## Hardware acceptance record

When documenting the next hardware run, capture:

| Subsystem | Evidence to record |
| --- | --- |
| Display and buttons | Startup display, next/select/back behavior |
| Shared SPI | Detection of each module individually and with all three connected |
| MicroSD | File listing plus write/read verification |
| PN532 | Detection and reading of an owned test tag |
| GPS | UART output and a valid outdoor fix |
| Infrared | Capture and replay with an owned remote/device |
| Power | Supply voltage under the combined load |

A front/back photo, a wiring overview, and a brief demonstration video would complete the presentation of the physical build. They are not currently in this repository.
