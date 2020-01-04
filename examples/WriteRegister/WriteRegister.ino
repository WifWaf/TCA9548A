#include <Arduino.h>
#include "TCA9548A.h"

TCA9548A I2CMux;     // Address can be passed into the constructor

void setup() {
  Serial.begin(9600);             // Define baud rate
  I2CMux.begin(Wire);             // TwoWire isntance can be passed here as 3rd argument

  I2CMux.closeAll();              // Set a base state which we know (also the default state on power on)
}

void loop() 
{
  uint8_t buff = 0x00;

  Serial.println("\n--- Calculate Channel Byte (153) ---");

  delay(500);

  Serial.println("Adding Channels 0, 3, 4 & 7");
  buff |= TCA_CHANNEL_0;
  buff |= TCA_CHANNEL_3;
  buff |= TCA_CHANNEL_4;
  buff |= TCA_CHANNEL_7;

  delay(500);

  Serial.print("Writing Register: ");
  Serial.println(buff);
  I2CMux.writeRegister(buff);

  delay(500);

  Serial.print("Reading Register: ");
  Serial.println(I2CMux.readRegister());

  delay(500);

  Serial.println("Closing Channels");
  I2CMux.closeAll();
  
  while(1==1);
}