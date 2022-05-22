#include <Wire.h>
#include "DHT.h"
#include "TM1637.h"

const uint8_t MY_ADDR1 = 4;
const uint8_t dhtType = DHT11;
const uint8_t dhtPin = 13;

const uint8_t SDA1 = 21;
const uint8_t SCL1 = 22;

const uint8_t SDA2 = 32;
const uint8_t SCL2 = 33;

TwoWire I2C_1 = TwoWire(0);
byte dataToSend1 = 0;
byte dataToSend2 = 0;

DHT dht(dhtPin, dhtType);

TM1637 tm1637(SCL2,SDA2);

float h = 0;
float t = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  I2C_1.begin(MY_ADDR1,SDA1,SCL1);
  I2C_1.onRequest(requestEvent);
  
  dht.begin();
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  int numdisplay = 0;

  h = dht.readHumidity();
  t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) {
    Serial.println("error!!");
    return;
  }
  Serial.printf("Humidity: %d%%\n",(int)h);
  Serial.printf("Temperature: %d°C\n",(int)t);

  numdisplay = (int)h*100 + (int)t;

  tm1637.display(0,numdisplay / 1000 % 10);
  tm1637.display(1,numdisplay / 100 % 10);
  tm1637.display(2,numdisplay / 10 % 10);
  tm1637.display(3,numdisplay % 10);

  delay(500);
}

void requestEvent()
{ 
  Serial.printf("requestEvent\n");
  
  dataToSend1 = int(h);
  dataToSend2 = int(t);
  
  I2C_1.write(dataToSend1);
  I2C_1.write(dataToSend2);

}
