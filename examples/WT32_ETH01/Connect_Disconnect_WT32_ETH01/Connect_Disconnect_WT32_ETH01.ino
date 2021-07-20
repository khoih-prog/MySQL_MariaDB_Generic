/*********************************************************************************************************************************
  Connect_Disconnect_WiFi.ino

  Library for communicating with a MySQL or MariaDB Server

  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.

  The library provides simple and easy Client interface to MySQL or MariaDB Server.

  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
  Version: 1.2.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      13/08/2020 Initial coding/porting to support nRF52, SAM DUE and SAMD21/SAMD51 boards using W5x00 Ethernet
                                  (Ethernet, EthernetLarge, Ethernet2, Ethernet3 library), WiFiNINA and ESP8266/ESP32-AT shields
  1.0.1   K Hoang      18/08/2020 Add support to Ethernet ENC28J60. Fix bug, optimize code.
  1.0.2   K Hoang      20/08/2020 Fix crashing bug when timeout. Make code more error-proof. Drop support to ESP8266_AT_Webserver.
  1.0.3   K Hoang      02/10/2020 Add support to Ethernet ENC28J60 using new EthernetENC library.
  1.1.0   K Hoang      08/06/2021 Add support to RP2040-based boards such as Nano_RP2040_Connect, RASPBERRY_PI_PICO. etc.
  1.2.0   K Hoang      20/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720A)
 **********************************************************************************************************************************/
/*
  MySQL Connector/Arduino Example : connect and disconnect (close)

  This example demonstrates how to use the connection to open at the start
  of a loop, perform some query, then close the connection. Use this technique
  for solutions that must sleep for a long period or otherwise require
  additional processing or delays. The connect/close pair allow you to
  control how long the connection is open and thus reduce the amount of
  time a connection is held open. It also helps for lossy connections.

  This example demonstrates how to connect to a MySQL server and specifying
  the default database when connecting.

  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

  INSTRUCTIONS FOR USE

  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Connect a USB cable to your Arduino
  4) Select the correct board and port
  5) Compile and upload the sketch to your Arduino
  6) Once uploaded, open Serial Monitor (use 115200 speed) and observe

  Created by: Dr. Charles A. Bell
*/

#if !(defined(ESP32))
  #error This code is intended to run on the WT32 boards and ESP32 platform ! Please check your Tools->Board setting.
#endif

#define MYSQL_DEBUG_PORT      Serial

// Debug Level from 0 to 4
#define _MYSQL_LOGLEVEL_      1

#include <WebServer_WT32_ETH01.h>

#include <MySQL_Generic_WiFi.h>

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

IPAddress server_addr(192, 168, 2, 112);
uint16_t server_port = 5698;    //3306;

char user[]             = "invited-guest";      // MySQL user login username
char password[]         = "the-invited-guest";  // MySQL user login password

MySQL_Connection conn((Client *)&client);
MySQL_Query query = MySQL_Query(&conn);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  MYSQL_DISPLAY1("\nStarting Connect_Disconnect_WT32_ETH01 on", BOARD_NAME);
  MYSQL_DISPLAY(WEBSERVER_WT32_ETH01_VERSION);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);

  //bool begin(uint8_t phy_addr=ETH_PHY_ADDR, int power=ETH_PHY_POWER, int mdc=ETH_PHY_MDC, int mdio=ETH_PHY_MDIO, 
  //           eth_phy_type_t type=ETH_PHY_TYPE, eth_clock_mode_t clk_mode=ETH_CLK_MODE);
  //ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  WT32_ETH01_onEvent();

  WT32_ETH01_waitForConnect();

  // print out info about the connection:
  MYSQL_DISPLAY1("Connected to network. My IP address is:", ETH.localIP());
}

void runQuery()
{
  MYSQL_DISPLAY("Running a query: SELECT * FROM test_arduino.hello_arduino LIMIT 6;");
  
  // Execute the query
  // KH, check if valid before fetching
  if ( !query.execute("SELECT * FROM test_arduino.hello_arduino LIMIT 6;") )
  {
    MYSQL_DISPLAY("Querying error");
    return;
  }
  
  query.show_results();             // show the results
  query.close();                    // close the query
}

void loop()
{
  MYSQL_DISPLAY("Connecting...");
  
  //if (conn.connect(server_addr, server_port, user, password))
  if (conn.connectNonBlocking(server_addr, server_port, user, password) != RESULT_FAIL)
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
