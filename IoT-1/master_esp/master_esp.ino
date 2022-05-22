#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define BUTTON_PIN 34

int currentState;

const uint8_t DEST_ADDR2 = 4;
const int SDA1 = 21;
const int SCL1 = 22;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
TwoWire I2C_1 = TwoWire(0);

void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  I2C_1.begin(SDA1, SCL1);

  lcd.init();                      // initialize the lcd
  lcd.backlight();
}

void loop()
{
  currentState = digitalRead(BUTTON_PIN);
  Serial.print(currentState);

  int i = 0;
  if (currentState == LOW) {
    I2C_1.requestFrom((uint8_t)DEST_ADDR2, (uint8_t)2);
    Serial.print("request sent");
    while (I2C_1.available()) {
      byte c = I2C_1.read();
      if ((int)c != 255) {
        lcd.setCursor(3, i % 2);
        i++;
        lcd.print((int)c);
      }
    }
  }
}
