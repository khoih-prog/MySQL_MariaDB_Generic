/*********************************************************************************************************************************
  Query_Results_WiFi.ino

  Library for communicating with a MySQL or MariaDB Server

  Based on and modified from Dr. Charles A. Bell's MySQL_Connector_Arduino Library https://github.com/ChuckBell/MySQL_Connector_Arduino
  to support nRF52, SAMD21/SAMD51, SAM DUE, STM32F/L/H/G/WB/MP1, ESP8266, ESP32, etc. boards using W5x00, ENC28J60, LAM8742A Ethernet,
  WiFiNINA, ESP-AT, built-in ESP8266/ESP32 WiFi.

  The library provides simple and easy Client interface to MySQL or MariaDB Server.

  Built by Khoi Hoang https://github.com/khoih-prog/MySQL_MariaDB_Generic
  Licensed under MIT license
 **********************************************************************************************************************************/
/*
  MySQL Connector/Arduino Example : query results

  This example demonstrates how to issue a SELECT query and how to read columns
  and rows from the result set. Study this example until you are familiar with how to
  do this before writing your own sketch to read and consume query results.
  
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

#if !(defined(ESP32))
  #error This code is intended to run on the WT32 boards and ESP32 platform ! Please check your Tools->Board setting.
#endif

#define MYSQL_DEBUG_PORT      Serial

// Debug Level from 0 to 4
#define _MYSQL_LOGLEVEL_      1

#include <WebServer_WT32_ETH01.h>

#include <MySQL_Generic.h>

// Select the IP address according to your local network
IPAddress myIP(192, 168, 2, 232);
IPAddress myGW(192, 168, 2, 1);
IPAddress mySN(255, 255, 255, 0);

// Google DNS Server IP
IPAddress myDNS(8, 8, 8, 8);

#define USING_HOST_NAME     false   //true

#if USING_HOST_NAME
  // Optional using hostname, and Ethernet built-in DNS lookup
  char server[] = "your_account.ddns.net"; // change to your server's hostname/URL
#else
  IPAddress server(192, 168, 2, 112);
#endif

uint16_t server_port = 5698;    //3306;

char user[]             = "invited-guest";      // MySQL user login username
char password[]         = "the-invited-guest";  // MySQL user login password

// Sample query
const char query[] = "SELECT * FROM world.city LIMIT 6";
//const char query[] = "SELECT * FROM test_arduino.hello_arduino LIMIT 6;";

MySQL_Connection conn((Client *)&client);

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  MYSQL_DISPLAY1("\nStarting Query_Results_WT32_ETH01 on", BOARD_NAME);
  MYSQL_DISPLAY(WEBSERVER_WT32_ETH01_VERSION);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);

  // To be called before ETH.begin()
  WT32_ETH01_onEvent();

  //bool begin(uint8_t phy_addr=ETH_PHY_ADDR, int power=ETH_PHY_POWER, int mdc=ETH_PHY_MDC, int mdio=ETH_PHY_MDIO, 
  //           eth_phy_type_t type=ETH_PHY_TYPE, eth_clock_mode_t clk_mode=ETH_CLK_MODE);
  //ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLK_MODE);
  ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER);

  // Static IP, leave without this line to get IP via DHCP
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = 0, IPAddress dns2 = 0);
  ETH.config(myIP, myGW, mySN, myDNS);

  WT32_ETH01_waitForConnect();

  // print out info about the connection:
  MYSQL_DISPLAY1("Connected to network. My IP address is:", ETH.localIP());

  MYSQL_DISPLAY3("Connecting to SQL Server @", server, ", Port =", server_port);
  MYSQL_DISPLAY3("User =", user, ", PW =", password);
}

void runQuery()
{
  MYSQL_DISPLAY("\nRunning SELECT and printing results");
  MYSQL_DISPLAY(query);

  // Initiate the query class instance
  MySQL_Query query_mem = MySQL_Query(&conn);

  // Execute the query

  // KH, check if valid before fetching
  if ( !query_mem.execute(query) )
  {
    MYSQL_DISPLAY("Querying error");
    return;
  }
  //////

  // Fetch the columns and print them
  column_names *cols = query_mem.get_columns();

  for (int f = 0; f < cols->num_fields; f++)
  {
    MYSQL_DISPLAY0(cols->fields[f]->name);

    if (f < cols->num_fields - 1)
    {
      MYSQL_DISPLAY0(", ");
    }
  }
  
  MYSQL_DISPLAY();
  
  // Read the rows and print them
  row_values *row = NULL;

  do
  {
    row = query_mem.get_next_row();

    if (row != NULL)
    {
      for (int f = 0; f < cols->num_fields; f++)
      {
        MYSQL_DISPLAY0(row->values[f]);

        if (f < cols->num_fields - 1)
        {
          MYSQL_DISPLAY0(", ");
        }
      }

      MYSQL_DISPLAY();
    }
  } while (row != NULL);
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
