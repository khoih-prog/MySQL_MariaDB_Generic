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
  Version: 1.5.1

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/08/2020 Initial coding/porting to support nRF52, SAM DUE and SAMD21/SAMD51 boards using W5x00 Ethernet
                                  (Ethernet, EthernetLarge, Ethernet2, Ethernet3 library), WiFiNINA and ESP8266/ESP32-AT shields
  1.0.1   K Hoang      18/08/2020 Add support to Ethernet ENC28J60. Fix bug, optimize code.
  1.0.2   K Hoang      20/08/2020 Fix crashing bug when timeout. Make code more error-proof. Drop support to ESP8266_AT_Webserver.
  1.0.3   K Hoang      02/10/2020 Add support to Ethernet ENC28J60 using new EthernetENC library.
  1.1.0   K Hoang      08/06/2021 Add support to RP2040-based boards such as Nano_RP2040_Connect, RASPBERRY_PI_PICO. etc.
  1.2.0   K Hoang      20/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720A)
  1.3.0   K Hoang      30/08/2021 Add support to Teensy 4.1 using NativeEthernet
  1.3.1   K Hoang      31/08/2021 Remove unnecessary SPI-bus code in NativeEthernet examples
  1.4.0   K Hoang      05/09/2021 Add support to Teensy 4.1 using QNEthernet
  1.5.0   K Hoang      17/09/2021 Add support to Portenta_H7, using either WiFi or Vision-shield Ethernet
  1.5.1   K Hoang      10/10/2021 Update `platform.ini` and `library.json`
 **********************************************************************************************************************************/

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
    void      init(void);
    void      initHmac(const uint8_t* secret, int secretLength);
    uint8_t*  result(void);
    virtual size_t write(uint8_t);
    virtual size_t write(uint8_t* data, int length);
    using Print::write;
    
  private:
    void      pad();
    void      addUncounted(uint8_t data);
    void      hashBlock();
    uint32_t  rol32(uint32_t number, uint8_t bits);
    _buffer   buffer;
    uint8_t   bufferOffset;
    _state    state;
    uint32_t  byteCount;
    uint8_t   keyBuffer[BLOCK_LENGTH];
    uint8_t   innerHash[HASH_LENGTH];
};

extern Encrypt_SHA1 Sha1;

#include "MySQL_Generic_Encrypt_Sha1_Impl.h"

#endif    // MYSQL_GENERIC_ENCRYPT_SHA1_H
