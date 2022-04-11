/****************************************************************************************************************************
  multiFileProject_WiFi.ino
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.

  The library provides simple and easy Client interface to MySQL or MariaDB Server.
  
  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#include "defines.h"
#include "Credentials.h"

#define MYSQL_MARIADB_GENERIC_VERSION_MIN_TARGET      "MySQL_MariaDB_Generic v1.7.0"
#define MYSQL_MARIADB_GENERIC_VERSION_MIN             1007000

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "MySQL_Generic.h"

void setup() 
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000); // wait for serial port to connect
  
  Serial.println("\nStart multiFileProject_WiFi");
  Serial.println(MYSQL_MARIADB_GENERIC_VERSION);

#if defined(MYSQL_MARIADB_GENERIC_VERSION_MIN)
  if (MYSQL_MARIADB_GENERIC_VERSION_INT < MYSQL_MARIADB_GENERIC_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(MYSQL_MARIADB_GENERIC_VERSION_MIN_TARGET);
  }
#endif
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
