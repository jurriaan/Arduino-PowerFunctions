# Lego Power Functions Infrared Control for Arduino

This is a Arduino Lego Power Functions Library.
For now it only supports single/combo PWM.
Based on [SuperCow's code](http://forum.arduino.cc/index.php?topic=38142.msg282833#msg282833)

## Protocol

See [LEGO_Power_Functions_RC_v120.pdf](https://github.com/jurriaan/Arduino-PowerFunctions/raw/master/LEGO_Power_Functions_RC_v120.pdf) for more info

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


(c) 2013 Jurriaan Pruis
(c) 2017 Giovanni Giorgi
