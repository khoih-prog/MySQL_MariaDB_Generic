/*********************************************************************************************************************************
  MySQL_Generic_Debug.h
  
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

/*********************************************************************************************************************************
  Copyright (c) 2012, 2016 Oracle and/or its affiliates. All rights reserved.

  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA

 **********************************************************************************************************************************/

#pragma once

#ifndef MYSQL_GENERIC_DEBUG_H
#define MYSQL_GENERIC_DEBUG_H

#include <stdio.h>

const char CONNECTED[]      /*PROGMEM*/ = "Connected";
const char DISCONNECTED[]   /*PROGMEM*/ = "Disconnected.";

const char MEMORY_ERROR[]   /*PROGMEM*/ = "Memory error.";
const char PACKET_ERROR[]   /*PROGMEM*/ = "Packet error.";
const char READ_TIMEOUT[]   /*PROGMEM*/ = "ERROR: Timeout waiting for client.";

const char BAD_MOJO[]       /*PROGMEM*/ = "Bad mojo. EOF found reading column header.";
const char ROWS[]           /*PROGMEM*/ = " rows in result.";
const char READ_COLS[]      /*PROGMEM*/ = "ERROR: You must read the columns first!";
const char NOT_CONNECTED[]  /*PROGMEM*/ = "ERROR: Class requires connected server.";


#ifdef MYSQL_DEBUG_PORT
  #define MYSQL_DEBUG_OUTPUT MYSQL_DEBUG_PORT
#else
  #define MYSQL_DEBUG_OUTPUT Serial
#endif

// Change _MYSQL_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _MYSQL_LOGLEVEL_
#define _MYSQL_LOGLEVEL_       0
#endif

//////////////////////////////////////////

const char MYSQL_MARK[] = "[SQL] ";
const char MYSQL_SP[]   = " ";

#define MYSQL_PRINT         MYSQL_DEBUG_OUTPUT.print
#define MYSQL_PRINTLN       MYSQL_DEBUG_OUTPUT.println

#define MYSQL_PRINT_MARK    MYSQL_PRINT(MYSQL_MARK)
#define MYSQL_PRINT_SP      MYSQL_PRINT(MYSQL_SP)

///////////////////////////////////////////////////

#define MYSQL_DISPLAY(x)        { MYSQL_PRINTLN(x); }
#define MYSQL_DISPLAY0(x)       { MYSQL_PRINT(x); }
#define MYSQL_DISPLAY1(x,y)     { MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINTLN(y); }
#define MYSQL_DISPLAY2(x,y,z)   { MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINTLN(z); }
#define MYSQL_DISPLAY3(x,y,z,w) { MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINT(z); MYSQL_PRINT_SP; MYSQL_PRINTLN(w); }
#define MYSQL_DISPLAY5(x,y,z,w,xx,yy) { MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINT(z); MYSQL_PRINT_SP; MYSQL_PRINT(w); MYSQL_PRINT_SP; MYSQL_PRINT(xx); MYSQL_PRINT_SP; MYSQL_PRINTLN(yy); }

///////////////////////////////////////////////////

#define MYSQL_LOGERROR(x)        if(_MYSQL_LOGLEVEL_>0) { MYSQL_PRINT_MARK; MYSQL_PRINTLN(x); }
#define MYSQL_LOGERROR0(x)       if(_MYSQL_LOGLEVEL_>0) { MYSQL_PRINT(x); }
#define MYSQL_LOGERROR0LN(x)     if(_MYSQL_LOGLEVEL_>0) { MYSQL_PRINTLN(x); }
#define MYSQL_LOGERROR1(x,y)     if(_MYSQL_LOGLEVEL_>0) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINTLN(y); }
#define MYSQL_LOGERROR2(x,y,z)   if(_MYSQL_LOGLEVEL_>0) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINTLN(z); }
#define MYSQL_LOGERROR3(x,y,z,w) if(_MYSQL_LOGLEVEL_>0) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINT(z); MYSQL_PRINT_SP; MYSQL_PRINTLN(w); }

///////////////////////////////////////////////////

