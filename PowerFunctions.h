#ifndef PowerFunctions_h
#define PowerFunctions_h

#include <stdio.h>
#include "Arduino.h"

#define COMBO_DIRECT_MODE 0x01
#define SINGLE_PIN_CONTINUOUS 0x2
#define SINGLE_PIN_TIMEOUT 0x3
#define SINGLE_OUTPUT 0x4

#define START_STOP 1014
#define HIGH_PAUSE 546
#define LOW_PAUSE 260

//PWM speed steps
#define PWM_FLT 0x0
#define PWM_FWD1 0x1
#define PWM_FWD2 0x2
#define PWM_FWD3 0x3
#define PWM_FWD4 0x4
#define PWM_FWD5 0x5
#define PWM_FWD6 0x6
#define PWM_FWD7 0x7
#define PWM_BRK 0x8
#define PWM_REV7 0x9
#define PWM_REV6 0xA
#define PWM_REV5 0xB
#define PWM_REV4 0xC
#define PWM_REV3 0xD
#define PWM_REV2 0xE
#define PWM_REV1 0xf

//speed
/*
#define RED_FLT 0x0
#define RED_FWD 0x1
#define RED_REV 0x2
#define RED_BRK 0x3
#define BLUE_FLT 0x0
#define BLUE_FWD 0x4
#define BLUE_REV 0x8
#define BLUE_BRK 0xC
*/

//output
#define RED 0x0
#define BLUE 0x1

class PowerFunctions
{
	public:
  	PowerFunctions(uint8_t, uint8_t);
    void single_output(uint8_t, uint8_t);

  protected:
    void pause(uint8_t);
    void send_bit();
    void send(uint16_t);
    void start_stop_bit();
    uint8_t _channel;
    uint8_t _pin;
    bool _toggle;
};

#endif
// END OF FILE