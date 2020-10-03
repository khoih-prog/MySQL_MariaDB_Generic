/*********************************************************************************************************************************
  Query_Progmem_WiFi.ino

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
  MySQL Connector/Arduino Example : query with PROGMEM strings

  This example demonstrates how to issue queries using strings stored in
  PROGMEM. As you will see, you need only add a parameter to the execute()
  method in the cursor class, const and PROGMEM to the string declaration
  and add the #include <avr/pgmspace.h> directive.

  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

  NOTICE: You must download and install the World sample database to run
          this sketch unaltered. See http://dev.mysql.com/doc/index-other.html.

  INSTRUCTIONS FOR USE

  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Connect a USB cable to your Arduino
  4) Select the correct board and port
  5) Compile and upload the sketch to your Arduino
  6) Once uploaded, open Serial Monitor (use 115200 speed) and observe

  Note: The MAC address can be anything so long as it is unique on your network.

  Created by: Dr. Charles A. Bell
*/

#include "defines.h"
#include "Credentials.h"

#include <MySQL_Generic_WiFi.h>
#include <avr/pgmspace.h>

IPAddress server_addr(192, 168, 2, 112);
uint16_t server_port = 5698;    //3306;

// Sample query
const char PROGMEM query[] = "SELECT * FROM test_arduino.hello_arduino LIMIT 6;";

MySQL_Connection conn((Client *)&client);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println("\nStarting Query_Progmem_WiFi on " + String(BOARD_NAME));

  // Remember to initialize your WiFi module
#if ( USING_WIFI_ESP8266_AT  || USING_WIFIESPAT_LIB ) 
  #if ( USING_WIFI_ESP8266_AT )
    Serial.println("Using ESP8266_AT/ESP8266_AT_WebServer Library");
  #elif ( USING_WIFIESPAT_LIB )
    Serial.println("Using WiFiEspAT Library");
  #endif
  
  // initialize serial for ESP module
  EspSerial.begin(115200);
  // initialize ESP module
  WiFi.init(&EspSerial);

  Serial.println(F("WiFi shield init done"));

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }
#endif

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
  Serial.println(String("User = ") + user + String(", PW = ") + password);
}

void runQuery(void)
{
  Serial.println("\nRunning SELECT from PROGMEM and printing results\n");
  Serial.println(query);
  
  // Initiate the query class instance
  MySQL_Query query_mem = MySQL_Query(&conn);
  
  // Execute the query with the PROGMEM option
  // KH, check if valid before fetching
  if ( !query_mem.execute(query, true) )
  {
    Serial.println("Querying error");
    return;
  }
  
  // Show the results
  query_mem.show_results();
  // close the query
  query_mem.close();
}

void loop()
{
  Serial.println("Connecting...");
  
  //if (conn.connect(server_addr, server_port, user, password))
  if (conn.connectNonBlocking(server_addr, server_port, user, password) != RESULT_FAIL)
  {
    delay(500);
    runQuery();
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
