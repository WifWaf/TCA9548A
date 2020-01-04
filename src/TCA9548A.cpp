/****************************************************** 
  Arduino library for TCA9548A I2C Multiplexer
  
  Author: Jonathan Dempsey JDWifWaf@gmail.com  
  Version: 1.0.0
  License: Apache 2.0
 *******************************************************/

#include "TCA9548A.h"

#define DEBUG 0  // Enable Debug Mode

TCA9548A::TCA9548A(uint8_t address) : _address(address) {}

void TCA9548A::begin(TwoWire &inWire)
{
    this->myWire = &inWire;
    this->myWire->begin();
}

void TCA9548A::openChannel(uint8_t channel)
{
    uint8_t buff = 0x00;    
    buff = 1 << channel;
    this->_channels |= buff;

    #if DEBUG
    Serial.print("Open Channel: "); Serial.print(channel); Serial.print(" Data: "); Serial.println(buff);
    #endif  

    write(this->_channels);
}

void TCA9548A::closeChannel(uint8_t channel)
{
    uint8_t buff = 0x00;    
    buff = 1 << channel;    
    this->_channels ^= buff;

    #if DEBUG
    Serial.print("Close Channel: "); Serial.print(channel); Serial.print(" Data: "); Serial.println(buff);
    #endif  

    write(this->_channels);
}

void TCA9548A::closeAll()
{
    this->_channels = 0x00;
    write(this->_channels);
}

void TCA9548A::openAll()
{
    this->_channels = 0xFF;
    write(this->_channels);
}

void TCA9548A::writeRegister(uint8_t value)
{
    this->_channels = value;

    #if DEBUG
    Serial.print("Write Control Register: "); Serial.println(value);
    #endif  

    write(this->_channels);
}

void TCA9548A::write(uint8_t inData)
{
    #if DEBUG
    Serial.print("Write Address: "); Serial.print(this->_address, HEX); Serial.print(" Data: "); Serial.println(inData);
    #endif

    this->myWire->beginTransmission(this->_address);
    this->myWire->write(inData);
    this->myWire->endTransmission(true);
}

uint8_t TCA9548A::read()
{
    uint8_t buff = 0;
    this->myWire->requestFrom(this->_address, 1, true);

    if(!this->myWire->available())
        return 255;

    buff = this->myWire->read();

    #if DEBUG
    Serial.print("Read Address: "); Serial.print(this->_address, HEX); Serial.print(" Data: "); Serial.println(buff);
    #endif
    
    return buff;
}