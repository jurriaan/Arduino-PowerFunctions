// -*- mode:c++; mode: flymake -*-
#include <PowerFunctions.h>



/*** 
 * This demo uses an arduino to drive a 
 * LEGO RC Tracked Racer 42065
 * To drive it you must give inverted command in sync.
 * 
 */

PowerFunctions pf(12, 0,true /* <= Enable debug mode? */); 


int j=0;
void setup() {
  // put your setup code here, to run once:  
}




void goForward(uint16_t time){
  pf.combo_pwm(PWM_FWD2, PWM_REV2);
  delay(time/2);
  pf.combo_pwm(PWM_FWD4, PWM_REV4);
  delay(time/2);
  pf.combo_pwm(PWM_BRK,PWM_BRK);
  pf.combo_pwm(PWM_FLT,PWM_FLT);
}

void turn90Degrees(){
  // Now try to do a 90 angle with a moderate speed. To do it is enough to run a motor
  pf.combo_pwm(PWM_BRK,PWM_BRK);  
  pf.combo_pwm(PWM_REV5,PWM_BRK);
  delay(500);
  pf.combo_pwm(PWM_BRK,PWM_BRK);    
}





void step(uint8_t output, uint8_t pwm,  uint16_t time) {
  pf.single_pwm(output, pwm);
  delay(time);
  pf.single_pwm(output, PWM_BRK);
  delay(30);
  pf.single_pwm(output, PWM_FLT);
}


/////////////
void zigZag(uint16_t msTime){
  unsigned long startTime=millis();
  do {
    // Zig to left
    pf.combo_pwm(PWM_FWD4, PWM_REV2);

    delay(400);    
    goForward(1500);
    
    // Zig to right
    pf.combo_pwm(PWM_FWD2, PWM_REV4);
    
    delay(400);    
    goForward(1500);
    
  }while ((millis()-startTime) < msTime);
}

void loop() {
  /* Make a Square: 
   */

  turn90Degrees();
  goForward(1200);
  turn90Degrees();
  goForward(1200);
  turn90Degrees();
  turn90Degrees();
  goForward(1200);
  turn90Degrees();
  goForward(1200);

  zigZag(10000);
  
}
