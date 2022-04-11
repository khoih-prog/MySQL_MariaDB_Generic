/*********************************************************************************************************************************
  MySQL_Generic_Ethernet.h
      
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, WT32_ETH01, Teensy, Portenta_H7, etc. boards 
  using W5x00, ENC28J60, LAM8742A Ethernet, WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi, Portenta Ethernet/WiFi

  The library provides simple and easy Client interface to MySQL or MariaDB Server.
  
  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
  
  Version: 1.7.2

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
  1.7.1   K Hoang      10/04/2022 Use Ethernet_Generic library as default. Support SPI1/SPI2 for RP2040/ESP32
  1.7.2   K Hoang      11/04/2022 Fix missing paragraph in `library.properties`
 **********************************************************************************************************************************/

#ifndef MYSQL_GENERIC_ETHERNET_H
#define MYSQL_GENERIC_ETHERNET_H

#include <SPI.h>

///////////////////////////////////////////////////////

#if USE_ETHERNET_PORTENTA_H7
  #include <Portenta_Ethernet.h>
  #include <Ethernet.h>
  
  EthernetClient client;
  
  #define SHIELD_TYPE           "Ethernet using Portenta_Ethernet Library"

//////////////////////////////////////

#elif USE_QN_ETHERNET
  #include <QNEthernet.h>
  using namespace qindesign::network;
  
  EthernetClient client;
  
  #define SHIELD_TYPE           "Ethernet using Teensy 4.1 QNEthernet Library"

//////////////////////////////////////
    
#elif USE_NATIVE_ETHERNET
  #include "NativeEthernet.h"
  
  EthernetClient client;
  
  #define SHIELD_TYPE           "Ethernet using Teensy 4.1 NativeEthernet Library"

//////////////////////////////////////
  
#elif USE_ETHERNET_LAN8742A
  #include <LwIP.h>
  #include <STM32Ethernet.h>
  
  EthernetClient client;
  
  #define SHIELD_TYPE           "LAN8742A Ethernet & STM32Ethernet Library" 

//////////////////////////////////////

#elif USE_ETHERNET_LAN8720
  #include <LwIP.h>
  #include <STM32Ethernet.h>
  
  EthernetClient client;
  
  #define SHIELD_TYPE           "LAN8720 Ethernet & STM32Ethernet Library" 

//////////////////////////////////////
      
#elif USE_ETHERNET_GENERIC
  #if (ESP32)
    #include <soc/spi_pins.h>
      
    // Optional SPI2
    //#define USING_SPI2                          true

    #if USING_SPI2
      #define PIN_MISO          HSPI_IOMUX_PIN_NUM_MISO
      #define PIN_MOSI          HSPI_IOMUX_PIN_NUM_MOSI
      #define PIN_SCK           HSPI_IOMUX_PIN_NUM_CLK
      #define PIN_SS            HSPI_IOMUX_PIN_NUM_CS
    
      #define SHIELD_TYPE       "W5x00 using Ethernet_Generic Library on SPI2"
      
    #else
    
      #define PIN_MISO          MISO
      #define PIN_MOSI          MOSI
      #define PIN_SCK           SCK
      #define PIN_SS            SS
    
      #define SHIELD_TYPE       "W5x00 using Ethernet_Generic Library on SPI"
      
    #endif

  #else
    #if USING_SPI2
      #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library on SPI1"
    #else
      #define SHIELD_TYPE           "W5x00 using Ethernet_Generic Library on SPI0/SPI"
    #endif 
  #endif
 
  #include "Ethernet_Generic.h"
  
  EthernetClient client;

//////////////////////////////////////

#elif USE_ETHERNET_ESP8266
  #include "Ethernet_ESP8266.h"
  
  EthernetClient client;
  
  #define SHIELD_TYPE           "W5x00 using Ethernet_ESP8266 Library" 

//////////////////////////////////////
  
#elif USE_ETHERNET_ENC
  #include "EthernetENC.h"
  
  EthernetClient client;

  #define SHIELD_TYPE           "ENC28J60 using EthernetENC Library"

//////////////////////////////////////
  
#elif USE_CUSTOM_ETHERNET
  // You have to include an Ethernet library in your program
  //#include "Ethernet_XYZ.h"
  //#include "EthernetLarge.h"
  
  EthernetClient client;
  
  #if !defined(SHIELD_TYPE)
    #define SHIELD_TYPE           "Custom Ethernet using your choice of Library"
  #endif

//////////////////////////////////////
  
#else

  #ifdef USE_ETHERNET_GENERIC
    #undef USE_ETHERNET_GENERIC
  #endif
  #define USE_ETHERNET_GENERIC   true
  #include "Ethernet_Generic.h"
  
  EthernetClient client;

  #define SHIELD_TYPE           "W5x00 using default Ethernet_Generic Library"
  
#endif

///////////////////////////////////////////////////////
 
#endif    //MYSQL_GENERIC_ETHERNET_H
