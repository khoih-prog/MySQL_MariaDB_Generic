/*********************************************************************************************************************************
  MySQL_Generic_Encrypt_Sha1.h
  
  GNU GPL v3:
  This file is part of the code entitled, "cryptosuite" available at https://code.google.com/p/cryptosuite/. The file was copied from that
  repository and renamed for use in Connector/Arduino to preserve compatibility and protect against namespace collisions for users who
  want to use the full cryptosuite functionality. For Connector/Arduino all that is needed is this one sha1 class.
     
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

#pragma once

#ifndef MYSQL_GENERIC_ENCRYPT_SHA1_H
#define MYSQL_GENERIC_ENCRYPT_SHA1_H

#include <inttypes.h>
#include "Print.h"

#define HASH_LENGTH 20
#define BLOCK_LENGTH 64

union _buffer 
{
  uint8_t   b [BLOCK_LENGTH];
  uint32_t  w [BLOCK_LENGTH / 4];
};

union _state 
{
  uint8_t   b [HASH_LENGTH];
  uint32_t  w [HASH_LENGTH / 4];
};

class Encrypt_SHA1 : public Print
{
  public:
    void      init();
    void      initHmac(const uint8_t* secret, const int& secretLength);
    uint8_t*  result();
    virtual size_t write(uint8_t data);
    virtual size_t write(uint8_t* data, const int& length);
    using Print::write;
    
  private:
    void      pad();
    void      addUncounted(const uint8_t& data);
    void      hashBlock();
    uint32_t  rol32(const uint32_t& number, const uint8_t& bits);
    _buffer   buffer;
    uint8_t   bufferOffset;
    _state    state;
    uint32_t  byteCount;
    uint8_t   keyBuffer[BLOCK_LENGTH];
    uint8_t   innerHash[HASH_LENGTH];
};

//extern Encrypt_SHA1 Sha1;

//#include "MySQL_Generic_Encrypt_Sha1_Impl.h"

#endif    // MYSQL_GENERIC_ENCRYPT_SHA1_H
