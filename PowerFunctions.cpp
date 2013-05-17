//
// Lego Power Functions Infrared Control for Arduino
// see http://www.philohome.com/pf/LEGO_Power_Functions_RC_v120.pdf for more info
// Based on SuperCow's code (http://forum.arduino.cc/index.php?topic=38142.0)
//

#include <stdlib.h>
#include "PowerFunctions.h"
#include "Arduino.h"

PowerFunctions::PowerFunctions(uint8_t pin, uint8_t channel)
{
  _channel = channel;
  _toggle = 0x8;
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

void PowerFunctions::single_output(uint8_t output, uint8_t pwm) {
  uint8_t nib1, nib2, nib3, nib4, i;

  _toggle ^= 0x8;
  nib1 = _toggle | _channel;
  nib2 = SINGLE_OUTPUT | output;
  nib3 = pwm;
  nib4 = 0xf ^ nib1 ^ nib2 ^ nib3;

  for(i = 0; i < 6; i++)
  {
    pause(i);
    send(nib1 << 12 | nib2 << 8 | nib3 << 4 | nib4);
  }
}

void PowerFunctions::pause(uint8_t count)
{
  uint8_t pause = 0;

  if(count == 0) {
    pause = 4 - _channel + 1;
  } else if(count < 3) { // 1, 2
    pause = 5;
  } else {  // 3, 4, 5
    pause = 5 + (_channel + 1) * 2;
  }
  delayMicroseconds(pause * 77);
}

void PowerFunctions::start_stop_bit()
{
  send_bit();
  delayMicroseconds(START_STOP); // Extra pause for start_stop_bit
}

void PowerFunctions::send_bit() {
  for(uint8_t i = 0; i < 6; i++) {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(13);
    digitalWrite(_pin, LOW);
    delayMicroseconds(13);
  }
}

void PowerFunctions::send(uint16_t message)
{
  start_stop_bit();
  for(uint8_t i = 0;i < 16;i++) {
    send_bit();
    delayMicroseconds((0x8000 & (message << i)) != 0 ? HIGH_PAUSE : LOW_PAUSE);
  }
  start_stop_bit();
  delay(5);
}
