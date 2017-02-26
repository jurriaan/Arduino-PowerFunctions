BOARD_TAG    = uno
ARDUINO_LIBS = Arduino-PowerFunctions
# ARDUINO_DIR = C:/Arduino

### CXXFLAGS_STD
### Set the C++ standard to be used during compilation. Documentation (https://github.com/WeAreLeka/Arduino-Makefile/blob/std-flags/arduino-mk-vars.md#cxxflags_std)
CXXFLAGS_STD      = -std=gnu++11

### CXXFLAGS
### Flags you might want to set for debugging purpose. Comment to stop.
## GG C++ Extension with -std=c++11
CXXFLAGS         += -pedantic -Wall -Wextra

include ../../arduino-makefile/Arduino.mk

# For emacs fly-make
check-syntax:
	$(CXX) -c -include Arduino.h   -x c++ $(CXXFLAGS)   $(CPPFLAGS)  -fsyntax-only $(CHK_SOURCES)

doxygen:
	doxygen Doxyfile
tags:
	etags *.ino ../libraries/*/*.{c,h,cpp}
