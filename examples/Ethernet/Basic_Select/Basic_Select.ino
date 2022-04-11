/*********************************************************************************************************************************
  Basic_Select.ino
      
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.

  The library provides simple and easy Client interface to MySQL or MariaDB Server.
  
  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/

/*
  MySQL Connector/Arduino Example : basic select

  This example demonstrates how to issue a SELECT query with no parameters
  and use the data returned. For this, we use the Cursor class to execute
  the query and get the results.

  It demonstrates who methods for running queries. The first allows you to
  allocate memory for the cursor and later reclaim it, the second shows how
  to use a single instance of the cursor use throughout a sketch.

  NOTICE: You must download and install the World sample database to run
          this sketch unaltered. See http://dev.mysql.com/doc/index-other.html.

  CAUTION: Don't mix and match the examples. Use one or the other in your
           own sketch -- you'll get compilation errors at the least.

  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

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

#include <MySQL_Generic.h>

// Select the static Local IP address according to your local network
IPAddress ip(192, 168, 2, 222);

#define USING_HOST_NAME     false   //true

#if USING_HOST_NAME
  // Optional using hostname, and Ethernet built-in DNS lookup
  char server[] = "your_account.ddns.net"; // change to your server's hostname/URL
#else
  IPAddress server(192, 168, 2, 112);
#endif

uint16_t server_port = 5698;    //3306;

char user[]     = "invited-guest";              // MySQL user login username
char password[] = "the-invited-guest";          // MySQL user login password

char default_database[] = "world";              //"test_arduino";
char default_table[]    = "city";               //"test_arduino";

String default_column   = "population"; 
String default_value    = "Toronto"; 

String query = String("SELECT ") + default_column + " FROM " + default_database + "." + default_table 
                 + " WHERE name = '" + default_value + "'";

MySQL_Connection conn((Client *)&client);
// Create an instance of the cursor passing in the connection
MySQL_Query sql_query = MySQL_Query(&conn);

void initEthernet()
{
#if !(USE_ETHERNET_PORTENTA_H7 || USE_ETHERNET_LAN8742A || USE_ETHERNET_LAN8720)

  MYSQL_LOGERROR(F("========================================="));
  MYSQL_LOGERROR(F("Default SPI pinout:"));
  MYSQL_LOGERROR1(F("MOSI:"), MOSI);
  MYSQL_LOGERROR1(F("MISO:"), MISO);
  MYSQL_LOGERROR1(F("SCK:"),  SCK);
  MYSQL_LOGERROR1(F("SS:"),   SS);
  MYSQL_LOGERROR(F("========================================="));

#if defined(ESP8266)
  // For ESP8266, change for other boards if necessary
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   D2    // For ESP8266
  #endif
  
    MYSQL_LOGERROR1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);
  
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // For ESP8266
    // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
    // Ethernet           0                 X            X            X            X        0
    // Ethernet2          X                 X            X            X            X        0
    // Ethernet3          X                 X            X            X            X        0
    // EthernetLarge      X                 X            X            X            X        0
    // Ethernet_ESP8266   0                 0            0            0            0        0
    // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
    // Must use library patch for Ethernet, EthernetLarge libraries
    Ethernet.init (USE_THIS_SS_PIN);
   
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#elif defined(ESP32)

  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   22    // For ESP32
  #endif

  MYSQL_LOGERROR1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
    // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);

  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#elif ETHERNET_USE_RPIPICO

  pinMode(USE_THIS_SS_PIN, OUTPUT);
  digitalWrite(USE_THIS_SS_PIN, HIGH);
  
  // ETHERNET_USE_RPIPICO, use default SS = 5 or 17
  #ifndef USE_THIS_SS_PIN
    #if defined(ARDUINO_ARCH_MBED)
      #define USE_THIS_SS_PIN   17     // For Arduino Mbed core
    #else  
      #define USE_THIS_SS_PIN   17    // For E.Philhower core
    #endif
  #endif

  MYSQL_LOGERROR1(F("RPIPICO setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // For RPI Pico using Arduino Mbed RP2040 core
    // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
    // For RPI Pico using E. Philhower RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
    // Default pin 5/17 to SS/CS
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
    
  #endif    //( USE_ETHERNET_GENERIC || USE_ETHERNET_LARGE )
  
#else   //defined(ESP8266)
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif

  MYSQL_LOGERROR3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
  
    Ethernet.init (USE_THIS_SS_PIN);
 
  #endif  //( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )

#endif    //defined(ESP8266)

#if !(USE_ETHERNET_PORTENTA_H7 || USE_ETHERNET_LAN8742A || USE_ETHERNET_LAN8720)
    // Just info to know how to connect correctly
  #if defined(CUR_PIN_MISO)
    MYSQL_LOGERROR(F("Currently Used SPI pinout:"));
    MYSQL_LOGERROR1(F("MOSI:"), CUR_PIN_MOSI);
    MYSQL_LOGERROR1(F("MISO:"), CUR_PIN_MISO);
    MYSQL_LOGERROR1(F("SCK:"),  CUR_PIN_SCK);
    MYSQL_LOGERROR1(F("SS:"),   CUR_PIN_SS);
  #else
    MYSQL_LOGERROR(F("Currently Used SPI pinout:"));
    MYSQL_LOGERROR1(F("MOSI:"), MOSI);
    MYSQL_LOGERROR1(F("MISO:"), MISO);
    MYSQL_LOGERROR1(F("SCK:"),  SCK);
    MYSQL_LOGERROR1(F("SS:"),   SS);
  #endif
  
  MYSQL_LOGERROR(F("========================="));
#endif

#endif    // #if !(USE_ETHERNET_PORTENTA_H7 || USE_ETHERNET_LAN8742A || USE_ETHERNET_LAN8720)

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  MYSQL_DISPLAY1("Using mac index =", index);
  MYSQL_DISPLAY1("Connected! IP address:", Ethernet.localIP());
}

void setup()
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000); // wait for serial port to connect

  MYSQL_DISPLAY3("\nStarting Basic_Select on", BOARD_NAME, ", with", SHIELD_TYPE);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);

  initEthernet();

  MYSQL_DISPLAY3("Connecting to SQL Server @", server, ", Port =", server_port);
  MYSQL_DISPLAY5("User =", user, ", PW =", password, ", DB =", default_database);
}

void runQuery()
{
  row_values *row = NULL;
  long head_count = 0;

  MYSQL_DISPLAY("1) Demonstrating using a dynamically allocated query.");
  // Initiate the query class instance
  MySQL_Query query_mem = MySQL_Query(&conn);
  
  // Execute the query
  MYSQL_DISPLAY(query);

  // Execute the query
  // KH, check if valid before fetching
  if ( !query_mem.execute(query.c_str()) )
  {
    MYSQL_DISPLAY("Querying error");
    return;
  }
  
  // Fetch the columns (required) but we don't use them.
  //column_names *columns = query_mem.get_columns();
  query_mem.get_columns();

  // Read the row (we are only expecting the one)
  do 
  {
    row = query_mem.get_next_row();
    
    if (row != NULL) 
    {
      head_count = atol(row->values[0]);
    }
  } while (row != NULL);

  // Show the result
  MYSQL_DISPLAY1("  Toronto pop =", head_count);

  delay(500);

  MYSQL_DISPLAY("2) Demonstrating using a local, global query.");
  
  // Execute the query
  MYSQL_DISPLAY(query);
  sql_query.execute(query.c_str());
  
  // Fetch the columns (required) but we don't use them.
  sql_query.get_columns();
  
  // Read the row (we are only expecting the one)
  do 
  {
    row = sql_query.get_next_row();
    if (row != NULL) 
    {
      head_count = atol(row->values[0]);
    }
  } while (row != NULL);
  
  // Now we close the cursor to free any memory
  sql_query.close();

  // Show the result but this time do some math on it
  MYSQL_DISPLAY1("  Toronto pop =", head_count);
  MYSQL_DISPLAY1("  Toronto pop increased by 11725 =", head_count + 11725);
}

void loop()
{
  MYSQL_DISPLAY("Connecting...");
  
  //if (conn.connect(server, server_port, user, password))
  if (conn.connectNonBlocking(server, server_port, user, password) != RESULT_FAIL)
  {
    delay(500);
    runQuery();
    conn.close();                     // close the connection
  } 
  else 
  {
    MYSQL_DISPLAY("\nConnect failed. Trying again on next iteration.");
  }

  MYSQL_DISPLAY("\nSleeping...");
  MYSQL_DISPLAY("================================================");
 
  delay(60000);
}
