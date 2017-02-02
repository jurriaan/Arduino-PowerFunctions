// -*- mode:c++; mode: flymake -*-
#include <PowerFunctions.h>



/*** 
 * This demo uses an arduino to drive a 
 * LEGO RC Tracked Racer 42065
 * To drive it you must give inverted command in sync.
 * We go forward a bit then backward
 */

PowerFunctions pf(12, 0);


int j=0;
void setup() {
  // put your setup code here, to run once:
  // a functional object that will increment any type
  //auto incr = [](auto x) { return x++; };  
  //auto i =0;
  // incr(i);
}


void goForward(uint16_t time){
  pf.combo_pwm(PWM_FWD2, PWM_REV2);
  delay(time);
  pf.combo_pwm(PWM_BRK,PWM_BRK);
  pf.combo_pwm(PWM_FLT,PWM_FLT);
}


void goBackward(uint16_t time){
  pf.combo_pwm(PWM_REV2, PWM_FWD2);
  delay(time);
  pf.combo_pwm(PWM_BRK,PWM_BRK);
  pf.combo_pwm(PWM_FLT,PWM_FLT);
}

void loop() {
  // put your main code here, to run repeatedly:
  goForward(1500);
  goBackward(500);
  while(true) { delay(1000); }

  // Now try to do a 90 angle with a moderate speed
  pf.combo_pwm(PWM_BRK,PWM_BRK);  
  pf.combo_pwm(PWM_REV5,PWM_BRK);
  deplay(500);
  pf.combo_pwm(PWM_BRK,PWM_BRK);    
  
}





void step(uint8_t output, uint8_t pwm,  uint16_t time) {
  pf.single_pwm(output, pwm);
  delay(time);
  pf.single_pwm(output, PWM_BRK);
  delay(30);
  pf.single_pwm(output, PWM_FLT);
}
