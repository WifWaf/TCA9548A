#include <Arduino.h>
#include "TCA9548A.h"

TCA9548A I2CMux;                  // Address can be passed into the constructor

void setup() {
  Serial.begin(9600);             // Define baud rate

  //  Wire.setPins(21, 22);       // ESP32 users, use setPins(sda, scl) if customised, *before* passing Wire to the library (the line below). 
  I2CMux.begin(Wire);             // Wire instance is passed to the library

  I2CMux.closeAll();              // Set a base state which we know (also the default state on power on)
}

void loop() 
{
  Serial.println("--- Opening single channels --- ");
  for(uint8_t x = 0; x < 8; x++)
  {
    Serial.print("Opening << Channel: ");   
    Serial.println(x); 

    I2CMux.openChannel(x);    // Open channel
    
    delay(500);

    Serial.print("Register = Value: ");
    Serial.println(I2CMux.readRegister());   // Note here, register does not translate directly to channel number

    delay(500);  

    Serial.print("Closing >> Channel: ");   
    Serial.println(x); 

    I2CMux.closeChannel(x);   // Close channel

    delay(500); 
  }
  
  Serial.println("--- Opening multiple channels --- ");
  for(uint8_t x = 0; x < 8; x++)
  {
    Serial.print("Opening << Channel: ");   
    Serial.println(x); 

    I2CMux.openChannel(x);   // Open channel

    delay(500);

    Serial.print("Register = Value: ");
    Serial.println(I2CMux.readRegister());

    delay(500);
  }
  Serial.println("Closing >> channels");  
  I2CMux.closeAll();        // Close all

  delay(500);
}
