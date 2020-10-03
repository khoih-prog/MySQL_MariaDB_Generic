/*********************************************************************************************************************************
  MySQL_Generic_Query.h
  
  This header file defines a query class for running queries on a MySQL/MariaDB server. 
  You can issue any command using SQL statements for inserting or retrieving data.
     
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

/*********************************************************************************************************************************
  Copyright (c) 2012, 2016 Oracle and/or its affiliates. All rights reserved.

  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA

 **********************************************************************************************************************************/

#ifndef MYSQL_GENERIC_QUERY_H
#define MYSQL_GENERIC_QUERY_H

#include "MySQL_Generic_Debug.h"

#include <MySQL_Generic_Connection.h>

// Comment this if you don't need SELECT queries to reduce memory footprint of the library.
#define WITH_SELECT          

#define MAX_FIELDS    0x20   // Maximum number of fields. Reduce to save memory. Default=32

#ifdef WITH_SELECT

// Structure for retrieving a field (minimal implementation).
typedef struct 
{
  char *db;
  char *table;
  char *name;
} field_struct;

// Structure for storing result set metadata.
typedef struct 
{
  int num_fields;     // actual number of fields
  field_struct *fields[MAX_FIELDS];
} column_names;

// Structure for storing row data.
typedef struct 
{
  char *values[MAX_FIELDS];
} row_values;

#endif  // WITH_SELECT

class MySQL_Query 
{
  public:
    MySQL_Query(MySQL_Connection *connection);
    ~MySQL_Query();
    bool execute(const char *query, bool progmem = false);

  private:
    bool execute_query(int query_len);
    
#ifdef WITH_SELECT

  public:
    void close();
    column_names  *get_columns();
    row_values    *get_next_row();
    void          show_results();
    
    int get_rows_affected() 
    {
      return rows_affected;
    }
    
    int get_last_insert_id() 
    {
      return last_insert_id;
    }

  private:
    void  free_columns_buffer();
    void  free_row_buffer();
    bool  clear_ok_packet();

    char  *read_string(int *offset);
    int   get_field(field_struct *fs);
    int   get_row();
    bool  get_fields();
    int   get_row_values();
    column_names *query_result();

    bool          columns_read;
    int           num_cols;
    
    column_names  columns;
    row_values    row;
    
    int           rows_affected;
    int           last_insert_id;
    
#endif

    MySQL_Connection *conn;
};

#include <MySQL_Generic_Query_Impl.h>


#endif    // MYSQL_GENERIC_QUERY_H
