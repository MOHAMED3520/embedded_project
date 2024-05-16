/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.10 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.13.11 or later version;
     - for iOS 1.10.3 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT

#include <ESP8266WiFi.h>

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 76 bytes
  { 255,0,0,25,0,69,0,17,0,0,0,25,2,106,200,200,92,1,1,4,
  0,129,9,13,84,18,12,6,66,14,63,68,73,83,84,65,78,67,69,0,
  67,10,37,80,26,19,26,64,14,4,30,25,11,65,11,112,24,23,135,17,
  18,18,118,67,21,163,56,21,134,52,64,14,0,30,25,11 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // output variables
  char DIST_TXT[11]; // string UTF8 end zero
  uint8_t led_01_r; // =0..255 LED Red brightness
  uint8_t led_01_g; // =0..255 LED Green brightness
  uint8_t led_01_b; // =0..255 LED Green brightness
  char text_01[11]; // string UTF8 end zero

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

String received = "";
float val;

void readFloatFromSerial() {
  char ch = 0;

  // Read characters from serial until ',' is detected
  while((ch = Serial.read()) != ',') {
    received += ch;
  }

  // Convert the received string to float
  val = received.toFloat();

  // Clear the received string for the next value
  received = "";
}

void setup() 
{
  RemoteXY_Init (); 
  Serial.begin(9600); // Start the serial communication with the baud rate
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
 

   if (Serial.available() > 0) {
    readFloatFromSerial();
    Serial.println(val);
  }
    
  
dtostrf(val, 0, 3, RemoteXY.DIST_TXT);


  if (val<95){
    RemoteXY.led_01_r=255;
    RemoteXY.led_01_g=0;
    strcpy  (RemoteXY.text_01, "Far");
  }
  else if (val>=95 & val <= 100){
    RemoteXY.led_01_r=255;
    RemoteXY.led_01_g=100;
    strcpy  (RemoteXY.text_01, "Close");
  }
   else if (val>100 ){
    RemoteXY.led_01_g=255;
    RemoteXY.led_01_r=0;
    strcpy  (RemoteXY.text_01, "Arrived");
  }
  else {
    RemoteXY.led_01_r=0;
    RemoteXY.led_01_g=0;
    strcpy  (RemoteXY.text_01, "");
  }

delay(1000);

}
