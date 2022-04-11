/*********************************************************************************************************************************
  MySQL_Generic_Packet.h
  
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

#ifndef MYSQL_GENERIC_PACKET_H
#define MYSQL_GENERIC_PACKET_H

// KH
#include <Arduino.h>
#include <Client.h>

#define MYSQL_OK_PACKET         0x00
#define MYSQL_EOF_PACKET        0xfe
#define MYSQL_ERROR_PACKET      0xff

// KH, for validating packet size
#define MAX_TRANSMISSION_UNIT   1500
//////

class MySQL_Packet 
{
  public:
    byte *buffer;           // buffer for reading packets
    
    // KH, from v1.0.1
    uint16_t largest_buffer_size = 0;
    //////
    
    int packet_len;         // length of current packet
    Client *client;         // instance of client class (e.g. EthernetClient)
    char *server_version;   // save server version from handshake

    MySQL_Packet(Client *client_instance);
    virtual ~MySQL_Packet()
    {
			if (buffer)
			{
				MYSQL_LOGDEBUG("Free buffer");

				free(buffer);
			}
			if (server_version)
			{
				MYSQL_LOGDEBUG("Free server_version");

				free(server_version);
			}
    };
    
    bool    complete_handshake(char *user, char *password);
    void    send_authentication_packet(char *user, char *password, char *db = NULL);
    void    parse_handshake_packet();
    bool    scramble_password(char *password, byte *pwd_hash);
    
    // KH, mod from v1.0.2. Return true if valid packet
    bool    read_packet();
    
    int     get_packet_type();
    void    parse_error_packet();
    int     get_lcb_len(const int& offset);
    int     read_int(const int& offset, const int& size = 0);
    void    store_int(byte *buff, const long& value, const int& size);
    int     read_lcb_int(const int& offset);
    int     wait_for_bytes(const int& bytes_need);

    void    print_packet();

  private:
    byte seed[20];
};

//#include <MySQL_Generic_Packet_Impl.h>


#endif    // MYSQL_GENERIC_PACKET_H
