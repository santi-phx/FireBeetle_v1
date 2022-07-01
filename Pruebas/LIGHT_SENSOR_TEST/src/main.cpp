// PRUEBA UNITARIA SENSOR INTENSIDAD LUMINICA MAX44009 en tarjeta GY-49

#include <Arduino.h>

#include <Wire.h>    //include library
#define Address 0x4A // GY-49 I2C Address is 0x4A(74)

void setup()
{
  // configure gy-49 module
  Wire.begin();                    // initialize library
  Serial.begin(9600);              // start serial monitor
  Wire.beginTransmission(Address); // start wire iic transmission
  Wire.write(0x02);                // Select configuration register
  Wire.write(0x40);                // Continuous mode, Integration time = 800 ms
  Wire.endTransmission();          // Stop iic transmission
  delay(300);
}

void loop()
{
  unsigned int data[2];
  Wire.beginTransmission(Address); // start wire iic transmission
  Wire.write(0x03);                // Select data register
  Wire.endTransmission();          // Stop iic transmission
  Wire.requestFrom(Address, 2);    // Request 2 bytes of data
  // Read 2 bytes of data
  // luminance msb, luminance lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  // Convert the data to lux
  int exponent = (data[0] & 0xF0) >> 4;
  int mantissa = ((data[0] & 0x0F) << 4) | (data[1] & 0x0F);
  float luminance = pow(2, exponent) * mantissa * 0.045;

  // Output data to serial monitor
  Serial.print("Ambient Light Luminance :");
  Serial.print(luminance);
  Serial.println(" lux");
  delay(300);
}