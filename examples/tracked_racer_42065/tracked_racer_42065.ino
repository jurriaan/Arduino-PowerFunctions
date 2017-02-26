// -*- mode:c++; mode: flymake -*-
#include <PowerFunctions.h>



/*** 
 *  Zig Zag a RC Tracked Racer!
 *  Version 1.1
 *  
 * This demo uses an arduino to drive a 
 * LEGO RC Tracked Racer 42065
 * To drive it you must give inverted command in sync.
 * 
 * Wiring: wire 4 buttons with different resistence to pin A0, using the keyboard example 7 in ardruino starter kit
 * Connect the led to pin 12.
 * 
 * Alternate Wiring: Use a mosfet to drive more power to the led (use pin 12 to control the mosfet.
 * 
 * 
 */

PowerFunctions pf(12, 0,true /* <= Enable debug mode on pin 13? */); 



int j=0;
void setup() {
  // put your setup code here, to run once:  
   Serial.begin(9600);
}



void goForward(uint16_t time){
  
  pf.combo_pwm(PWM_FWD4, PWM_REV4);
  delay(time);
  pf.combo_pwm(PWM_FLT,PWM_FLT);
}

/** NEEDS STILL TESTING
void turn90Degrees(){
  // Now try to do a 90 angle with a moderate speed. To do it is enough to run a motor
  pf.combo_pwm(PWM_BRK,PWM_BRK);  
  pf.combo_pwm(PWM_REV5,PWM_BRK);
  delay(500);
  pf.combo_pwm(PWM_BRK,PWM_BRK);    
}
*/




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
  const int delayf=2;
  const int zigRange=2;
  do {

    // TO TEST THE TURNING MECHANINCS
    
    
    // Zig to left
    pf.combo_pwm(PWM_FWD4, PWM_REV2);
    delay(100*delayf*zigRange);
    
    goForward(50*delayf);

    // Center again
    pf.combo_pwm(PWM_FWD2, PWM_REV4);
    delay(100*delayf*zigRange);
    
    // Zig to right
    pf.combo_pwm(PWM_FWD2, PWM_REV4);
    delay(100*delayf*zigRange);   

    goForward(50* delayf);
    
    
    
  }while ((millis()-startTime) < msTime);
}

boolean stop=true;
void loop() {
  /* Make a Square: 
   */
  // Analog read button and then do the trick...
  int keyVal = analogRead(A0);

  // play the note corresponding to each value on A0
  if (keyVal >=1016) {
    // Super start:
    stop=false;
  } else if (keyVal >= 990 && keyVal <= 1010) {
    // Super stop
    stop=true;
    Serial.println(F("STOP"));
  } else if (keyVal >= 505 && keyVal <= 515) {
  } else if (keyVal >= 5 && keyVal <= 10) {
  } else {
  }  

  if(!stop) {
     Serial.println(F("ZIGZAG"));
     zigZag(10000); // 10 sec zig zag
     stop=true;
  }
  Serial.println(keyVal);

 
  
}
