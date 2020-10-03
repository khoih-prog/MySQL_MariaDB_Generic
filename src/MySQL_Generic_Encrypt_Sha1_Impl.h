/*********************************************************************************************************************************
  MySQL_Generic_Encrypt_Sha1_Impl.h
  
  GNU GPL v3:
  This file is part of the code entitled, "cryptosuite" available at https://code.google.com/p/cryptosuite/. The file was copied from that
  repository and renamed for use in Connector/Arduino to preserve compatibility and protect against namespace collisions for users who
  want to use the full cryptosuite functionality. For Connector/Arduino all that is needed is this one sha1 class.
     
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.
  
  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
  Version: 1.0.3

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/08/2020 Initial coding/porting to support nRF52, SAM DUE and SAMD21/SAMD51 boards using W5x00 Ethernet
                                  (Ethernet, EthernetLarge, Ethernet2, Ethernet3 library), WiFiNINA and ESP8266/ESP32-AT shields
  1.0.1   K Hoang      18/08/2020 Add support to Ethernet ENC28J60. Fix bug, optimize code.
  1.0.2   K Hoang      20/08/2020 Fix crashing bug when timeout. Make code more error-proof. Drop support to ESP8266_AT_Webserver.
  1.0.3   K Hoang      02/10/2020 Add support to Ethernet ENC28J60 using new EthernetENC library.
 **********************************************************************************************************************************/

#ifndef MYSQL_GENERIC_ENCRYPT_SHA1_IMPL_H
#define MYSQL_GENERIC_ENCRYPT_SHA1_IMPL_H

#include <string.h>

#define MYSQL_SHA1_K0     0x5a827999
#define MYSQL_SHA1_K20    0x6ed9eba1
#define MYSQL_SHA1_K40    0x8f1bbcdc
#define MYSQL_SHA1_K60    0xca62c1d6

const uint8_t sha1InitState[] PROGMEM = 
{
  0x01, 0x23, 0x45, 0x67, // H0
  0x89, 0xab, 0xcd, 0xef, // H1
  0xfe, 0xdc, 0xba, 0x98, // H2
  0x76, 0x54, 0x32, 0x10, // H3
  0xf0, 0xe1, 0xd2, 0xc3  // H4
};

void Encrypt_SHA1::init(void) 
{
  // KH
  //memcpy_P(state.b, sha1InitState, HASH_LENGTH);
  memcpy(state.b, sha1InitState, HASH_LENGTH);
  
  byteCount = 0;
  bufferOffset = 0;
}

uint32_t Encrypt_SHA1::rol32(uint32_t number, uint8_t bits) 
{
  return ((number << bits) | (number >> (32 - bits)));
}

void Encrypt_SHA1::hashBlock() 
{
  // SHA1 only for now
  uint8_t i;
  uint32_t a, b, c, d, e, t;

  a = state.w[0];
  b = state.w[1];
  c = state.w[2];
  d = state.w[3];
  e = state.w[4];
  
  for (i = 0; i < 80; i++) 
  {
    if (i >= 16) 
    {
      t = buffer.w[(i + 13) & 15] ^ buffer.w[(i + 8) & 15] ^ buffer.w[(i + 2) & 15] ^ buffer.w[i & 15];
      buffer.w[i & 15] = rol32(t, 1);
    }
    
    if (i < 20) 
    {
      t = (d ^ (b & (c ^ d))) + MYSQL_SHA1_K0;
    } 
    else if (i < 40) 
    {
      t = (b ^ c ^ d) + MYSQL_SHA1_K20;
    } 
    else if (i < 60) 
    {
      t = ((b & c) | (d & (b | c))) + MYSQL_SHA1_K40;
    } 
    else 
    {
      t = (b ^ c ^ d) + MYSQL_SHA1_K60;
    }
    
    t += rol32(a, 5) + e + buffer.w[i & 15];
    e = d;
    d = c;
    c = rol32(b, 30);
    b = a;
    a = t;
  }
  
  state.w[0] += a;
  state.w[1] += b;
  state.w[2] += c;
  state.w[3] += d;
  state.w[4] += e;
}

void Encrypt_SHA1::addUncounted(uint8_t data) 
{
  buffer.b[bufferOffset ^ 3] = data;
  bufferOffset++;
  
  if (bufferOffset == BLOCK_LENGTH) 
  {
    hashBlock();
    bufferOffset = 0;
  }
}

size_t Encrypt_SHA1::write(uint8_t data) 
{
  ++byteCount;
  addUncounted(data);
  
  // KH add
  return 1;
}

size_t Encrypt_SHA1::write(uint8_t* data, int length) 
{
  for (int i = 0; i < length; i++) 
  {
    write(data[i]);
  }
  
  // KH add
  return length;
}

void Encrypt_SHA1::pad() 
{
  // Implement SHA-1 padding (fips180-2 §5.1.1)

  // Pad with 0x80 followed by 0x00 until the end of the block
  addUncounted(0x80);
  
  while (bufferOffset != 56) 
    addUncounted(0x00);

  // Append length in the last 8 bytes
  addUncounted(0); // We're only using 32 bit lengths
  addUncounted(0); // But SHA-1 supports 64 bit lengths
  addUncounted(0); // So zero pad the top bits
  addUncounted(byteCount >> 29); // Shifting to multiply by 8
  addUncounted(byteCount >> 21); // as SHA-1 supports bitstreams as well as
  addUncounted(byteCount >> 13); // byte.
  addUncounted(byteCount >> 5);
  addUncounted(byteCount << 3);
}


uint8_t* Encrypt_SHA1::result(void) 
{
  // Pad to complete the last block
  pad();

  // Swap byte order back
  for (int i = 0; i < 5; i++) 
  {
    uint32_t a, b;
    
    a = state.w[i];
    b = a << 24;
    b |= (a << 8) & 0x00ff0000;
    b |= (a >> 8) & 0x0000ff00;
    b |= a >> 24;
    state.w[i] = b;
  }

  // Return pointer to hash (20 characters)
  return state.b;
}


#define HMAC_IPAD 0x36
#define HMAC_OPAD 0x5c

Encrypt_SHA1 Sha1;

#endif    // MYSQL_GENERIC_ENCRYPT_SHA1_IMPL_H
