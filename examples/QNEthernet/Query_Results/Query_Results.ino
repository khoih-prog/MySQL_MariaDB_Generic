/*********************************************************************************************************************************
  Query_Results.ino

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

#include "defines.h"

#include <MySQL_Generic.h>

#define USING_HOST_NAME     true

#if USING_HOST_NAME
  // Optional using hostname, and Ethernet built-in DNS lookup
  //char server[] = "your_account.ddns.net"; // change to your server's hostname/URL
  char server[] = "khoih.ddns.net"; // change to your server's hostname/URL
#else
  IPAddress server(192, 168, 2, 112);
#endif

uint16_t server_port = 5698;    //3306;

char user[]     = "invited-guest";              // MySQL user login username
char password[] = "the-invited-guest";          // MySQL user login password

// Sample query
char query[] = "SELECT * FROM test_arduino.hello_arduino LIMIT 6";

MySQL_Connection conn((Client *)&client);

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect

  MYSQL_DISPLAY2("\nStarting Query_Results on", BOARD_NAME, SHIELD_TYPE);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);

#if USE_NATIVE_ETHERNET
  MYSQL_DISPLAY(F("======== USE_NATIVE_ETHERNET ========"));
#elif USE_QN_ETHERNET
  MYSQL_DISPLAY(F("=========== USE_QN_ETHERNET ==========="));
#endif

#if USE_NATIVE_ETHERNET

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  MYSQL_DISPLAY(F("========================="));

  MYSQL_DISPLAY1("Using mac index =", index);
  MYSQL_DISPLAY1("Connected! IP address:", Ethernet.localIP());

#else

  #if USING_DHCP
    // Start the Ethernet connection, using DHCP
    Serial.print("Initialize Ethernet using DHCP => ");
    Ethernet.begin();
  #else   
    // Start the Ethernet connection, using static IP
    Serial.print("Initialize Ethernet using static IP => ");
    Ethernet.begin(myIP, myNetmask, myGW);
    Ethernet.setDNSServerIP(mydnsServer);
  #endif

  if (!Ethernet.waitForLocalIP(5000))
  {
    MYSQL_DISPLAY(F("Failed to configure Ethernet"));

    if (!Ethernet.linkStatus())
    {
      MYSQL_DISPLAY(F("Ethernet cable is not connected."));
    }

    // Stay here forever
    while (true)
    {
      delay(1);
    }
  }
  else
  {
    MYSQL_DISPLAY1(F("Connected! IP address:"), Ethernet.localIP());
  }

#endif

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

  delay(10000);
}
