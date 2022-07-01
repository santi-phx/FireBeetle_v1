// PRUEBA SENSOR TEMPERATURA Y LUZ INTEGRADOS CON MODO DEEP SLEEP.

#include <OneWire.h>
#include <DallasTemperature.h>

#define SENSOR_PIN 19 // ESP32 pin GIOP21 connected to DS18B20 sensor's DQ pin
#include <Wire.h>     //include library
#define Address 0x4A  // GY-49 I2C Address is 0x4A(74)

OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

float tempC; // temperature in Celsius
float tempF; // temperature in Fahrenheit

void setup()
{

  Wire.begin();                    // initialize library
  Serial.begin(9600);              // initialize serial
  DS18B20.begin();                 // initialize the DS18B20 sensor
  Wire.beginTransmission(Address); // start wire iic transmission
  Wire.write(0x02);                // Select configuration register
  Wire.write(0x40);                // Continuous mode, Integration time = 800 ms
  Wire.endTransmission();          // Stop iic transmission
  delay(300);
}

void loop()
{
  // LIGHT
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

  // TEMPERATURA
  DS18B20.requestTemperatures();      // send the command to get temperatures
  tempC = DS18B20.getTempCByIndex(0); // read temperature in °C
  tempF = tempC * 9 / 5 + 32;         // convert °C to °F

  Serial.print("Temperature: ");
  Serial.print(tempC); // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  "); // separator between °C and °F
  Serial.print(tempF);   // print the temperature in °F
  Serial.println("°F");

  // Set timer to 5 seconds
  // turn off de peripherals
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF); // Estas 3 instrucciones no han mostrado diferencia en consumo hasta ahora
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_enable_timer_wakeup(4000000);
  esp_deep_sleep_start();
}