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
  I2CMux.openChannel(0);
  /* Code to interactive with revealed address on bus */
  I2CMux.closeChannel(0);

  I2CMux.openChannel(1);
  I2CMux.openChannel(2);
   /* Code  to interactive with revealed addresses on bus */
  I2CMux.closeAll();
}