#define MYSQL_LOGWARN(x)         if(_MYSQL_LOGLEVEL_>1) { MYSQL_PRINT_MARK; MYSQL_PRINTLN(x); }
#define MYSQL_LOGWARN0(x)        if(_MYSQL_LOGLEVEL_>1) { MYSQL_PRINT(x); }
#define MYSQL_LOGWARN0LN(x)      if(_MYSQL_LOGLEVEL_>1) { MYSQL_PRINTLN(x); }
#define MYSQL_LOGWARN1(x,y)      if(_MYSQL_LOGLEVEL_>1) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINTLN(y); }
#define MYSQL_LOGWARN2(x,y,z)    if(_MYSQL_LOGLEVEL_>1) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINTLN(z); }
#define MYSQL_LOGWARN3(x,y,z,w)    if(_MYSQL_LOGLEVEL_>1) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINT(z); MYSQL_PRINT_SP; MYSQL_PRINTLN(w); }

///////////////////////////////////////////////////

#define MYSQL_LOGINFO(x)         if(_MYSQL_LOGLEVEL_>2) { MYSQL_PRINT_MARK; MYSQL_PRINTLN(x); }
#define MYSQL_LOGINFO0(x)        if(_MYSQL_LOGLEVEL_>2) { MYSQL_PRINT(x); }
#define MYSQL_LOGINFO0LN(x)      if(_MYSQL_LOGLEVEL_>2) { MYSQL_PRINTLN(x); }
#define MYSQL_LOGINFO1(x,y)      if(_MYSQL_LOGLEVEL_>2) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINTLN(y); }
#define MYSQL_LOGINFO2(x,y,z)    if(_MYSQL_LOGLEVEL_>2) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINTLN(z); }
#define MYSQL_LOGINFO3(x,y,z,w)  if(_MYSQL_LOGLEVEL_>2) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINT(z); MYSQL_PRINT_SP; MYSQL_PRINTLN(w); }

///////////////////////////////////////////////////

#define MYSQL_LOGDEBUG(x)        if(_MYSQL_LOGLEVEL_>3) { MYSQL_PRINT_MARK; MYSQL_PRINTLN(x); }
#define MYSQL_LOGDEBUG0(x)       if(_MYSQL_LOGLEVEL_>3) { MYSQL_PRINT(x); }
#define MYSQL_LOGDEBUG0LN(x)     if(_MYSQL_LOGLEVEL_>3) { MYSQL_PRINTLN(x); }
#define MYSQL_LOGDEBUG1(x,y)     if(_MYSQL_LOGLEVEL_>3) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINTLN(y); }
#define MYSQL_LOGDEBUG2(x,y,z)   if(_MYSQL_LOGLEVEL_>3) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINTLN(z); }
#define MYSQL_LOGDEBUG3(x,y,z,w) if(_MYSQL_LOGLEVEL_>3) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINT(z); MYSQL_PRINT_SP; MYSQL_PRINTLN(w); }

///////////////////////////////////////////////////

#define MYSQL_LOGLEVEL5(x)        if(_MYSQL_LOGLEVEL_>4) { MYSQL_PRINT_MARK; MYSQL_PRINTLN(x); }
#define MYSQL_LOGLEVEL5_0(x)      if(_MYSQL_LOGLEVEL_>4) { MYSQL_PRINT(x); }
#define MYSQL_LOGLEVEL5_0LN(x)    if(_MYSQL_LOGLEVEL_>4) { MYSQL_PRINTLN(x); }
#define MYSQL_LOGLEVEL5_1(x,y)    if(_MYSQL_LOGLEVEL_>4) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINTLN(y); }
#define MYSQL_LOGLEVEL5_2(x,y,z)  if(_MYSQL_LOGLEVEL_>4) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINTLN(z); }
#define MYSQL_LOGLEVEL5_3(x,y,z,w) if(_MYSQL_LOGLEVEL_>4) { MYSQL_PRINT_MARK; MYSQL_PRINT(x); MYSQL_PRINT_SP; MYSQL_PRINT(y); MYSQL_PRINT_SP; MYSQL_PRINT(z); MYSQL_PRINT_SP; MYSQL_PRINTLN(w); }

///////////////////////////////////////////////////

#endif    // MYSQL_GENERIC_DEBUG_H
