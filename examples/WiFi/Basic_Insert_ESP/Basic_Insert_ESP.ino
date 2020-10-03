/*********************************************************************************************************************************
  Basic_Insert_ESP.ino
      
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
/*
  MySQL Connector/Arduino Example : connect by wifi

  This example demonstrates how to connect to a MySQL server from an
  Arduino using an Arduino-compatible Wifi shield. Note that "compatible"
  means it must conform to the Ethernet class library or be a derivative
  with the same classes and methods.
  
  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

  INSTRUCTIONS FOR USE

  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Change the SSID and pass to match your WiFi network
  4) Connect a USB cable to your Arduino
  5) Select the correct board and port
  6) Compile and upload the sketch to your Arduino
  7) Once uploaded, open Serial Monitor (use 115200 speed) and observe

  If you do not see messages indicating you have a connection, refer to the
  manual for troubleshooting tips. The most common issues are the server is
  not accessible from the network or the user name and password is incorrect.

  Created by: Dr. Charles A. Bell
*/

#if ! (ESP8266 || ESP32 )
  #error This code is intended to run on the ESP8266/ESP32 platform! Please check your Tools->Board setting
#endif

#include "Credentials.h"

#define MYSQL_DEBUG_PORT      Serial

// Debug Level from 0 to 4
#define _MYSQL_LOGLEVEL_      1

#include <MySQL_Generic_WiFi.h>

IPAddress server_addr(192, 168, 2, 112);
uint16_t server_port = 5698;    //3306;

char default_database[] = "test_arduino";           //"test_arduino";
char default_table[]    = "hello_arduino";          //"test_arduino";

String default_value    = "Hello, Arduino!"; 

// Sample query
String INSERT_SQL = String("INSERT INTO ") + default_database + "." + default_table 
                 + " (message) VALUES ('" + default_value + "')";

MySQL_Connection conn((Client *)&client);

MySQL_Query *query_mem;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStarting Basic_Insert_ESP on " + String(ARDUINO_BOARD));

  // Begin WiFi section
  Serial.println(String("Connecting to ") + ssid);
  
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  // print out info about the connection:
  Serial.print("Connected to network. My IP address is: ");
  Serial.println(WiFi.localIP());

  Serial.print("Connecting to SQL Server @ ");
  Serial.print(server_addr);
  Serial.println(String(", Port = ") + server_port);
  Serial.println(String("User = ") + user + String(", PW = ") + password + String(", DB = ") + default_database);
}

void runInsert(void)
{
  // Initiate the query class instance
  MySQL_Query query_mem = MySQL_Query(&conn);

  if (conn.connected())
  {
    Serial.println(INSERT_SQL);
    
    // Execute the query
    // KH, check if valid before fetching
    if ( !query_mem.execute(INSERT_SQL.c_str()) )
      Serial.println("Insert error");
    else    
      Serial.println("Data Inserted.");
  }
  else
  {
    Serial.println("Disconnected from Server. Can't insert.");
  }
}

void loop()
{
  Serial.println("Connecting...");
  
  //if (conn.connect(server_addr, server_port, user, password))
  if (conn.connectNonBlocking(server_addr, server_port, user, password) != RESULT_FAIL)
  {
    delay(500);
    runInsert();
    conn.close();                     // close the connection
  } 
  else 
  {
    Serial.println("\nConnect failed. Trying again on next iteration.");
  }

  Serial.println("\nSleeping...");
  Serial.println("================================================");
 
  delay(10000);
}
