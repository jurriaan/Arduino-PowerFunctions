//
// Lego Power Functions Infrared Control for Arduino
// see http://www.philohome.com/pf/LEGO_Power_Functions_RC_v120.pdf for more info
// Based on SuperCow's code (http://forum.arduino.cc/index.php?topic=38142.0)
//

#define toggle() _toggle ^= 0x8
#define CHECKSUM() (0xf ^ _nib1 ^ _nib2 ^ _nib3)

#include <stdlib.h>
#include "PowerFunctions.h"
#include "Arduino.h"

// Aliases
void PowerFunctions::red_pwm(uint8_t pwm) { single_pwm(RED, pwm); }
void PowerFunctions::blue_pwm(uint8_t pwm) { single_pwm(BLUE, pwm); }

// Constructor
PowerFunctions::PowerFunctions(uint8_t pin, uint8_t channel)
{
  _channel = channel;
  _toggle = 0;
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

// Single output mode PWM
void PowerFunctions::single_pwm(uint8_t output, uint8_t pwm) {
  _nib1 = _toggle | _channel;
  _nib2 = SINGLE_OUTPUT | output;
  _nib3 = pwm;
  send();
  toggle();
}

void PowerFunctions::single_increment(uint8_t output){
  _nib1 = _toggle | _channel;
  _nib2 = SINGLE_EXT | output;
  _nib3 = 0x4;
  send();
  toggle();
}

void PowerFunctions::single_decrement(uint8_t output){
  _nib1 = _toggle | _channel;
  _nib2 = SINGLE_EXT | output;
  _nib3 = 0x5;
  send();
  toggle();
}

// Combo PWM mode
void PowerFunctions::combo_pwm(uint8_t blue_speed, uint8_t red_speed)
{
  _nib1 = ESCAPE | _channel;
  _nib2 = blue_speed;
  _nib3 = red_speed;
  send();
}

void PowerFunctions::send_beacon()
{
  _nib1 = ESCAPE | _channel;
  _nib2 = 0x0;
  _nib3 = 0x0;
  send();
}

//
// Private methods
//

// Pause function see "Transmitting Messages" in Power Functions PDF
void PowerFunctions::pause(uint8_t count)
{
  uint8_t pause = 0;

  if(count == 0) {
    pause = 4 - (_channel + 1);
  } else if(count < 3) { // 1, 2
    pause = 5;
  } else {  // 3, 4, 5
    pause = 5 + (_channel + 1) * 2;
  }
  delayMicroseconds(pause * 77); //MAX_MESSAGE_LENGTH
}

// Send the start/stop bit
void PowerFunctions::start_stop_bit()
{
  send_bit();
  delayMicroseconds(START_STOP); // Extra pause for start_stop_bit
}

// Send a bit
void PowerFunctions::send_bit() {
  for(uint8_t i = 0; i < 6; i++) {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(HALF_PERIOD);
    digitalWrite(_pin, LOW);
    delayMicroseconds(HALF_PERIOD);
  }
}

void PowerFunctions::send()
{
  uint8_t i, j;
  uint16_t message = _nib1 << 12 | _nib2 << 8 | _nib3 << 4 | CHECKSUM();
  for(i = 0; i < 6; i++)
  {
    pause(i);
    start_stop_bit();
    for(j = 0; j < 16; j++) {
      send_bit();
      delayMicroseconds((0x8000 & (message << j)) != 0 ? HIGH_PAUSE : LOW_PAUSE);
    }
    start_stop_bit();
  }
}
