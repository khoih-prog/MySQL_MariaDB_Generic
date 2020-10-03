/*********************************************************************************************************************************
  MySQL_Generic_Connection.h
  
  This header file defines a connection class for connecting to a MySQL/MariaDB server.
  
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.

  The library provides simple and easy Client interface to MySQL or MariaDB Server.
  
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

/*********************************************************************************************************************************
  Copyright (c) 2012, 2016 Oracle and/or its affiliates. All rights reserved.

  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA

 **********************************************************************************************************************************/
 
#ifndef MYSQL_GENERIC_CONNECTION_H
#define MYSQL_GENERIC_CONNECTION_H

#include "MySQL_Generic_Debug.h"

#include <MySQL_Generic_Packet.h>

typedef enum 
{
  RESULT_OK     = 0, 
  RESULT_FAIL,
  RESULT_PENDING
} Connection_Result;


class MySQL_Connection : public MySQL_Packet 
{
  public:
    MySQL_Connection(Client *client_instance) : MySQL_Packet(client_instance) {}
    
    bool connect(IPAddress server, int port, char *user, char *password, char *db = NULL);
    
    Connection_Result connectNonBlocking(IPAddress server, int port, char *user, char *password, char *db = NULL);
    
    int connected() 
    {
      return client->connected();
    }
    
    const char *version() 
    {
      return MYSQL_GENERIC_VERSION;
    }
    
    void close();
};

#include <MySQL_Generic_Connection_Impl.h>

#endif    // MYSQL_GENERIC_CONNECTION_H
