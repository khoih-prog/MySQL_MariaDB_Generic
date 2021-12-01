/*********************************************************************************************************************************
  MySQL_Generic_Connection_Impl.h
  
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, WT32_ETH01, Teensy, Portenta_H7, etc. boards 
  using W5x00, ENC28J60, LAM8742A Ethernet, WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi, Portenta Ethernet/WiFi

  The library provides simple and easy Client interface to MySQL or MariaDB Server.
  
  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
  Version: 1.5.2

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
  1.5.2   K Hoang      01/12/2021 Auto detect ESP32 core for LittleFS. Fix bug in examples for WT32_ETH01
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
 
#ifndef MYSQL_GENERIC_CONNECTION_IMPL_H
#define MYSQL_GENERIC_CONNECTION_IMPL_H

#include <Arduino.h>

#include <MySQL_Generic_Encrypt_Sha1.h>

#define MAX_CONNECT_ATTEMPTS      10
#define CONNECT_DELAY_MS          1000
#define SUCCESS                   1

/*
  connect - Connect to a MySQL server.

  This method is used to connect to a MySQL server. It will attempt to
  connect to the server as a client retrying up to MAX_CONNECT_ATTEMPTS.
  This permits the possibility of longer than normal network lag times
  for wireless networks. You can adjust MAX_CONNECT_ATTEMPTS to suit
  your environment.

  server[in]      IP address of the server as IPAddress type
  port[in]        port number of the server
  user[in]        user name
  password[in]    (optional) user password
  db[in]          (optional) default database

  Returns bool - True = connection succeeded
*/

bool MySQL_Connection::connect(IPAddress server, int port, char *user, char *password, char *db)
{
  int connected = 0;
  int retries = 0;
  
  MYSQL_LOGERROR3("Connecting to Server:", server, ", Port = ", port);
  
  if (db)
    MYSQL_LOGERROR1("Using Database:", db);

  // Retry up to MAX_CONNECT_ATTEMPTS times.
  while (retries++ < MAX_CONNECT_ATTEMPTS)
  {
    connected = client->connect(server, port);
    
    MYSQL_LOGDEBUG1("connected =", connected);

    if (connected != SUCCESS)
    {
      MYSQL_LOGDEBUG1("Can't connect. Retry #", retries);
      delay(CONNECT_DELAY_MS);
    }
    else
    {
      break;
    }
  }

  if (connected != SUCCESS)
    return false;

  MYSQL_LOGERROR("Connect OK. Try reading packets");

  if ( !read_packet() )
  {
    MYSQL_LOGERROR("Can't connect. Error reading packets");
    return false;
  }

  MYSQL_LOGERROR("Try parsing packets");

  parse_handshake_packet();

  MYSQL_LOGERROR("Try send_authentication packets");

  send_authentication_packet(user, password, db);
   
  if ( !read_packet() )
  {
    MYSQL_LOGERROR("Can't connect. Error reading auth packets");
    return false;
  }

  if (get_packet_type() != MYSQL_OK_PACKET)
  {
    parse_error_packet();
    return false;
  }

  MYSQL_LOGERROR1("Connected. Server Version =", server_version);

  free(server_version); // don't need it anymore

  return true;
}


Connection_Result MySQL_Connection::connectNonBlocking(IPAddress server, int port, char *user, char *password, char *db)
{
  int connected = 0;
  int retries   = 0;
  
  long now = 0;
  
  MYSQL_LOGERROR3("Connecting to Server:", server, ", Port = ", port);
  
  if (db)
    MYSQL_LOGERROR1("Using Database:", db);
  
  while (retries < MAX_CONNECT_ATTEMPTS)
  {  
    if ( (now == 0) || ( millis() - now ) > CONNECT_DELAY_MS )
    {
      now = millis();
      
      connected = client->connect(server, port);
      
      retries++;
      
      MYSQL_LOGDEBUG1("connected =", connected);

      if (connected == SUCCESS)
      {
        break;
      }
      else
      {
        MYSQL_LOGDEBUG1("Can't connect. Retry #", retries);
      }     
    }
    else
    {
      //delay(CONNECT_DELAY_MS);
      yield();
    }
  }

  if (connected != SUCCESS)
    return RESULT_FAIL;

  MYSQL_LOGERROR("Connect OK. Try reading packets");

  if ( !read_packet() )
  {
    MYSQL_LOGERROR("Can't connect. Error reading packets");
    return RESULT_FAIL;
  }

  MYSQL_LOGERROR("Try parsing packets");

  parse_handshake_packet();

  MYSQL_LOGERROR("Try send_authentication packets");

  send_authentication_packet(user, password, db);
  
  if ( !read_packet() )
  {
    MYSQL_LOGERROR("Can't connect. Error reading auth packets");
    return RESULT_FAIL;
  }

  if (get_packet_type() != MYSQL_OK_PACKET)
  {
    parse_error_packet();
    return RESULT_FAIL;
  }

  MYSQL_LOGERROR1("Connected. Server Version =", server_version);

  free(server_version); // don't need it anymore

  return RESULT_OK;
}

