/****************************************************************************************************************************
  MySQL_Generic_WiFi.h
  
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

#ifndef MYSQL_GENERIC_WIFI_H
#define MYSQL_GENERIC_WIFI_H

// ESP8266 and ESP32 built-in WiFi have highest priority and will override all other settings
#if (ESP8266)
  #warning Using ESP8266 built-in WiFi
  #include <ESP8266WiFi.h>
  WiFiClient client;
  
#elif (ESP32)
  #warning Using ESP32 built-in WiFi
  #include <WiFi.h>
  WiFiClient client;
  
#elif USING_WIFI_ESP8266_AT
  // Changed from USING_WIFI_ESP_AT to USING_WIFI_ESP8266_AT from v1.0.2
  #error Using ESP8266_AT Library not supported now
  // Uncomment to use ESP32-AT commands
  //#define USE_ESP32_AT      true
  
  #include <ESP8266_AT_WebServer.h>
  #include <ESP8266_AT.h>
  #include <ESP8266_AT_Client.h>
  ESP8266_AT_Client client;
#elif (USING_WIFININA_GENERIC)
  #warning Using WiFiNINA_Generic Library
  #include "WiFiNINA_Generic.h"
  #include "WiFiClient_Generic.h"
  WiFiClient client;
  
#elif (USING_WIFININA)
  #warning Using WiFiNINA Library
  #include "WiFiNINA.h"
  #include "WiFiClient.h"
  WiFiClient client;
  
#elif (USING_WIFIESPAT_LIB)
  #warning Using WiFiEspAT Library
  #include "WiFiEspAT.h"
  WiFiClient client;
  
#elif (USING_WIFI_CUSTOM)
  #warning Using Custom WiFi Library. To modify according to Library.
  #include "WiFi_XYZ.h"
  #include "WiFi_XYZ_Client.h"
  WiFiClient client;
  
#else
  #error You must specify a WiFi Library to use.
  
#endif

#include <MySQL_Generic_Connection.h>
#include <MySQL_Generic_Query.h>

#endif    //MYSQL_GENERIC_WIFI_H
