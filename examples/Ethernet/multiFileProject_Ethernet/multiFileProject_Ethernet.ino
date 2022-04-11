/****************************************************************************************************************************
  multiFileProject.ino
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

#define MYSQL_MARIADB_GENERIC_VERSION_MIN_TARGET      "MySQL_MariaDB_Generic v1.7.0"
#define MYSQL_MARIADB_GENERIC_VERSION_MIN             1007000

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "MySQL_Generic.h"

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
  
  Serial.println("\nStart multiFileProject");
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