//////////////////////////////////////////////////////////////
// KH, add to use hostname. from v1.4.0

bool MySQL_Connection::connect(const char *hostname, int port, char *user, char *password, char *db)
{
  int connected = 0;
  int retries = 0;
  
  MYSQL_LOGERROR3("Connecting to Server:", hostname, ", Port = ", port);
  
  if (db)
    MYSQL_LOGERROR1("Using Database:", db);

  // Retry up to MAX_CONNECT_ATTEMPTS times.
  while (retries++ < MAX_CONNECT_ATTEMPTS)
  {
    connected = client->connect(hostname, port);
    
    MYSQL_LOGDEBUG1("connected =", connected);

    if (connected != SUCCESS)
    {
      MYSQL_LOGDEBUG1("Can't connect. Retry #", retries);
      delay(CONNECT_DELAY_MS);
    }
    else
    {
      break;
    }
  }

  if (connected != SUCCESS)
    return false;

  MYSQL_LOGERROR("Connect OK. Try reading packets");

  if ( !read_packet() )
  {
    MYSQL_LOGERROR("Can't connect. Error reading packets");
    return false;
  }

  MYSQL_LOGERROR("Try parsing packets");

  parse_handshake_packet();

  MYSQL_LOGERROR("Try send_authentication packets");

  send_authentication_packet(user, password, db);
   
  if ( !read_packet() )
  {
    MYSQL_LOGERROR("Can't connect. Error reading auth packets");
    return false;
  }

  if (get_packet_type() != MYSQL_OK_PACKET)
  {
    parse_error_packet();
    return false;
  }

  MYSQL_LOGERROR1("Connected. Server Version =", server_version);

  free(server_version); // don't need it anymore

  return true;
}

Connection_Result MySQL_Connection::connectNonBlocking(const char *hostname, int port, char *user, char *password, char *db)
{
  int connected = 0;
  int retries   = 0;
  
  long now = 0;
  
  MYSQL_LOGERROR3("Connecting to Server:", hostname, ", Port = ", port);
  
  if (db)
    MYSQL_LOGERROR1("Using Database:", db);
  
  while (retries < MAX_CONNECT_ATTEMPTS)
  {  
    if ( (now == 0) || ( millis() - now ) > CONNECT_DELAY_MS )
    {
      now = millis();
      
      connected = client->connect(hostname, port);
      
      retries++;
      
      MYSQL_LOGDEBUG1("connected =", connected);

      if (connected == SUCCESS)
      {
        break;
      }
      else
      {
        MYSQL_LOGDEBUG1("Can't connect. Retry #", retries);
      }     
    }
    else
    {
      //delay(CONNECT_DELAY_MS);
      yield();
    }
  }

  if (connected != SUCCESS)
    return RESULT_FAIL;

  MYSQL_LOGERROR("Connect OK. Try reading packets");

  if ( !read_packet() )
  {
    MYSQL_LOGERROR("Can't connect. Error reading packets");
    return RESULT_FAIL;
  }

  MYSQL_LOGERROR("Try parsing packets");

  parse_handshake_packet();

  MYSQL_LOGERROR("Try send_authentication packets");

  send_authentication_packet(user, password, db);
  
  if ( !read_packet() )
  {
    MYSQL_LOGERROR("Can't connect. Error reading auth packets");
    return RESULT_FAIL;
  }

  if (get_packet_type() != MYSQL_OK_PACKET)
  {
    parse_error_packet();
    return RESULT_FAIL;
  }

  MYSQL_LOGERROR1("Connected. Server Version =", server_version);

  free(server_version); // don't need it anymore

  return RESULT_OK;
}


//////////////////////////////////////////////////////////////

/*
  close - cancel the connection

  This method closes the connection to the server and frees up any memory
  used in the buffer.
*/
void MySQL_Connection::close()
{
  if (connected())
  {
    client->flush();
    client->stop();
    
    MYSQL_LOGERROR("Disconnected");
  }
}

#endif    // MYSQL_GENERIC_CONNECTION_IMPL_H
