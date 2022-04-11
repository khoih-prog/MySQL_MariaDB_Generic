## MySQL_MariaDB_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/MySQL_MariaDB_Generic.svg?)](https://www.ardu-badge.com/MySQL_MariaDB_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/MySQL_MariaDB_Generic.svg)](https://github.com/khoih-prog/MySQL_MariaDB_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/MySQL_MariaDB_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/MySQL_MariaDB_Generic.svg)](http://github.com/khoih-prog/MySQL_MariaDB_Generic/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Important Change from v1.7.0](#Important-Change-from-v170)
* [Why do we need this MySQL_MariaDB_Generic library](#why-do-we-need-this-mysql_mariadb_generic-library)
  * [Features](#features)
  * [Currently supported Boards](#currently-supported-boards)
  * [Currently supported WiFi shields/modules](#currently-supported-wifi-shieldsmodules)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error) 
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error)
  * [8. For fixing ESP8266 compile error](#8-for-fixing-esp8266-compile-error)
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Important Notes](#important-notes)
* [Basic Usage](#basic-usage)
  * [ 1. To use Ethernet module/shield](#1-to-use-ethernet-moduleshield)
  * [ 2. To use WiFi module/shield](#2-to-use-wifi-moduleshield)
  * [ 3. To use WiFiNINA module/shield](#3-to-use-wifinina-moduleshield)
* [Examples](#examples)
  * [For Ethernet module/shield](#for-ethernet-moduleshield)
  * [For WiFi module/shield](#for-wifi-moduleshield)
  * [For WiFiNINA module/shield](#for-wifinina-moduleshield)
  * [For WT32_ETH01](#for-wt32_eth01)
  * [For Teensy 4.1 NativeEthernet](#for-teensy-41-nativeethernet)
  * [For Teensy 4.1 QNEthernet](#for-teensy-41-qnethernet)
  * [For Portenta_H7 Ethernet](#For-Portenta_H7-Ethernet)
  * [For Portenta_H7 WiFi](#For-Portenta_H7-WiFi)
* [Example Basic_Select](#example-Basic_Select)
  * [1. File Basic_Select.ino](#1-file-Basic_Selectino)
  * [2. File defines.h](#2-file-definesh)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. Query_Progmem on NRF52840_FEATHER using W5x00/Ethernet_Generic Library](#1-query_progmem-on-nrf52840_feather-using-w5x00Ethernet_Generic-library) 
  * [ 2. Complex_Select on NUCLEO_F767ZI using LAN8742A/STM32Ethernet Library](#2-complex_select-on-nucleo_f767zi-using-lan8742astm32ethernet-library)
  * [ 3. Query_Results_WiFi on ITSYBITSY_M4](#3-query_results_wifi-on-itsybitsy_m4) 
  * [ 4. Basic_Select_WiFi on SEEED_XIAO_M0](#4-basic_select_wifi-on-seeed_xiao_m0)
  * [ 5. Query_Results_WiFiNINA on SAMD_NANO_33_IOT](#5-query_results_wifinina-on-samd_nano_33_iot) 
  * [ 6. Connect_By_Hostname on SAM DUE using W5x00/Ethernet_Generic Library](#6-connect_by_hostname-on-sam-due-using-w5x00Ethernet_Generic-library)
  * [ 7. Complex_Select on NRF52840_FEATHER using ENC28J60/UIPEthernet Library](#7-complex_select-on-nrf52840_feather-using-enc28j60uipethernet-library) 
  * [ 8. Complex_Select on NRF52840_FEATHER using ENC28J60/EthernetENC Library](#8-complex_select-on-nrf52840_feather-using-enc28j60ethernetenc-library)
  * [ 9. Query_Progmem on NRF52840_FEATHER using ENC28J60/EthernetENC Library](#9-query_progmem-on-nrf52840_feather-using-enc28j60ethernetenc-library) 
  * [10. Basic_Insert_ESP on ESP8266_NODEMCU_ESP12E](#10-basic_insert_esp-on-esp8266_nodemcu_esp12e)
  * [11. Basic_Insert_ESP on ESP32S2_DEV](#11-basic_insert_esp-on-esp32s2_dev)
  * [12. Basic_Select_WiFiNINA on MBED NANO_RP2040_CONNECT](#12-basic_select_wifinina-on-mbed-nano_rp2040_connect)
  * [13. Complex_Select on MBED RASPBERRY_PI_PICO using W5x00/Ethernet_Generic Library](#13-complex_select-on-mbed-raspberry_pi_pico-using-w5x00Ethernet_Generic-library) 
  * [14. Complex_Select on RASPBERRY_PI_PICO using W5x00/Ethernet_Generic Library](#14-complex_select-on-raspberry_pi_pico-using-w5x00Ethernet_Generic-library)
  * [15. Complex_Select_WT32_ETH01 on WT32-ETH01](#15-complex_select_wt32_eth01-on-wt32-eth01)
  * [16. Complex_Select on Teensy 4.1 with NativeEthernet](#16-complex_select-on-teensy-41-with-nativeethernet)
  * [17. Complex_Select on Teensy 4.1 with QNEthernet](#17-complex_select-on-teensy-41-with-qnethernet)
  * [18. Complex_Insert on PORTENTA_H7_M7 using Portenta_Ethernet](#18-Complex_Insert-on-PORTENTA_H7_M7-using-Portenta_Ethernet)
  * [19. Complex_Select_WiFi on PORTENTA_H7_M7](#19-Complex_Select_WiFi-on-PORTENTA_H7_M7)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Change from v1.7.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)


---
---

### Why do we need this [MySQL_MariaDB_Generic library](https://github.com/khoih-prog/MySQL_MariaDB_Generic)

#### Features

Have you ever wanted to connect your Arduino project to a database to either store the data you've collected or retrieve data saved to trigger events in your sketch? 

Well, now you can connect your Arduino project directly to a **MySQL / MariaDB server** without using an intermediate computer or a web-based or cloud-based service. Having direct access to a **MySQL / MariaDB database server** means you can store data acquired from your project as well as check values stored in tables on the server.

This also means you can setup your own, local MySQL server to store your data further removing the need for Internet connectivity. If that is not an issue, you can still connect to and store data on a MySQL server via your network, Internet, or even in the cloud!

This [**MySQL_MariaDB_Generic library**](https://github.com/khoih-prog/MySQL_MariaDB_Generic) will let you to do exactly that and more!

This [**MySQL_MariaDB_Generic library**](https://github.com/khoih-prog/MySQL_MariaDB_Generic) is based on and modified from [**Dr. Charles Bell's MySQL_Connector_Arduino Library**](https://github.com/ChuckBell/MySQL_Connector_Arduino), to provide support to many more boards and shields, such as **Arduino SAMD21, Adafruit SAMD21/SAMD51, Seeeduino SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1, Teensy, SAM DUE, AVR Mega, RP2040-based (Nano RP2040 Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040), Portenta_H7, etc. boards**. Those supported boards can be used with **ESP8266/ESP32’s WiFi, WiFiNINA, W5x00/ENC28J60/LAN8742A Ethernet, ESP8266/ESP32-AT, NativeEthernet/QNEthernet modules/shields, Portenta_H7 WiFi/Ethernet.**

---

#### Currently supported Boards

This [**MySQL_MariaDB_Generic** library](https://github.com/khoih-prog/MySQL_MariaDB_Generic) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 
 2. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 3. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 4. **SAM DUE** 
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0)** using either Ethernet, WiFi, or for Teensy 4.1 NativeEthernet/QNEthernet 
 6. **STM32F/L/H/G/WB/MP1 boards (with 32+K Flash)**
  - Nucleo-144
  - Nucleo-64
  - Discovery
  - Generic STM32F0, STM32F1, STM32F2, STM32F3, STM32F4, STM32F7 (with 64+K Flash): x8 and up
  - STM32L0, STM32L1, STM32L4, STM32L5
  - STM32G0, STM32G4
  - STM32H7
  - STM32WB
  - STM32MP1
  - LoRa boards
  - 3-D printer boards
  - Generic Flight Controllers
  - Midatronics boards

 7. **ESP32**
 8. **ESP8266**
 
 9. RP2040-based boards, such as **Nano_RP2040_Connect**, using [**Arduino mbed OS for Nano boards**](https://github.com/arduino/ArduinoCore-mbed).

10. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).

11. RP2040-based boards, such as **Seeed XIAO RP2040**, using **Seeeduino RP2040** core

12. **WT32_ETH01 (ESP32 + LAN8720A)**

13. **Portenta_H7** using either `Murata WiFi` or `Vision-shield Ethernet`

---

#### Currently supported WiFi shields/modules

1. WiFiNINA using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
2. WiFi101 using [`WiFi101 library`](https://github.com/arduino-libraries/WiFi101)
3. u-blox W101, W102 using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
4. ESP8266-AT command using [`WiFiEspAT library`](https://github.com/jandrassy/WiFiEspAT)
5. ESP8266/ESP32-AT command using [`ESP_AT_Lib library`](https://github.com/khoih-prog/ESP_AT_Lib)
6. **Portenta_H7 built-in Murata WiFi**


---

#### Currently supported Ethernet shields/modules

1. W5x00 using [`Ethernet_Generic`](https://github.com/khoih-prog/Ethernet_Generic) library
2. W5x00 using [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge), [`Ethernet2`](https://github.com/adafruit/Ethernet2) or [`Ethernet3`](https://github.com/sstaub/Ethernet3) library
3. ENC28J60 using [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
4. Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library
5. Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library
6. Portenta_H7 Ethernet using [`Portenta_Ethernet`](https://github.com/arduino/ArduinoCore-mbed/tree/master/libraries/Ethernet) library
  
<p align="center">
    <img src="https://github.com/khoih-prog/MySQL_MariaDB_Generic/blob/master/pics/Portenta_Vision.jpg">
</p>


---
---

 
## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`ESP32 Core 2.0.2+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
 3. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/).
 4. [`Arduino AVR core 1.8.5+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) for AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 5. [`Teensy core v1.56+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 6. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 7. [`Arduino SAMD core 1.8.13+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 8. [`Adafruit SAMD core 1.7.10+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 9. [`Fab_SAM_Arduino core v1.16.18-alpha2+`](https://github.com/qbolsee/ArduinoCore-fab-sam) for SAMD21/SAMD51 boards. [![GitHub release](https://img.shields.io/github/release/qbolsee/ArduinoCore-fab-sam.svg)](https://github.com/qbolsee/ArduinoCore-fab-sam/releases/latest)
10. [`Seeeduino SAMD core 1.8.2+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
11. [`Seeeduino RP2040 core 2.7.2+`](https://github.com/Seeed-Studio) for XIAO RP2040 boards. 
12. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
13. [`Arduino Core for STM32 v2.2.0+`](https://github.com/stm32duino/Arduino_Core_STM32) for STM32F/L/H/G/WB/MP1 boards. [![GitHub release](https://img.shields.io/github/release/stm32duino/Arduino_Core_STM32.svg)](https://github.com/stm32duino/Arduino_Core_STM32/releases/latest)
14. [`Earle Philhower's arduino-pico core v1.13.1+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
15. [`Arduino mbed_rp2040 core 3.0.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) RP2040-based boards, such as RASPBERRY_PI_PICO. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)


16. [`WiFiNINA_Generic library v1.8.14-3+`](https://github.com/khoih-prog/WiFiNINA_Generic) for WiFiNINA. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic).

17. Depending on which Ethernet module/shield you're using :
   - [`Ethernet_Generic library v2.0.1+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
   - [`EthernetENC library v2.0.2+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.11+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
   - [`STM32Ethernet library v1.2.0+`](https://github.com/stm32duino/STM32Ethernet) for built-in LAN8742A Ethernet on (Nucleo-144, Discovery). [![GitHub release](https://img.shields.io/github/release/stm32duino/STM32Ethernet.svg)](https://github.com/stm32duino/STM32Ethernet/releases/latest). To be used with [`LwIP library v2.1.2+`](https://github.com/stm32duino/LwIP). [![GitHub release](https://img.shields.io/github/release/stm32duino/LwIP.svg)](https://github.com/stm32duino/LwIP/releases/latest)
   - [`NativeEthernetLarge library stable111+`](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1 built-in Ethernet.
   - [`QNEthernet Library version v0.14.0+`](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet. **New**
   
18. [`WiFiEspAT library v1.3.2+`](https://github.com/jandrassy/WiFiEspAT) if necessary to use ESP8288/ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiEspAT.svg?)](https://www.ardu-badge.com/WiFiEspAT).
19. [`ESP8266_AT_WebServer library v1.5.3+`](https://github.com/khoih-prog/ESP8266_AT_WebServer) if necessary to use ESP8288/ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP8266_AT_WebServer.svg?)](https://www.ardu-badge.com/ESP8266_AT_WebServer).
20. [`ESP_AT_Lib library v1.4.1+`](https://github.com/khoih-prog/ESP_AT_Lib) if necessary to use ESP8288/ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_Lib.svg?)](https://www.ardu-badge.com/ESP_AT_Lib).
21. [`WebServer_WT32_ETH01 library v1.4.1+`](https://github.com/khoih-prog/WebServer_WT32_ETH01) to use WT32_ETH01 (ESP32 + LAN8720). To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WebServer_WT32_ETH01.svg?)](https://www.ardu-badge.com/WebServer_WT32_ETH01).

---
---

## Installation

### Use Arduino Library Manager
The best and easiest way is to use `Arduino Library Manager`. Search for `MySQL_MariaDB_Generic`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/MySQL_MariaDB_Generic.svg?)](https://www.ardu-badge.com/MySQL_MariaDB_Generic) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**MySQL_MariaDB_Generic**](https://github.com/khoih-prog/MySQL_MariaDB_Generic) page.
2. Download the latest release `MySQL_MariaDB_Generic-master.zip`.
3. Extract the zip file to `MySQL_MariaDB_Generic-master` directory 
4. Copy whole `MySQL_MariaDB_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**MySQL_MariaDB_Generic** library](https://registry.platformio.org/libraries/khoih-prog/MySQL_MariaDB_Generic) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/MySQL_MariaDB_Generic/installation). Search for **MySQL_MariaDB_Generic** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)


---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "MySQL_Generic.hpp"     //https://github.com/khoih-prog/MySQL_Generic
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "MySQL_Generic.h"           //https://github.com/khoih-prog/MySQL_Generic
```

Check the new [**multiFileProject_Ethernet** example](examples/Ethernet/multiFileProject_Ethernet) for a `HOWTO` demo.

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)



---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.9) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.9). 

Supposing the Adafruit SAMD core version is 1.7.9. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.9/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2). 

Supposing the Seeeduino SAMD core version is 1.8.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.2.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.0.0/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.0/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.0
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.0.0. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.0/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.2. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/arduino/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.6.18-alpha2. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino SAMD core version is 2.7.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`


---
---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.12/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

#### 8. For fixing ESP8266 compile error

To fix `ESP8266 compile error` such as

```
error: 'class EthernetClass' has no member named 'init'
Ethernet.init (USE_THIS_SS_PIN);
```

just rename the following file in ./arduino-1.8.13/hardware/esp8266com/esp8266/libraries/Ethernet directory

- From `Ethernet.h` to `Ethernet_ESP8266.h`

---
---


### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).


---
---

### Important Notes

1. From v1.0.0, code is restructured to provide flexibility to make it easy to support many more **WiFi/Ethernet** modules/shields in the future. Please delete the *.cpp files, replaced by *.hpp files, in the src directory, if *.cpp files still exist after installing new version.

2. For **Adafruit nRF52**, use the SPI's pins as follows:

  - SS/CS     = 10
  - SPI_MOSI  = MO(SI)
  - SPI_MISO  = MI(SO)
  - SPI_SCK   = SCK

3. For **Adafruit SAMD21/SAMD51**, use the SPI's CS/SS pin as follows:

  - Itsy-Bitsy M0/M4, Feather M0 (Express), Hallowing M0 Express, Zero, Metro M0 => use CS = 16 = pin A2
  - Feather M4 (SAMD51)   => use SS/CS = 9
  - Grand Central M4      => use SS/CS = 53
  - Hallowing M4          => use SS/CS = 10
  - Metro M4 AirLift      => use SS/CS = 36

To know the default CS/SS pins of not listed boards, check the related `variant.h` files in 

`~/.arduino15/packages/adafruit/hardware/samd/x.y.zz/variants/board_name/variant.h`

4. For **Arduino SAM DUE**, use the SPI's pins as follows:

  - SS/CS     = 10
  - SPI_MOSI  = 75 ( pin 4 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_MISO  = 74 ( pin 1 @ [ICSP connector](pics/ICSP_connector.jpg) )
  - SPI_SCK   = 76  ( pin 3 @ [ICSP connector](pics/ICSP_connector.jpg) )
  
<p align="center">
    <img src="https://github.com/khoih-prog/MySQL_MariaDB_Generic/blob/master/pics/ICSP_connector.jpg">
</p>
  
5. For **RP2040**, use the SPI's pins as follows:

  - SS/CS = GP17 default or GP5 by modifying `defines.h`
  - MOSI  = GP19
  - MISO  = GP16
  - SCK   = GP18
  
<p align="center">
    <img src="https://github.com/khoih-prog/MySQL_MariaDB_Generic/blob/master/pics/RP2040-Pinout.png">
</p>
  
    
---
---

## Basic Usage

Please see [Dr. Charles Bell's wiki documentation](https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki), especially [Examples section](https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki/Examples) for the best and detailed explanation.

There are many modifications to facilitate the usage of [**MySQL_MariaDB_Generic Library**](https://github.com/khoih-prog/MySQL_MariaDB_Generic). Please have a look at the examples to see the differences.

---

### 1. To use Ethernet module/shield

#### Just select an Ethernet module/shield and the corresponding library to use in defines.h:

```c++
// Only one of the following to be true.
#define USE_ETHERNET_GENERIC      true
#define USE_ETHERNET_ESP8266      false
#define USE_ETHERNET_ENC          false
#define USE_ETHERNET_LAN8742A     false
#define USE_ETHERNET_LAN8720      false
#define USE_CUSTOM_ETHERNET       false
#define USE_UIP_ETHERNET          false
```

#### In the sketch:

```c++
#include "defines.h"

#include <MySQL_Generic_Ethernet.h>

...

MySQL_Connection conn((Client *)&client);
MySQL_Query sql_query = MySQL_Query(&conn);
```

---

### 2. To use WiFi module/shield

#### For ESP8266 or ESP32, don't need to select any WiFi module/shield in defines.h.

#### For remaining boards, just select a WiFi module/shield and the corresponding library to use in defines.h:

```c++
// Select only one of these libraries, only for boards other than ESP8266/ESP32
#define USING_WIFI_ESP_AT               false         // Using ESP8266_AT_WebServer lib (https://github.com/khoih-prog/ESP8266_AT_WebServer)
#define USING_WIFININA_GENERIC          false         // Using WiFiNINA_Generic library (https://github.com/khoih-prog/WiFiNINA_Generic)
#define USING_WIFININA                  false         // Using WiFiNINA library
#define USING_WIFIESPAT_LIB             true          // Using WiFiEspAT library (https://github.com/jandrassy/WiFiEspAT)
#define USING_WIFI_CUSTOM               false
```

#### In the sketch:

```c++
#include "defines.h"
#include "Credentials.h"

#include <MySQL_Generic_WiFi.h>

...

MySQL_Connection conn((Client *)&client);
MySQL_Query sql_query = MySQL_Query(&conn);
```

---

### 3. To use WiFiNINA module/shield

#### Can't use WiFiNINA for ESP8266 or ESP32.

#### For remaining boards, just select a library to use in defines.h:

```c++
// Select only one of these libraries, only for boards other than ESP8266/ESP32
#define USING_WIFININA_GENERIC        true
#define USING_WIFININA                false
```

#### In the sketch:

```c++
#include "defines.h"
#include "Credentials.h"

#include <MySQL_Generic_WiFiNINA.h>

...

MySQL_Connection conn((Client *)&client);
MySQL_Query sql_query = MySQL_Query(&conn);
```

---
---

### Examples

#### For Ethernet module/shield

 1. [Basic_Insert](examples/Ethernet/Basic_Insert)
 2. [Basic_Select](examples/Ethernet/Basic_Select)
 3. [Complex_Insert](examples/Ethernet/Complex_Insert)
 4. [Complex_Select](examples/Ethernet/Complex_Select)
 5. [Connect](examples/Ethernet/Connect)
 6. [Connect_By_Hostname](examples/Ethernet/Connect_By_Hostname)
 7. [Connect_Default_Database](examples/Ethernet/Connect_Default_Database)
 8. [Connect_Disconnect](examples/Ethernet/Connect_Disconnect)
 9. [Query_Progmem](examples/Ethernet/Query_Progmem)
10. [Query_Results](examples/Ethernet/Query_Results)
11. [multiFileProject_Ethernet](examples/Ethernet/multiFileProject_Ethernet) **New**

#### For WiFi module/shield

 1. [Basic_Insert_ESP](examples/WiFi/Basic_Insert_ESP)
 2. [Basic_Insert_WiFi](examples/WiFi/Basic_Insert_WiFi)
 3. [Basic_Select_WiFi](examples/WiFi/Basic_Select_WiFi)
 4. [Complex_Insert_WiFi](examples/WiFi/Complex_Insert_WiFi)
 5. [Complex_Select_WiFi](examples/WiFi/Complex_Select_WiFi)
 6. [Connect_WiFi](examples/WiFi/Connect_WiFi)
 7. [Connect_Default_Database_WiFi](examples/WiFi/Connect_Default_Database_WiFi)
 8. [Connect_Disconnect_WiFi](examples/WiFi/Connect_Disconnect_WiFi)
 9. [Query_Progmem_WiFi](examples/WiFi/Query_Progmem_WiFi)
10. [Query_Results_WiFi](examples/WiFi/Query_Results_WiFi)
11. [Reboot_WiFi](examples/WiFi/Reboot_WiFi)
12. [multiFileProject_WiFi](examples/WiFi/multiFileProject_WiFi) **New**

#### For WiFiNINA module/shield

 1. [Basic_Insert_WiFiNINA](examples/WiFiNINA/Basic_Insert_WiFiNINA)
 2. [Basic_Select_WiFiNINA](examples/WiFiNINA/Basic_Select_WiFiNINA)
 3. [Complex_Insert_WiFiNINA](examples/WiFiNINA/Complex_Insert_WiFiNINA)
 4. [Complex_Select_WiFiNINA](examples/WiFiNINA/Complex_Select_WiFiNINA)
 5. [Connect_WiFiNINA](examples/WiFiNINA/Connect_WiFiNINA)
 6. [Connect_Default_Database_WiFiNINA](examples/WiFiNINA/Connect_Default_Database_WiFiNINA)
 7. [Connect_Disconnect_WiFiNINA](examples/WiFiNINA/Connect_Disconnect_WiFiNINA)
 8. [Query_Progmem_WiFiNINA](examples/WiFiNINA/Query_Progmem_WiFiNINA)
 9. [Query_Results_WiFiNINA](examples/WiFiNINA/Query_Results_WiFiNINA)
10. [Reboot_WiFiNINA](examples/WiFiNINA/Reboot_WiFiNINA)
11. [multiFileProject_WiFiNINA](examples/WiFiNINA/multiFileProject_WiFiNINA) **New**

#### For WT32_ETH01

 1. [Basic_Insert_WT32_ETH01](examples/WT32_ETH01/Basic_Insert_WT32_ETH01)
 2. [Basic_Select_WT32_ETH01](examples/WT32_ETH01/Basic_Select_WT32_ETH01)
 3. [Complex_Insert_WT32_ETH01](examples/WT32_ETH01/Complex_Insert_WT32_ETH01)
 4. [Complex_Select_WT32_ETH01](examples/WT32_ETH01/Complex_Select_WT32_ETH01)
 5. [Connect_WT32_ETH01](examples/WT32_ETH01/Connect_WT32_ETH01)
 6. [Connect_Default_Database_WT32_ETH01](examples/WT32_ETH01/Connect_Default_Database_WT32_ETH01)
 7. [Connect_Disconnect_WT32_ETH01](examples/WT32_ETH01/Connect_Disconnect_WT32_ETH01)
 8. [Query_Progmem_WT32_ETH01](examples/WT32_ETH01/Query_Progmem_WT32_ETH01)
 9. [Query_Results_WT32_ETH01](examples/WT32_ETH01/Query_Results_WT32_ETH01)
10. [Reboot_WT32_ETH01](examples/WT32_ETH01/Reboot_WT32_ETH01)
11. [multiFileProject_WT32_ETH01](examples/WT32_ETH01/multiFileProject_WT32_ETH01) **New**

#### For Teensy 4.1 NativeEthernet

 1. [Basic_Insert](examples/NativeEthernet/Basic_Insert)
 2. [Basic_Select](examples/NativeEthernet/Basic_Select)
 3. [Complex_Insert](examples/NativeEthernet/Complex_Insert)
 4. [Complex_Select](examples/NativeEthernet/Complex_Select)
 5. [Connect](examples/NativeEthernet/Connect)
 6. [Connect_By_Hostname](examples/NativeEthernet/Connect_By_Hostname)
 7. [Connect_Default_Database](examples/NativeEthernet/Connect_Default_Database)
 8. [Connect_Disconnect](examples/NativeEthernet/Connect_Disconnect)
 9. [Query_Progmem](examples/NativeEthernet/Query_Progmem)
10. [Query_Results](examples/NativeEthernet/Query_Results)
11. [multiFileProject_NativeEthernet](examples/NativeEthernet/multiFileProject_NativeEthernet) **New**

#### For Teensy 4.1 QNEthernet

 1. [Basic_Insert](examples/QNEthernet/Basic_Insert)
 2. [Basic_Select](examples/QNEthernet/Basic_Select)
 3. [Complex_Insert](examples/QNEthernet/Complex_Insert)
 4. [Complex_Select](examples/QNEthernet/Complex_Select)
 5. [Connect](examples/QNEthernet/Connect)
 6. [Connect_By_Hostname](examples/QNEthernet/Connect_By_Hostname)
 7. [Connect_Default_Database](examples/QNEthernet/Connect_Default_Database)
 8. [Connect_Disconnect](examples/QNEthernet/Connect_Disconnect)
 9. [Query_Progmem](examples/QNEthernet/Query_Progmem)
10. [Query_Results](examples/QNEthernet/Query_Results)
11. [multiFileProject_QNEthernet](examples/QNEthernet/multiFileProject_QNEthernet) **New**

#### For Portenta_H7 Ethernet

 1. [Basic_Insert](examples/Portenta_H7/Ethernet/Basic_Insert)
 2. [Basic_Select](examples/Portenta_H7/Ethernet/Basic_Select)
 3. [Complex_Insert](examples/Portenta_H7/Ethernet/Complex_Insert)
 4. [Connect](examples/Portenta_H7/Ethernet/Connect)
 5. [Connect_By_Hostname](examples/Portenta_H7/Ethernet/Connect_By_Hostname)
 6. [Connect_Default_Database](examples/Portenta_H7/Ethernet/Connect_Default_Database)
 7. [multiFileProject_Portenta_H7_Ethernet](examples/Portenta_H7/Ethernet/multiFileProject_Portenta_H7_Ethernet) **New**


#### For Portenta_H7 WiFi

 1. [Basic_Insert_WiFi](examples/Portenta_H7/WiFi/Basic_Insert_WiFi)
 2. [Basic_Select_WiFi](examples/Portenta_H7/WiFi/Basic_Select_WiFi)
 3. [Complex_Insert_WiFi](examples/Portenta_H7/WiFi/Complex_Insert_WiFi)
 4. [Complex_Select_WiFi](examples/Portenta_H7/WiFi/Complex_Select_WiFi)
 5. [Connect_WiFi](examples/Portenta_H7/WiFi/Connect_WiFi)
 6. [Connect_Default_Database_WiFi](examples/Portenta_H7/WiFi/Connect_Default_Database_WiFi)
 7. [Connect_Disconnect_WiFi](examples/Portenta_H7/WiFi/Connect_Disconnect_WiFi)
 8. [Reboot_WiFi](examples/Portenta_H7/WiFi/Reboot_WiFi)
 9. [multiFileProject_Portenta_H7_WiFi](examples/Portenta_H7/WiFi/multiFileProject_Portenta_H7_WiFi) **New**



---
---

### Example [Basic_Select](examples/Ethernet/Basic_Select)

Please take a look at other examples, as well.

#### 1. File [Basic_Select.ino](examples/Ethernet/Basic_Select/Basic_Select.ino)

https://github.com/khoih-prog/MySQL_MariaDB_Generic/blob/78ff2dbda8caaa10266eb93acd286641aba7dd27/examples/Ethernet/Basic_Select/Basic_Select.ino#L50-L326



#### 2. File [defines.h](examples/Ethernet/Basic_Select/defines.h)

https://github.com/khoih-prog/MySQL_MariaDB_Generic/blob/78ff2dbda8caaa10266eb93acd286641aba7dd27/examples/Ethernet/Basic_Select/defines.h#L16-L463


---
---

### Debug Terminal Output Samples

#### 1. Query_Progmem on NRF52840_FEATHER using W5x00/Ethernet_Generic Library

This is terminal debug output when running [Query_Progmem](examples/Ethernet/Query_Progmem) on nRF52 **Adafruit NRF52840_FEATHER using W5500 Ethernet module and Ethernet_Generic library** connecting to MariaDB Server.

```
Starting Query_Progmem on NRF52840_FEATHER using W5x00/Ethernet_Generic Library
MySQL_MariaDB_Generic v1.7.2
Ethernet_Generic W5500 init, using SPI_CS = 10, number of sockets = 4
Using mac index = 10
Connected! IP address: 192.168.2.145
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1

Running SELECT from PROGMEM and printing results

SELECT * FROM world.city LIMIT 12
ID,Name,CountryCode,District,Population
1,Kabul,AFG,Kabol,1780000
2,Qandahar,AFG,Qandahar,237500
3,Herat,AFG,Herat,186800
4,Mazar-e-Sharif,AFG,Balkh,127800
5,Amsterdam,NLD,Noord-Holland,731200
6,Rotterdam,NLD,Zuid-Holland,593321
7,Haag,NLD,Zuid-Holland,440900
8,Utrecht,NLD,Utrecht,234323
9,Eindhoven,NLD,Noord-Brabant,201843
10,Tilburg,NLD,Noord-Brabant,193238
11,Groningen,NLD,Groningen,172701
12,Breda,NLD,Noord-Brabant,160398
12 rows in result.
```

---

#### 2. Complex_Select on NUCLEO_F767ZI using LAN8742A/STM32Ethernet Library

This is terminal debug output when running [Complex_Select](examples/Ethernet/Complex_Select) on STM32F7 **Nucleo-144 NUCLEO_F767ZI using LAN8742A built-in Ethernet and STM32Ethernet library** connecting to MariaDB Server.

```
Starting Complex_Select on NUCLEO_F767ZI using LAN8742A/STM32Ethernet Library
MySQL_MariaDB_Generic v1.7.2
Using mac index = 0
Connected! IP address: 192.168.2.165
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest, DB = world
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 857880 ORDER BY population DESC LIMIT 12;
name,population
Naucalpan de Ju⸮rez,857511
Pikine,855287
Lubumbashi,851381
Monrovia,850000
Freetown,850000
Zaporizzja,848000
Handan,840000
S⸮o Lu⸮s,837588
Wuxi,830000
Ouagadougou,824000
Ciudad de Guatemala,823301
Coimbatore,816321
[SQL] Disconnected

Sleeping...
================================================
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 972170 ORDER BY population DESC LIMIT 12;
name,population
Mekka,965700
K⸮ln,962507
Managua,959000
Detroit,951270
Shenzhen,950500
Haora (Howrah),950435
Campinas,950043
Brazzaville,950000
Khartum,947483
Karaj,940968
Taichung,940589
Santa Cruz de la Sierra,935361
[SQL] Disconnected

Sleeping...
================================================

```

---

#### 3. Query_Results_WiFi on ITSYBITSY_M4

This is terminal debug output when running [Query_Results_WiFi](examples/WiFi/Query_Results_WiFi) on SAMD51 **Adafruit ITSYBITSY_M4 using ESP8266-AT WiFi shield and WiFiEspAT library** connecting to MySQL Server.

```
Starting Query_Results_WiFi on ITSYBITSY_M4
MySQL_MariaDB_Generic v1.7.2
Using WiFiEspAT Library
WiFi shield init done
Connecting to HueNet1
Connected to network. My IP address is: 192.168.2.32
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1

Running SELECT and printing results

SELECT * FROM world.city LIMIT 6
ID, Name, CountryCode, District, Population
1, Kabul, AFG, Kabol, 1780000
2, Qandahar, AFG, Qandahar, 237500
3, Herat, AFG, Herat, 186800
4, Mazar-e-Sharif, AFG, Balkh, 127800
5, Amsterdam, NLD, Noord-Holland, 731200
6, Rotterdam, NLD, Zuid-Holland, 593321
[SQL] Disconnected

Sleeping...
================================================
```

---

#### 4. Basic_Select_WiFi on SEEED_XIAO_M0

This is terminal debug output when running [Basic_Select_WiFi](examples/WiFi/Basic_Select_WiFi) on SAMD21 **Seeeduino SEEED_XIAO_M0 using ESP8266-AT WiFi shield and WiFiEspAT library** connecting to MariaDB Server.


```
Starting Basic_Select_WiFi on SEEED_XIAO_M0
MySQL_MariaDB_Generic v1.7.2
Using WiFiEspAT Library
WiFi shield init done
Connecting to HueNet1
Connected to network. My IP address is: 192.168.2.32
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest, DB = world
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
1) Demonstrating using a dynamically allocated query.
SELECT population FROM world.city WHERE name = 'Toronto'
  Toronto pop = 688275
2) Demonstrating using a local, global query.
SELECT population FROM world.city WHERE name = 'Toronto'
  Toronto pop = 688275
  Toronto pop increased by 11725 = 700000
[SQL] Disconnected

Sleeping...
================================================

```

---

#### 5. Query_Results_WiFiNINA on SAMD_NANO_33_IOT

This is terminal debug output when running [Query_Results_WiFiNINA](examples/WiFiNINA/Query_Results_WiFiNINA) on SAMD21 **Arduino SAMD_NANO_33_IOT using built-in WiFiNINA and WiFiNINA_Generic library** connecting to MariaDB Server.


```
Starting Query_Results_WiFiNINA on SAMD_NANO_33_IOT
MySQL_MariaDB_Generic v1.7.2
Attempting to connect to SSID: HueNet1
SSID: HueNet1
IP Address: 192.168.2.118
signal strength (RSSI):-40 dBm
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1

Running SELECT and printing results

SELECT * FROM world.city LIMIT 12
ID, Name, CountryCode, District, Population
1, Kabul, AFG, Kabol, 1780000
2, Qandahar, AFG, Qandahar, 237500
3, Herat, AFG, Herat, 186800
4, Mazar-e-Sharif, AFG, Balkh, 127800
5, Amsterdam, NLD, Noord-Holland, 731200
6, Rotterdam, NLD, Zuid-Holland, 593321
7, Haag, NLD, Zuid-Holland, 440900
8, Utrecht, NLD, Utrecht, 234323
9, Eindhoven, NLD, Noord-Brabant, 201843
10, Tilburg, NLD, Noord-Brabant, 193238
11, Groningen, NLD, Groningen, 172701
12, Breda, NLD, Noord-Brabant, 160398
[SQL] Disconnected

Sleeping...
================================================

```

---

#### 6. Connect_By_Hostname on SAM DUE using W5x00/Ethernet_Generic Library

This is terminal debug output when running [Connect_By_Hostname](examples/Ethernet/Connect_By_Hostname) on **Arduino SAM DUE using W5100 Ethernet shield and Ethernet_Generic library** connecting to MariaDB Server.


```
Starting Connect_By_Hostname on SAM DUE using W5x00/Ethernet_Generic Library
MySQL_MariaDB_Generic v1.7.2
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5100, SSIZE =4096
Using mac index = 2
Connected! IP address: 192.168.2.177
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
[SQL] Disconnected
```

---

#### 7. Complex_Select on NRF52840_FEATHER using ENC28J60/UIPEthernet Library

This is terminal debug output when running [Complex_Select](examples/Ethernet/Complex_Select) on **NRF52840_FEATHER using ENC28J60 Ethernet shield and UIPEthernet library** connecting to MariaDB Server.


```
Starting Complex_Select on NRF52840_FEATHER using ENC28J60/UIPEthernet Library
MySQL_MariaDB_Generic v1.7.2
ENC28J60_CONTROL_CS =10
SS =5
SPI_MOSI =25
SPI_MISO =24
SPI_SCK =26
Using mac index = 5
Connected! IP address: 192.168.2.161
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest, DB = world
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 885240 ORDER BY population DESC LIMIT 12;
name,population
Port-au-Prince,884472
Mosul,879000
Barquisimeto,877239
Krasnojarsk,875500
Saratov,874000
Shubra al-Khayma,870716
S⸮o Gon⸮alo,869254
Songnam,869094
Chiba,863930
Nova Igua⸮u,862225
Naucalpan de Ju⸮rez,857511
Pikine,855287
[SQL] Disconnected

Sleeping...
================================================
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 1015280 ORDER BY population DESC LIMIT 12;
name,population
Kalyan,1014557
Birmingham,1013000
Rostov-na-Donu,1012700
Odesa,1011000
Perm,1009700
Napoli,1002619
Zapopan,1002239
Amman,1000000
Mogadishu,997000
Volgograd,993400
Sendai,989975
Peshawar,988005
[SQL] Disconnected

Sleeping...
================================================
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 1193330 ORDER BY population DESC LIMIT 12;
name,population
Tabriz,1191043
Dallas,1188580
Bel⸮m,1186926
Multan,1182441
Praha,1181126
Kalookan,1177604
Nanning,1161800
C⸮rdoba,1157507
Samara,1156100
Hyderabad,1151274
Omsk,1148900
Davao,1147116
[SQL] Disconnected

Sleeping...
================================================

```

---

#### 8. Complex_Select on NRF52840_FEATHER using ENC28J60/EthernetENC Library

This is terminal debug output when running [Complex_Select](examples/Ethernet/Complex_Select) on **NRF52840_FEATHER using ENC28J60 Ethernet shield and EthernetENC library** connecting to MariaDB Server.

```
Starting Complex_Select on NRF52840_FEATHER, with ENC28J60 using EthernetENC Library
MySQL_MariaDB_Generic v1.7.2
[SQL] =========================================
[SQL] Default SPI pinout:
[SQL] MOSI: 25
[SQL] MISO: 24
[SQL] SCK: 26
[SQL] SS: 5
[SQL] =========================================
[SQL] Board : NRF52840_FEATHER , setCsPin: 10
[SQL] =========================================
[SQL] Currently Used SPI pinout:
[SQL] MOSI: 25
[SQL] MISO: 24
[SQL] SCK: 26
[SQL] SS: 5
[SQL] =========================================
Using mac index = 15
Connected! IP address: 192.168.2.98
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest, DB = world
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 831690 ORDER BY population DESC LIMIT 12;
name,population
Wuxi,830000
Ouagadougou,824000
Ciudad de Guatemala,823301
Coimbatore,816321
Tegucigalpa,813900
Xuzhou,810000
Bamako,809552
Mbuji-Mayi,806475
Cartagena,805757
Ahvaz,804980
Bengasi,804000
Thane (Thana),803389
[SQL] Disconnected

Sleeping...
================================================
```

---

#### 9. Query_Progmem on NRF52840_FEATHER using ENC28J60/EthernetENC Library

This is terminal debug output when running [Query_Progmem](examples/Ethernet/Query_Progmem) on **NRF52840_FEATHER using ENC28J60 Ethernet shield and EthernetENC library** connecting to MariaDB Server.


```
Starting Query_Progmem on NRF52840_FEATHER, with ENC28J60 using EthernetENC Library
MySQL_MariaDB_Generic v1.7.2
[SQL] =========================================
[SQL] Default SPI pinout:
[SQL] MOSI: 25
[SQL] MISO: 24
[SQL] SCK: 26
[SQL] SS: 5
[SQL] =========================================
[SQL] Board : NRF52840_FEATHER , setCsPin: 10
[SQL] =========================================
[SQL] Currently Used SPI pinout:
[SQL] MOSI: 25
[SQL] MISO: 24
[SQL] SCK: 26
[SQL] SS: 5
[SQL] =========================================
Using mac index = 13
Connected! IP address: 192.168.2.106
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1

Running SELECT from PROGMEM and printing results

SELECT * FROM test_arduino.hello_arduino LIMIT 6
num,message,recorded
351,Hello, Arduino!,2020-08-18 13:52:35
352,Hello, Arduino!,2020-08-18 13:53:42
353,Hello, Arduino!,2020-08-18 13:54:57
354,Hello, Arduino!,2020-08-18 13:56:03
355,Hello, Arduino!,2020-08-18 22:37:21
356,Hello, Arduino!,2020-08-18 22:38:28
6 rows in result.
[SQL] Disconnected

Sleeping...
================================================
```

---

#### 10. Basic_Insert_ESP on ESP8266_NODEMCU_ESP12E

This is terminal debug output when running [Basic_Insert_ESP](examples/WiFi/Basic_Insert_ESP) on **ESP8266_NODEMCU_ESP12E using ESP8266 core v3.0.0** connecting to MariaDB Server.


```
Starting Basic_Insert_ESP on ESP8266_NODEMCU_ESP12E
MySQL_MariaDB_Generic v1.7.2
Connecting to HueNet1
...........Connected to network. My IP address is: 192.168.2.135
Connecting to SQL Server @ your_account.ddns.net , Port = 5698
User = invited-guest , PW = the-invited-guest , DB = test_arduino
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.27-MariaDB-0+deb10u1
INSERT INTO test_arduino.hello_arduino (message) VALUES ('Hello, Arduino!')
Data Inserted.
[SQL] Disconnected

Sleeping...
================================================
```

---

#### 11. Basic_Insert_ESP on ESP32S2_DEV

This is terminal debug output when running [Basic_Insert_ESP](examples/WiFi/Basic_Insert_ESP) on **ESP32S2_DEV using ESP32 core v1.0.6** connecting to MariaDB Server.


```
Starting Basic_Insert_ESP on ESP32S2_DEV
MySQL_MariaDB_Generic v1.7.2
Connecting to HueNet1
.......Connected to network. My IP address is: 192.168.2.190
Connecting to SQL Server @ your_account.ddns.net , Port = 5698
User = invited-guest , PW = the-invited-guest , DB = test_arduino
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.27-MariaDB-0+deb10u1
INSERT INTO test_arduino.hello_arduino (message) VALUES ('Hello, Arduino!')
Data Inserted.
[SQL] Disconnected

Sleeping...
================================================
```

---

#### 12. Basic_Select_WiFiNINA on MBED NANO_RP2040_CONNECT

This is terminal debug output when running [Basic_Select_WiFiNINA](examples/WiFiNINA/Basic_Select_WiFiNINA) on **MBED NANO_RP2040_CONNECT** connecting to MariaDB Server.


```
Starting Basic_Select_WiFiNINA on MBED NANO_RP2040_CONNECT
MySQL_MariaDB_Generic v1.7.2
Attempting to connect to SSID: HueNet1
SSID: HueNet1
IP Address: 192.168.2.153
signal strength (RSSI):-44 dBm
Connecting to SQL Server @ your_account.ddns.net, Port = 5698
User = invited-guest, PW = the-invited-guest, DB = world
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.27-MariaDB-0+deb10u1
1) Demonstrating using a dynamically allocated query.
SELECT population FROM world.city WHERE name = 'Toronto'
  Toronto pop = 688275
2) Demonstrating using a local, global query.
SELECT population FROM world.city WHERE name = 'Toronto'
  Toronto pop = 688275
  Toronto pop increased by 11725 = 700000
[SQL] Disconnected

Sleeping...
================================================
```

---

#### 13. Complex_Select on MBED RASPBERRY_PI_PICO using W5x00/Ethernet_Generic Library

This is terminal debug output when running [Complex_Select](examples/Ethernet/Complex_Select) on **MBED RASPBERRY_PI_PICO, with W5x00 using Ethernet_Generic Library** connecting to MariaDB Server, using [ArduinoCore-mbed mbed_rp2040 core](https://github.com/arduino/ArduinoCore-mbed)


```
Starting Complex_Select on MBED RASPBERRY_PI_PICO , with W5x00 using Ethernet_Generic Library on SPI0/SPI
MySQL_MariaDB_Generic v1.7.2
[SQL] =========================================
[SQL] Default SPI pinout:
[SQL] MOSI: 19
[SQL] MISO: 16
[SQL] SCK: 18
[SQL] SS: 17
[SQL] =========================================
[SQL] RPIPICO setCsPin: 17
[SQL] Currently Used SPI pinout:
[SQL] MOSI: 19
[SQL] MISO: 16
[SQL] SCK: 18
[SQL] SS: 17
[SQL] =========================
Using mac index = 2
Connected! IP address: 192.168.2.92
Connecting to SQL Server @ 192.168.2.112 , Port = 5698
User = invited-guest , PW = the-invited-guest , DB = world
Connecting...
[SQL] Connecting to Server: 192.168.2.112 , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 827440 ORDER BY population DESC LIMIT 12;
name,population
Ouagadougou,824000
Ciudad de Guatemala,823301
Coimbatore,816321
Tegucigalpa,813900
Xuzhou,810000
Bamako,809552
Mbuji-Mayi,806475
Cartagena,805757
Ahvaz,804980
Bengasi,804000
Thane (Thana),803389
L⸮dz,800110
[SQL] Disconnected

Sleeping...
================================================
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.27-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 934480 ORDER BY population DESC LIMIT 12;
name,population
Varanasi (Benares),929270
Patna,917243
Hohhot,916700
Rosario,907718
Voronez,907700
Soweto,904165
Torino,903705
San Jose,894943
Srinagar,892506
Agra,891790
Kampala,890800
Mandalay,885300
[SQL] Disconnected

Sleeping...
================================================
```

---

#### 14. Complex_Select on RASPBERRY_PI_PICO using W5x00/Ethernet_Generic Library

This is terminal debug output when running [Complex_Select](examples/Ethernet/Complex_Select) on **RASPBERRY_PI_PICO, with W5x00 using Ethernet_Generic Library** connecting to MariaDB Server, using [arduino-pico rp2040 core](https://github.com/earlephilhower/arduino-pico)


```
Starting Complex_Select on RASPBERRY_PI_PICO , with W5x00 using Ethernet_Generic Library on SPI1
MySQL_MariaDB_Generic v1.7.2
[SQL] =========================================
[SQL] Default SPI pinout:
[SQL] MOSI: 19
[SQL] MISO: 16
[SQL] SCK: 18
[SQL] SS: 17
[SQL] =========================================
[SQL] RPIPICO setCsPin: 13
[SQL] Currently Used SPI pinout:
[SQL] MOSI: 15
[SQL] MISO: 12
[SQL] SCK: 14
[SQL] SS: 13
[SQL] =========================
Using mac index = 0
Connected! IP address: 192.168.2.172
Connecting to SQL Server @ 192.168.2.112 , Port = 5698
User = invited-guest , PW = the-invited-guest , DB = world
Connecting...
[SQL] Connecting to Server: 192.168.2.112 , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.34-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 900290 ORDER BY population DESC LIMIT 12;
name,population
San Jose,894943
Srinagar,892506
Agra,891790
Kampala,890800
Mandalay,885300
Port-au-Prince,884472
Mosul,879000
Barquisimeto,877239
Krasnojarsk,875500
Saratov,874000
Shubra al-Khayma,870716
S⸮o Gon⸮alo,869254
[SQL] Disconnected

Sleeping...
================================================
```

---

#### 15. Complex_Select_WT32_ETH01 on WT32-ETH01

This is terminal debug output when running [Complex_Select_WT32_ETH01](examples/WT32_ETH01/Complex_Select_WT32_ETH01) on **WT32_ETH01** connecting to MariaDB Server.

```
Starting Complex_Select_WT32_ETH01 on WT32-ETH01
WebServer_WT32_ETH01 v1.4.1
MySQL_MariaDB_Generic v1.7.2
ETH MAC: A8:03:2A:A1:61:73, IPv4: 192.168.2.232
FULL_DUPLEX, 100Mbps
Connected to network. My IP address is: 192.168.2.232
Connecting to SQL Server @ your_account.ddns.net , Port = 5698
User = invited-guest , PW = the-invited-guest , DB = world
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.27-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 848510 ORDER BY population DESC LIMIT 6;
name,population
Zaporizzja,848000
Handan,840000
S⸮o Lu⸮s,837588
Wuxi,830000
Ouagadougou,824000
Ciudad de Guatemala,823301
[SQL] Disconnected

Sleeping...
================================================
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.27-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 962720 ORDER BY population DESC LIMIT 6;
name,population
K⸮ln,962507
Managua,959000
Detroit,951270
Shenzhen,950500
Haora (Howrah),950435
Campinas,950043
[SQL] Disconnected

Sleeping...
================================================
```

---


#### 16. Complex_Select on Teensy 4.1 with NativeEthernet

This is terminal debug output when running [Complex_Select](examples/NativeEthernet/Complex_Select) on **Teensy 4.1 with NativeEthernet** connecting to MariaDB Server.

```
Starting Complex_Select on Teensy 4.1 , with NativeEthernet
MySQL_MariaDB_Generic v1.7.2
Using mac index = 2
Connected! IP address: 192.168.2.86
Connecting to SQL Server @ your_account.ddns.net , Port = 5698
User = invited-guest , PW = the-invited-guest , DB = world
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.29-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 940450 ORDER BY population DESC LIMIT 12;
name,population
Santa Cruz de la Sierra,935361
Varanasi (Benares),929270
Patna,917243
Hohhot,916700
Rosario,907718
Voronez,907700
Soweto,904165
Torino,903705
San Jose,894943
Srinagar,892506
Agra,891790
Kampala,890800
[SQL] Disconnected

Sleeping...
================================================
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.29-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 1054490 ORDER BY population DESC LIMIT 12;
name,population
Shiraz,1053025
Donetsk,1050000
Ludhiana,1042740
Jilin,1040000
Tangshan,1040000
Vadodara (Baroda),1031346
Maputo,1018938
Montr�al,1016376
Kitakyushu,1016264
Kalyan,1014557
Birmingham,1013000
Rostov-na-Donu,1012700
[SQL] Disconnected

Sleeping...
```

---


#### 17. Complex_Select on Teensy 4.1 with QNEthernet

This is terminal debug output when running [Complex_Select](examples/NativeEthernet/Complex_Select) on **Teensy 4.1 using QNEthernet** connecting to MariaDB Server.

```
Starting Complex_Select on TEENSY 4.1 using QNEthernet
MySQL_MariaDB_Generic v1.7.2
=========== USE_QN_ETHERNET ===========
Initialize Ethernet using static IP => Connected! IP address: 192.168.2.222
Connecting to SQL Server @ your_account.ddns.net , Port = 5698
User = invited-guest , PW = the-invited-guest , DB = world
Connecting...
[SQL] Connecting to Server: your_account.ddns.net , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.29-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 837930 ORDER BY population DESC LIMIT 12;
name,population
S�o Lu�s,837588
Wuxi,830000
Ouagadougou,824000
Ciudad de Guatemala,823301
Coimbatore,816321
Tegucigalpa,813900
Xuzhou,810000
Bamako,809552
Mbuji-Mayi,806475
Cartagena,805757
Ahvaz,804980
Bengasi,804000
[SQL] Disconnected

Sleeping...
================================================
```

---


#### 18. Complex_Insert on PORTENTA_H7_M7 using Portenta_Ethernet

This is terminal debug output when running [Complex_Insert](examples/Portenta_H7/Ethernet/Complex_Insert) on **PORTENTA_H7_M7 using Portenta_Ethernet** connecting to MariaDB Server.

```
Starting Complex_Insert on PORTENTA_H7_M7 , with Ethernet using Portenta_Ethernet Library
MySQL_MariaDB_Generic v1.7.2
Using mac index = 14
Connected! IP address: 192.168.2.132
Connecting to SQL Server @ 192.168.2.112 , Port = 5698
User = invited-guest , PW = the-invited-guest
DB = test_arduino , Table = hello_sensor
Connecting...
[SQL] Connecting to Server: 192.168.2.112 , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.29-MariaDB-0+deb10u1
INSERT INTO test_arduino.hello_sensor (message, sensor_num, value) VALUES ('test sensor',24,50.1)
Complex Data Inserted.
[SQL] Disconnected

Sleeping...
================================================
```

---


#### 19. Complex_Select_WiFi on PORTENTA_H7_M7

This is terminal debug output when running [Complex_Insert_WiFi](examples/Portenta_H7/WiFi/Complex_Insert_WiFi) on **TPORTENTA_H7_M7 using Murata WiFi** connecting to MariaDB Server.

```
Starting Complex_Select_WiFi on PORTENTA_H7_M7
MySQL_MariaDB_Generic v1.7.2
Connecting to HueNet1
Connected to network. My IP address is: 192.168.2.130
Connecting to SQL Server @ 192.168.2.112 , Port = 5698
User = invited-guest , PW = the-invited-guest , DB = world
Connecting...
[SQL] Connecting to Server: 192.168.2.112 , Port =  5698
[SQL] Connected. Server Version = 5.5.5-10.3.29-MariaDB-0+deb10u1
====================================================
> Running SELECT with dynamically supplied parameter
SELECT name, population FROM world.city WHERE population < 928790 ORDER BY population DESC LIMIT 6;
name,population
Patna,917243
Hohhot,916700
Rosario,907718
Voronez,907700
Soweto,904165
Torino,903705
[SQL] Disconnected

Sleeping...
================================================
```


---
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _MYSQL_LOGLEVEL_ to 0

```cpp
#define MYSQL_DEBUG_PORT      Serial

// Debug Level from 0 to 4
#define _MYSQL_LOGLEVEL_      1
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---


### Issues ###

Submit issues to: [MySQL_MariaDB_Generic issues](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues)

---
---

### TO DO

 1. Support more boards
 2. Support more non-compatible Ethernet Libraries such as Ethernet_Shield_W5200, EtherCard, EtherSia
 3. Bug fixing.

---

### DONE

 1. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**
 2. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**.
 3. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
 4. Add support to **Seeeduino SAMD21/SAMD51: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, Wio Terminal, Grove UI Wireless, etc.** 
 5. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**.
 6. Add support to **STM32F/L/H/G/WB/MP1.** 
 7. Add support to SAM DUE and AVR Mega.
 8. Add support to ESP32/ESP8266.
 9. Add support to **WiFiNINA** using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic) and WiFiNINA library.
10. Add support to **Ethernet W5x00**, using either [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`Ethernet2`](https://github.com/khoih-prog/Ethernet2), [`Ethernet3`](https://github.com/khoih-prog/Ethernet3) or [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge) library
11. Add support to **ESP8266/ESP32-AT**, using either [`ESP8266_AT_WebServer library`](https://github.com/khoih-prog/ESP8266_AT_WebServer) or [`WiFiEspAT library`](https://github.com/jandrassy/WiFiEspAT) library
12. Add support to **Ethernet LAN8742A**, using [`STM32Ethernet library`](https://github.com/stm32duino/STM32Ethernet) and [`STM32duino_LwIP library`](https://github.com/stm32duino/LwIP).
13. Split each example into several manageable files.
14. Support ENC28J60 using [`UIPEthernet library`](https://github.com/UIPEthernet/UIPEthernet).
15. Support ENC28J60 using [`EthernetENC library`](https://github.com/jandrassy/EthernetENC).
16. Add Table of Contents and Version String
17. Add support to **ESP32-S2 (ESP32-S2 Saola, AI-Thinker ESP-12K, etc.)**
18. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico core**](https://github.com/earlephilhower/arduino-pico) to use LittleFS with or without Blynk/WiFiManager features.
19. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) to use LittleFS with or without Blynk/WiFiManager features.
20. Add support to WT32_ETH01 (ESP32 + LAN8720A)
21. Add support to Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library
22. Add support to Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library
23. Add new feature to permit using either server's hostname, such as `your_account.duckdns.org`, or server's IPAddress, such as IPAddress(192,168,2,112)
24. Add support to **Portenta_H7**, using either `Murata WiFi` or `Vision-shield Ethernet`
25. Optimize library code by using `reference-passing` instead of `value-passing`
26. Fix memory leak and memory management bugs.
27. Add support to SAMD21/SAMD51 boards using [Fab_SAM_Arduino core](https://github.com/qbolsee/ArduinoCore-fab-sam)
28. Add support to RP2040 boards using `Seeed RP2040 core`
29 Convert to `h-only` style
30. Add `multiFileProject` examples to demo for multiple-file projects
31. Use new [**Ethernet_Generic** library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
32. Support **SPI2 for ESP32**
33. Add support to SPI1 for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
34. Use new function `waitForLink()` for Teensy 4.1 `QNEthernet library v0.14.0+`

---
---

### Contributions and Thanks

1. Based on and modified from [Dr. Charles Bell's MySQL_Connector_Arduino Library](https://github.com/ChuckBell/MySQL_Connector_Arduino)
2. Thanks to good work of [Miguel Alexandre Wisintainer](https://github.com/tcpipchip) for initiating, inspriring, working with, developing, debugging and testing.
3. Thanks to [graham999au](https://github.com/graham999au) for the enhanement request [**NativeEthernet support for Teensy 4.1** #8](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/8), and help testing, leading to new version v1.3.0
4. Thanks to [Pablo Martikian](https://github.com/pabloandresm) to report issues and create bug-fixing PR:

	- [memory leak on 'server_version' #17](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/17)
	- [memory leak on MySQL_Connection.MySQL_Packet.buffer #18](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/18)
	- [corrupt heap at MySQL_Connection destructor #19](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/19)
	- [malloc server_version result not correctly handled may lead to memory corruption #20](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/20)
	- [fix server_version memory management #21](https://github.com/khoih-prog/MySQL_MariaDB_Generic/pull/21)
	- [suggest replacing all files xxxx_Impl.h by xxxx.cpp #22](https://github.com/khoih-prog/MySQL_MariaDB_Generic/issues/22)

leading to version v1.6.0, v1.6.1 and v1.7.0 to fix memory leak / management bugs / `Multiple Definitions` Linker Error.

<table>
  <tr>
    <td align="center"><a href="https://github.com/ChuckBell"><img src="https://github.com/ChuckBell.png" width="100px;" alt="ChuckBell"/><br /><sub><b>⭐️ ChuckBell</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/tcpipchip"><img src="https://github.com/tcpipchip.png" width="100px;" alt="tcpipchip"/><br /><sub><b>Miguel Wisintainer</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/graham999au"><img src="https://github.com/graham999au.png" width="100px;" alt="graham999au"/><br /><sub><b>graham999au</b></sub></a><br /></td>
    <td align="center"><a href="https://github.com/pabloandresm"><img src="https://github.com/pabloandresm.png" width="100px;" alt="pabloandresm"/><br /><sub><b>⭐️ Pablo Martikian</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- Most of the credits go to original author [Dr. Charles Bell](https://github.com/ChuckBell)

- The library is licensed under [MIT](https://github.com/khoih-prog/WebSockets2_Generic/blob/master/LICENSE)

---

## Copyright

1. Copyright (c) 2012- Oracle
2. Copyright (c) 2012- Dr. Charles Bell
3. Copyright (c) 2020- Khoi Hoang



