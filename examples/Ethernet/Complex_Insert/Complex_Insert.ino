/*********************************************************************************************************************************
  Complex_Insert.ino
      
  Library for communicating with a MySQL or MariaDB Server
  
  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.

  The library provides simple and easy Client interface to MySQL or MariaDB Server.
  
  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
/*
  MySQL Connector/Arduino Example : complex insert

  This example demonstrates how to issue an INSERT query to store data in a
  table using data from variables in our sketch. In this case, we supply the
  values dynamically.

  This sketch simulates storing data from a sensor in a table.

  For this, we will create a special database and table for testing.
  The following are the SQL commands you will need to run in order to setup
  your database for running this sketch.

  CREATE DATABASE test_arduino;
  CREATE TABLE test_arduino.hello_sensor (
    num integer primary key auto_increment,
    message char(40),
    sensor_num integer,
    value float,
    recorded timestamp
  );

  Here we have a table that contains an auto_increment primary key, a text
  field, a field to identify the sensor, the value read, and timestamp of
  the recorded data.

  Note: Since this sketch uses test data, we place the INSERT in the setup()
        method so that it runs only once. Typically, you would have the
        INSERT in the loop() method after your code to read from the sensor.

  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

  INSTRUCTIONS FOR USE

  1) Create the database and table as shown above.
  2) Change the address of the server to the IP address of the MySQL server
  3) Change the user and password to a valid MySQL user and password
  4) Connect a USB cable to your Arduino
  5) Select the correct board and port
  6) Compile and upload the sketch to your Arduino
  7) Once uploaded, open Serial Monitor (use 115200 speed) and observe
  8) After the sketch has run for some time, open a mysql client and issue
     the command: "SELECT * FROM test_arduino.hello_sensor" to see the data
     recorded. Note the field values and how the database handles both the
     auto_increment and timestamp fields for us. You can clear the data with
     "DELETE FROM test_arduino.hello_sensor".

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

char user[]             = "invited-guest";              // MySQL user login username
char password[]         = "the-invited-guest";          // MySQL user login password

char default_database[] = "test_arduino";           //"test_arduino";
char default_table[]    = "hello_sensor";         //"test_arduino";

// Sample query
char INSERT_DATA[] = "INSERT INTO %s.%s (message, sensor_num, value) VALUES ('%s',%d,%s)";
                 
char query[128];
char temperature[10];

MySQL_Connection conn((Client *)&client);

#if !( ESP32 || ESP8266 || defined(CORE_TEENSY) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3) || defined(STM32F4) || defined(STM32F7) || ( defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED) ) ) 

char *dtostrf(double val, signed char width, unsigned char prec, char *sout)
{
  char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;
}
#endif

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect

  MYSQL_DISPLAY3("\nStarting Complex_Insert on", BOARD_NAME, ", with", SHIELD_TYPE);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);

#if !(USE_ETHERNET_PORTENTA_H7)

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
  
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
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
  
  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
  
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
  
  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET_LARGE || USE_ETHERNET_ENC )

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
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // ESP32 => GPIO2,4,5,13,15,21,22 OK with Ethernet, Ethernet2, EthernetLarge
    // ESP32 => GPIO2,4,5,15,21,22 OK with Ethernet3
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);

  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
  
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);

  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET_LARGE  || USE_ETHERNET_ENC )

#elif ETHERNET_USE_RPIPICO

  pinMode(USE_THIS_SS_PIN, OUTPUT);
  digitalWrite(USE_THIS_SS_PIN, HIGH);
  
  // ETHERNET_USE_RPIPICO, use default SS = 5 or 17
  #ifndef USE_THIS_SS_PIN
    #if defined(ARDUINO_ARCH_MBED)
      #define USE_THIS_SS_PIN   5     // For Arduino Mbed core
    #else  
      #define USE_THIS_SS_PIN   17    // For E.Philhower core
    #endif
  #endif

  MYSQL_LOGERROR1(F("RPIPICO setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, EthernetLarge libraries
    // For RPI Pico using Arduino Mbed RP2040 core
    // SCK: GPIO2,  MOSI: GPIO3, MISO: GPIO4, SS/CS: GPIO5
    // For RPI Pico using E. Philhower RP2040 core
    // SCK: GPIO18,  MOSI: GPIO19, MISO: GPIO16, SS/CS: GPIO17
    // Default pin 5/17 to SS/CS
  
    //Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (USE_THIS_SS_PIN);
  
  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
  
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
    
  #endif    //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )
  
#else   //defined(ESP8266)
  // unknown board, do nothing, use default SS = 10
  #ifndef USE_THIS_SS_PIN
    #define USE_THIS_SS_PIN   10    // For other boards
  #endif

  MYSQL_LOGERROR3(F("Board :"), BOARD_NAME, F(", setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
  #if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 || USE_ETHERNET_ENC )
    // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries
  
    Ethernet.init (USE_THIS_SS_PIN);

  #elif USE_ETHERNET3
    // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
    #ifndef ETHERNET3_MAX_SOCK_NUM
      #define ETHERNET3_MAX_SOCK_NUM      4
    #endif
  
    Ethernet.setCsPin (USE_THIS_SS_PIN);
    Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
  
  #endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET_LARGE || USE_ETHERNET_ENC )

#endif    //defined(ESP8266)

  // Just info to know how to connect correctly
  MYSQL_LOGERROR(F("========================================="));
  MYSQL_LOGERROR(F("Currently Used SPI pinout:"));
  MYSQL_LOGERROR1(F("MOSI:"), MOSI);
  MYSQL_LOGERROR1(F("MISO:"), MISO);
  MYSQL_LOGERROR1(F("SCK:"),  SCK);
  MYSQL_LOGERROR1(F("SS:"),   SS);
  MYSQL_LOGERROR(F("========================================="));

#endif    // #if !(USE_ETHERNET_PORTENTA_H7)

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  MYSQL_DISPLAY1("Using mac index =", index);
  MYSQL_DISPLAY1("Connected! IP address:", Ethernet.localIP());

  MYSQL_DISPLAY3("Connecting to SQL Server @", server, ", Port =", server_port);
  MYSQL_DISPLAY3("User =", user, ", PW =", password);
  MYSQL_DISPLAY3("DB =", default_database, ", Table =", default_table);
}

void runInsert()
{
  // Initiate the query class instance
  MySQL_Query query_mem = MySQL_Query(&conn);

  if (conn.connected())
  {
    // Save
    dtostrf(50.125, 1, 1, temperature);
    sprintf(query, INSERT_DATA, default_database, default_table, "test sensor", 24, temperature);
    
    // Execute the query
    MYSQL_DISPLAY(query);

    // KH, check if valid before fetching
    if ( !query_mem.execute(query) )
    {
      MYSQL_DISPLAY("Complex Insert error");
    }
    else
    {
      MYSQL_DISPLAY("Complex Data Inserted.");
    }
  }
  else
  {
    MYSQL_DISPLAY("Disconnected from Server. Can't insert.");
  }
}

void loop()
{
  MYSQL_DISPLAY("Connecting...");
  
  //if (conn.connect(server, server_port, user, password))
  if (conn.connectNonBlocking(server, server_port, user, password) != RESULT_FAIL)
  {
    delay(500);
    runInsert();
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
