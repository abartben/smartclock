# Smartclock
An arduino-based clock connected to Internet<br/>
Short video presenting my project : <a href="https://www.youtube.com/watch?v=bhy818PjfPU">https://www.youtube.com/watch?v=bhy818PjfPU</a>
<br/>Description of the project on my <a href="http://abartben.wordpress.com/">blog</a>
# Wiring

The following wiring was used on an Arduino Mini Pro 5v 16Mhz

ESP8266 (wifi module) : RX -> 2, TX-> 4<br/>
RGB LED : Red -> 5, Green -> 6, blue -> 9 (caution intensity is inverted)<br/>
Buzzer : Pin 3<br/>
APDS9960 : On I2C port (A4 and A5)<br/>
MATRIX LED (4 MAX7221) : DataIn->12 Clock->13 Load/CS->10<br/>

# Internet sync

The script will connect to a VPS server (IP must be changed on ESP.ino line 62)
The request is like a telnet request and the result should be this :
<pre>17#26#22#13#02#2016##15#7#42#</pre>
Hour#Minutes#Seconds#day#month#year##day of alarm#hour for alarm#minutes for alarm#42 (because 42 !) <br/>
I will try to share the server side code in my future ...
