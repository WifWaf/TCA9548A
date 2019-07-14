/****************************************************** 
  Arduino library for TCA9548A I2C Multiplexer
  
  Author: Jonathan Dempsey JDWifWaf@gmail.com  
  Version: 1.0.0
  License: Apache 2.0
 *******************************************************/

#ifndef TCA9548A_H
#define TCA9548A_h

#include <Arduino.h>
#include <Wire.h>

#define DEBUG 0  // Enable Debug Mode

/* Channel hex values for writeRegister() function */
#define TCA_CHANNEL_0 0x1
#define TCA_CHANNEL_1 0x2
#define TCA_CHANNEL_2 0x4
#define TCA_CHANNEL_3 0x8
#define TCA_CHANNEL_4 0x10
#define TCA_CHANNEL_5 0x20
#define TCA_CHANNEL_6 0x40
#define TCA_CHANNEL_7 0x80

class TCA9548A
{
    public:
        TCA9548A(uint8_t address = 0x70);  // Default IC Address

        void begin(uint8_t sda, uint8_t sdl, TwoWire &inWire = Wire); // Default TwoWire Instance
        void openChannel(uint8_t channel);
        void closeChannel(uint8_t channel);
        void writeRegister(uint8_t value);
        inline byte readRegister() { return (byte)read(); }
        void closeAll();
        void openAll();
        
    protected:
    private:
        TwoWire *myWire;
        uint8_t _sda, _sdl, _address;
        uint8_t _channels;

        void write(uint8_t inData);
        uint8_t read();
};

#endif