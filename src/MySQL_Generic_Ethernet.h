/*********************************************************************************************************************************
  MySQL_Generic_Ethernet.h
      
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, WT32_ETH01, Teensy, Portenta_H7, etc. boards 
  using W5x00, ENC28J60, LAM8742A Ethernet, WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi, Portenta Ethernet/WiFi

  The library provides simple and easy Client interface to MySQL or MariaDB Server.
  
  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
  
  Version: 1.7.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/08/2020 Initial coding/porting to support nRF52, SAM DUE and SAMD21/SAMD51 boards using W5x00 Ethernet
                                  (Ethernet, EthernetLarge, Ethernet2, Ethernet3 library), WiFiNINA and ESP8266/ESP32-AT shields
  ...
  1.4.0   K Hoang      05/09/2021 Add support to Teensy 4.1 using QNEthernet
  1.5.0   K Hoang      17/09/2021 Add support to Portenta_H7, using either WiFi or Vision-shield Ethernet
  1.5.1   K Hoang      10/10/2021 Update `platform.ini` and `library.json`
  1.5.2   K Hoang      01/12/2021 Auto detect ESP32 core for LittleFS. Fix bug in examples for WT32_ETH01
  1.6.0   K Hoang      10/03/2022 Fix memory leak bug. Optimize code
  1.6.1   K Hoang      12/03/2022 Fix memory management bug
  1.7.0   K Hoang      12/03/2022 Convert to `h-only` style library
 **********************************************************************************************************************************/

#ifndef MYSQL_GENERIC_ETHERNET_H
#define MYSQL_GENERIC_ETHERNET_H

#include <SPI.h>

#if USE_ETHERNET
  #include "Ethernet.h"
  EthernetClient client;
  #warning Using Ethernet lib
#elif USE_ETHERNET_LARGE
  #include "EthernetLarge.h"
  EthernetClient client;
  #warning Using EthernetLarge lib
#elif USE_ETHERNET2
  #include "Ethernet2.h"
  EthernetClient client;
  #warning Using Ethernet2 lib
#elif USE_ETHERNET3
  #include "Ethernet3.h"
  EthernetClient client;
  #warning Using Ethernet3 lib
// KH, from v1.0.3
#elif USE_ETHERNET_ENC
  #include "EthernetENC.h"
  EthernetClient client;
  #warning Using ENC28J60 with EthernetENC lib
//////  
#elif USE_ETHERNET_ESP8266
  #include "Ethernet_ESP8266.h"
  EthernetClient client;
  #warning Using Ethernet_ESP8266 lib
#elif USE_ETHERNET_LAN8742A
  #include <LwIP.h>
  #include <STM32Ethernet.h>
  EthernetClient client;
  #warning Using Ethernet_LAN8742A lib

// KH, from v1.0.1  
#elif USE_UIP_ETHERNET
  #include <UIPEthernet.h>
  #include <utility/logging.h>
  EthernetClient client;
  #warning Using ENC28J60 UIPEthernet lib
//////

// KH, from v1.3.0  
#elif USE_NATIVE_ETHERNET
  #include <NativeEthernet.h>
  EthernetClient client;
  #warning Using Teensy 4.1 NativeEthernet lib
 
// KH, from v1.4.0  
#elif USE_QN_ETHERNET
  #include <QNEthernet.h>
  using namespace qindesign::network;
  EthernetClient client;
  #warning Using Teensy 4.1 QNEthernet lib

// KH, from v1.5.0  
#elif USE_ETHERNET_PORTENTA_H7
  #include <Portenta_Ethernet.h>
  #include <Ethernet.h>
  EthernetClient client;
  #warning Using Portenta_Ethernet lib for Portenta_H7.
     
#elif USE_CUSTOM_ETHERNET
  #include "Ethernet_XYZ.h"
  EthernetClient client;
  #warning Using Custom Ethernet library from EthernetWrapper. You must include a library here or error.
#else
  // Backup if none is selected
  #define USE_ETHERNET          true
  #include "Ethernet.h"
  EthernetClient client;
  #warning Using Ethernet lib
#endif
 
#endif    //MYSQL_GENERIC_ETHERNET_H
