# Internet of Things (IoT)

## IoT-1
---
A simple distributed temperature sensor should be implemented. The following requirements define its functionality:
1. The system shall be consisting of:
    - 2ea ESP32 microcontrollers (ESP)
    - 1ea DHT11 Temperature Sensor (DHT)
    - 1ea push-button (PB)
    - 1ea LCD1602 Liquid Crystal Display with integrated I2C controller (LCD)
    - 1ea TM1637 7-segment display (TM)
    - Plus whatever you think is useful…
2. The communication shall be provided by:
    - I2C bus 1 between ESP#1 and ESP#2
    - I2C bus 1 between ESP#2 and LCD
    - I2C bus 2 between ESP#1 and TM
    - Digital input at ESP#2 for PB
    - 1-Wire bus between ESP#1 and DHT
3. ESP#1 shall display the temperature on the TM as an integer value. It shall update
the temperature measurement once per second.
4. ESP#1 may display the humidity on the TM as well. In that case the humidity
shall be updated once per second.
5. ESP#2 shall watch the button state. If the button is pressed, it shall request the
temperature from ESP#1. After reception it shall display the temperature on the
LCD.
6. ESP#2 may do the same as described in Requirement 5 for the humidity instead
of the temperature.