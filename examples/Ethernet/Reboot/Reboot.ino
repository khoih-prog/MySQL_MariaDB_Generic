/*********************************************************************************************************************************
  Reboot.ino

  Library for communicating with a MySQL or MariaDB Server

  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.

  The library provides simple and easy Client interface to MySQL or MariaDB Server.

  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
  Version: 1.0.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/08/2020 Initial coding/porting to support nRF52, SAM DUE and SAMD21/SAMD51 boards using W5x00 Ethernet
                                  (using Ethernet, EthernetLarge, Ethernet2, Ethernet3 library) and WiFiNINA
 **********************************************************************************************************************************/

/*
  MySQL Connector/Arduino Example : reboot if connection lost

  This example demonstrates how to reboot an Arduino if connection to the
  server is lost for a period of time.

  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

  INSTRUCTIONS FOR USE

  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Connect a USB cable to your Arduino
  4) Select the correct board and port
  5) Compile and upload the sketch to your Arduino
  6) Once uploaded, open Serial Monitor (use 115200 speed) and observe

  To test the reboot, unplug your Ethernet cable once you see "disconnected"
  then wait for the timeout. Once the Arduino reboots, plug the cable in again
  and you should see the query processing resume.

  Created by: Dr. Charles A. Bell
*/

#include "defines.h"

#include <MySQL_Generic_Ethernet.h>

// Select the static Local IP address according to your local network
IPAddress ip(192, 168, 2, 222);

IPAddress server_addr(192, 168, 2, 112);
uint16_t server_port = 5698;    //3306;

char user[]     = "invited-guest";              // MySQL user login username
char password[] = "the-invited-guest";          // MySQL user login password

MySQL_Connection conn((Client *)&client);
MySQL_Query query = MySQL_Query(&conn);

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect

  Serial.print("\nStarting Reboot on " + String(BOARD_NAME));

#if USE_ETHERNET
  Serial.println(" using W5x00/Ethernet Library");
#elif USE_ETHERNET_LARGE
  Serial.println(" using W5x00/EthernetLarge Library");
#elif USE_ETHERNET2
  Serial.println(" using W5x00/Ethernet2 Library");
#elif USE_ETHERNET3
  Serial.println(" using W5x00/Ethernet3 Library");
#elif USE_ETHERNET_LAN8742A
  Serial.println(" using LAN8742A/STM32Ethernet Library");
#elif USE_ETHERNET_ESP8266
  Serial.println(" using W5x00/Ethernet_ESP8266 Library");
#elif USE_CUSTOM_ETHERNET
  Serial.println(" using W5x00/Ethernet Custom Library");
#else
  // Backup if none is selected
  Serial.println(" using W5x00/Ethernet Library");
#endif

  MYSQL_LOGWARN(F("========================="));
  MYSQL_LOGWARN(F("Default SPI pinout:"));
  MYSQL_LOGWARN1(F("MOSI:"), MOSI);
  MYSQL_LOGWARN1(F("MISO:"), MISO);
  MYSQL_LOGWARN1(F("SCK:"),  SCK);
  MYSQL_LOGWARN1(F("SS:"),   SS);
  MYSQL_LOGWARN(F("========================="));

#if defined(ESP8266)
  // For ESP8266, change for other boards if necessary
#ifndef USE_THIS_SS_PIN
#define USE_THIS_SS_PIN   D2    // For ESP8266
#endif

  MYSQL_LOGWARN1(F("ESP8266 setCsPin:"), USE_THIS_SS_PIN);

#if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 )
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

#endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )

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

  MYSQL_LOGWARN1(F("ESP32 setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
#if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 )
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

#endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )

#else   //defined(ESP8266)
  // unknown board, do nothing, use default SS = 10
#ifndef USE_THIS_SS_PIN
#define USE_THIS_SS_PIN   10    // For other boards
#endif

  MYSQL_LOGWARN1(F("Unknown board setCsPin:"), USE_THIS_SS_PIN);

  // For other boards, to change if necessary
#if ( USE_ETHERNET || USE_ETHERNET_LARGE || USE_ETHERNET2 )
  // Must use library patch for Ethernet, Ethernet2, EthernetLarge libraries

  Ethernet.init (USE_THIS_SS_PIN);

#elif USE_ETHERNET3
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
#ifndef ETHERNET3_MAX_SOCK_NUM
#define ETHERNET3_MAX_SOCK_NUM      4
#endif

  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);

#endif  //( USE_ETHERNET || USE_ETHERNET2 || USE_ETHERNET3 || USE_ETHERNET_LARGE )

#endif    //defined(ESP8266)

  // start the ethernet connection and the server:
  // Use Static IP
  //Ethernet.begin(mac, ip);
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;

  Ethernet.begin(mac[index]);

  // Just info to know how to connect correctly
  MYSQL_LOGWARN(F("========================="));
  MYSQL_LOGWARN(F("Currently Used SPI pinout:"));
  MYSQL_LOGWARN1(F("MOSI:"), MOSI);
  MYSQL_LOGWARN1(F("MISO:"), MISO);
  MYSQL_LOGWARN1(F("SCK:"),  SCK);
  MYSQL_LOGWARN1(F("SS:"),   SS);
  MYSQL_LOGWARN(F("========================="));

  Serial.print("Using mac index = ");
  Serial.println(index);

  Serial.print("Connected! IP address: ");
  Serial.println(Ethernet.localIP());
}

// Begin reboot code
int num_fails;                  // variable for number of failure attempts
#define MAX_FAILED_CONNECTS 5   // maximum number of failed connects to MySQL

void soft_reset()
{
#if ETHERNET_USE_SAMD
#if ( defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) || defined(__SAMD51G19A__)  )
  // For SAMD51
  // see Table 17-5 Timeout Period (valid values 0-11)
  WDT->CONFIG.reg = 5;
  WDT->CTRLA.reg = WDT_CTRLA_ENABLE;
  // To check if OK or bit.ENABLE/CLEAR
  while (WDT->SYNCBUSY.bit.WEN == 1);

  // use the WDT watchdog timer to force a system reset.
  WDT->CLEAR.reg = 0x00;
  // To check if OK or bit.ENABLE/CLEAR
  while (WDT->SYNCBUSY.bit.WEN == 1);
#else
  // For SAMD21, etc
  // see Table 17-5 Timeout Period (valid values 0-11)
  WDT->CONFIG.reg = 5;
  WDT->CTRL.reg = WDT_CTRL_ENABLE;
  while (WDT->STATUS.bit.SYNCBUSY == 1);

  // use the WDT watchdog timer to force a system reset.
  WDT->CLEAR.reg = 0x00;
  while (WDT->STATUS.bit.SYNCBUSY == 1);
#endif
#elif ETHERNET_USE_NRF52
  //delay(1000);
  // Restart for nRF52
  NVIC_SystemReset();
#elif ETHERNET_USE_SAMDUE
  void(*resetFunc)(void) = 0;
  resetFunc();
#elif ETHERNET_USE_STM32
  void(*resetFunc)(void) = 0;
  resetFunc();

#elif ETHERNET_USE_TEENSY
#if defined(__IMXRT1062__)
  // Teensy 4.1/4.0
  SCB_AIRCR = 0x05FA0004; //write value for restart for Teensy
#else
  void(*resetFunc)(void) = 0;
  resetFunc();
#endif
#endif
}
// End reboot code

void loop()
{
  if (conn.connected())
  {
    Serial.println("Running a query: SHOW DATABASES ");
    query.execute("SHOW DATABASES");  // execute a query
    query.show_results();             // show the results
    query.close();                    // close the cursor
    conn.close();                     // close the connection
    num_fails = 0;                    // reset failures
    
    delay(10000);
  }
  else
  {
    Serial.print("Connecting to SQL Server @ ");
    Serial.print(server_addr);
    Serial.println(String(", Port = ") + server_port);
    Serial.println(String("User = ") + user + String(", PW = ") + password);

    //if (conn.connect(server_addr, server_port, user, password))
    if (conn.connectNonBlocking(server_addr, server_port, user, password) != RESULT_FAIL)
    {
      delay(500);
    }
    else
    {
      num_fails++;
      Serial.println("Connect failed!");

      if (num_fails == MAX_FAILED_CONNECTS)
      {
        Serial.println("Ok, that's it. I'm outta here. Rebooting...");
        delay(2000);
        // Here we tell the Arduino to reboot by redirecting the instruction
        // pointer to the "top" or position 0. This is a soft reset and may
        // not solve all hardware-related lockups.
        soft_reset();
      }
    }
  }

  Serial.println("\nSleeping...");
  Serial.println("==========================================");
}
