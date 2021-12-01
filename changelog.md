## MySQL_MariaDB_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/MySQL_MariaDB_Generic.svg?)](https://www.ardu-badge.com/MySQL_MariaDB_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/MySQL_MariaDB_Generic.svg)](https://github.com/khoih-prog/MySQL_MariaDB_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/MySQL_MariaDB_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/MySQL_MariaDB_Generic.svg)](http://github.com/khoih-prog/MySQL_MariaDB_Generic/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Release v1.5.2](#release-v152)
  * [Release v1.5.1](#release-v151)
  * [Major Release v1.5.0](#major-release-v150)
  * [Major Release v1.4.0](#major-release-v140)
  * [Release v1.3.1](#release-v131)
  * [Release v1.3.0](#release-v130)
  * [Release v1.2.0](#release-v120)
  * [Major Release v1.1.0](#major-release-v110)
  * [Release v1.0.3](#release-v103)
  * [Release v1.0.2](#release-v102)
  * [Release v1.0.1](#release-v101)
  * [Release v1.0.0](#release-v100)

---
---

## Changelog

### Release v1.5.2

1. Auto detect ESP32 core version.
2. Fix bug in examples for WT32_ETH01
3. Update `Packages' Patches`

### Release v1.5.1

1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
2. Update `Packages' Patches`

### Major Release v1.5.0

1. Add support to **Portenta_H7**, using either WiFi or Vision-shield Ethernet
2. Add examples with new features

### Major Release v1.4.0

1. Add support to [QNEthernet Library](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet
2. Fix bug in non-blocking connection
3. Add new feature to permit using either server's hostname, such as `your_account.duckdns.org`, or server's IPAddress, such as IPAddress(192,168,2,112)
4. Update examples with new features, bug-fixes, etc.

### Release v1.3.1

1. Remove unnecessary SPI-bus code in NativeEthernet examples

### Release v1.3.0

1. Add support to **Teensy 4.1 using NativeEthernet**

### Release v1.2.0

1. Add support to WT32_ETH01 (ESP32 + LAN8720A)

### Major Release v1.1.0

1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** v1.8.0+ core](https://github.com/earlephilhower/arduino-pico).
2. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** v2.1.0+ core](https://github.com/arduino/ArduinoCore-mbed).
3. Add support to new **ESP32-S2** boards (**Arduino ESP32C3_DEV**). Check [HOWTO Install esp32 core for ESP32-S2 (Saola, AI-Thinker ESP-12K) and ESP32-C3 boards into Arduino IDE](#howto-install-esp32-core-for-esp32-s2-saola-ai-thinker-esp-12k-and-esp32-c3-boards-into-arduino-ide).
4. Verify working with new ESP8266 core v3.0.0 and new ESP32 core v1.0.6
5. Suppress all warnings possible.
6. Add Table of Contents and Version String

### Release v1.0.3

 1. Add support to ENC28J60 Ethernet module/shield using new **EthernetENC** library.
 2. Update Platform.ini to support PlatformIO 5.x owner-based dependency declaration.
 3. Enhance examples

#### Release v1.0.2

 1. Fix crashing bug when Client timeout. 
 2. Make code more error-proof.
 3. Drop support to ESP8266_AT_Webserver.
 4. Enhance examples

#### Release v1.0.1

 1. Add support to ENC28J60 Ethernet module/shield using **UIPEthernet** library.
 2. Fix bugs
 3. Optimize code
 4. Enhance examples
 5. Add UIPEthernet Library Patches for SAMD21/SAMD51

#### Release v1.0.0

 1. Add support to **nRF52** boards, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 2. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**
 3. Add support to **Adafruit SAMD21 Itsy-Bitsy M0, Feathr M0, Metro M0, AdaFruit CIRCUITPLAYGROUND_EXPRESS, etc.)**
 4. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**
 5. Add support to all **STM32F/L/H/G/WB/MP1 (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.)**
 6. Add support to **Seeeduino SAMD21/SAMD51 boards (SEEED_WIO_TERMINAL, SEEED_FEMTO_M0, SEEED_XIAO_M0, Wio_Lite_MG126, WIO_GPS_BOARD, SEEEDUINO_ZERO, SEEEDUINO_LORAWAN, SEEED_GROVE_UI_WIRELESS, etc.)**
 7. Add support to **SAM DUE and AVR Mega** boards.
 8. Add support to **ESP32/ESP8266** boards.
 9. Add connectNonBlocking() function to use in loop() to avoid being blocked running other tasks. 
10. Add support to WiFiNINA using [**WiFiNINA_Generic library**](https://github.com/khoih-prog/WiFiNINA_Generic) or WiFiNINA library.
11. Add support to W5x00 Ethernet module/shield using Ethernet, EthernetLarge, Ethernet2 or Ethernet3 library.
12. Add support to LAN8742A Ethernet module/shield using STM32Ethernet library.
13. Add support to ESP8266/ESP32-AT-command module/shield using [`WiFiEspAT library`](https://github.com/jandrassy/WiFiEspAT) or [`ESP8266_AT_WebServer library`](https://github.com/khoih-prog/ESP8266_AT_WebServer).
14. Add Packages' Patches.
15. Add sample Packages_Patches for **STM32F/L/H/G/WB/MP1** (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8)
16. Add Ethernet Library Patches
17. Add many examples


