# Smartclock
An arduino-based clock connected to Internet

# Wiring

The following wiring was used on an Arduino Mini Pro 5v 16Mhz

ESP8266 (wifi module) : RX -> 2, TX-> 4
RGB LED : Red -> 5, Green -> 6, blue -> 9 (caution intensity is inverted)
Buzzer : Pin 3
APDS9960 : On I2C port (A4 and A5)
MATRIX LED (4 MAX7221) : DataIn->12 Clock->13 Load/CS->10
