# Lego Power Functions Infrared Control for Arduino

This is a Arduino Lego Power Functions Library.
For now it only supports single/combo PWM.
Based on [SuperCow's code](http://forum.arduino.cc/index.php?topic=38142.msg282833#msg282833)

## Protocol

See [LEGO_Power_Functions_RC_v120.pdf](https://github.com/jurriaan/Arduino-PowerFunctions/raw/master/LEGO_Power_Functions_RC_v120.pdf) for more info
The first version of the specification was published on 2008 [1].
The version described in the pdf is the 1.2

## Usage

See [example](https://github.com/jurriaan/Arduino-PowerFunctions/blob/master/examples/power_functions/power_functions.ino).

## Standalone Compile (optional)
The [Arduino Makefile project](https://github.com/sudar/Arduino-Makefile) is used for standalone compile of examples.
Refer to arduino-makefile/Arduino.mk for instructions on how to
configure it.
Under windows, try to define a user variable like
 `setx ARDUINO_DIR  C:/Arduino`

Then to get a list of supported command issue

`make help`

Also, you can spped up large project construction with the GNU Make
"-j option" to make a parallel build.

## Other projects
This project [is able to decode IR protocol](https://raw.githubusercontent.com/matthiaszimmermann/ArduinoLegoIrReceiver) and can be paired with this one

The [New Ping library give you some insight about how the ping code was optimized](https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home)




## References

[1] http://www.technicbricks.com/2008/01/power-functions-rc-protocol-released-as.html<br>
[2] [General introduction into decoding IR signals with Arduino]https://learn.adafruit.com/ir-sensor/using-an-ir-sensor<br>

(c) 2013 Jurriaan Pruis
(c) 2017 Giovanni Giorgi
