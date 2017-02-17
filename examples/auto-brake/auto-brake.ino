// -*- mode:c++; mode: flymake -*-
/**
   This Small examples uses a  HC RS04 ultrasonic sensor on pin 7,8 to
   show an auto brake function.
   Mount the arduino with the sensor on the car.
   Define the Security distance (based on your project)

   
   If the sensor detect a object in a range <= AutoBrakeDistanceCm
   Arduino system will issue a power function brake on first channel, possibly overriding
   your orders.

   The NewPing v 1.8 is used for better measurements: for more information see https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
  
TODO: TRY TO COMPUTE RELATIVE SPEED VIA FORMULA LIKE
Speed = (FirstDistance - SecondDistance) / (SecondTime - FirstTime)


   Note: there are 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second.
*/
// CONFIG
const int triggerPort = 7;
const int echoPort = 8;
const int PowerFunctionPort = 12;
const int AutoBrakeDistanceCm = 10;

//  HCRS04 Specs talk about 400cm. NewPing default is 500
const int MaxDistCm = 400;


#include <PowerFunctions.h>
#include "NewPing.h"

// Decomment your preferred debug
#define log(x)  Serial.print(F(x))
//#define log(x)


PowerFunctions powerFunction(12, 0, /*debug=*/ true);
NewPing sonar(triggerPort, echoPort, MaxDistCm);

void setup() {

  pinMode( triggerPort, OUTPUT );
  pinMode( echoPort, INPUT );
  //pinMode( blueLed, OUTPUT);
  //pinMode(redLed, OUTPUT);
  Serial.begin( 9600 );
  Serial.println( F( "AutoBrake v1.2+"));
  // 
  // Make a two break cmd (test set)
  //
  powerFunction.combo_pwm(PWM_BRK, PWM_BRK);
  powerFunction.combo_pwm(PWM_BRK, PWM_BRK);

}

void loop() {

  // Static registered last distance
  static unsigned long lastDistance = 0;
  //analogWrite(blueLed, 255);


  unsigned long startTime = millis();

  // We do 3 short measures to gain better accuracy
  //unsigned long r = sonar.ping_cm();
  unsigned long r = sonar.convert_cm(sonar.ping_median(3));


  
  if (r == 0 ) {
    // Could also mean there are no obstacles and live happily...
    //log("OUT OF RANGE");
  } else  {
    if (r != lastDistance) {
      log("> ") ;
      Serial.println( r );
      log("cm") ;
      //int ledValue=map(rlong,minDistCm*10,maxDistCm*10,0,255);

      //TODO: Implement a sort of progressive brake to avoid too much trouble
      // The system should be able to extimate current velocity
      if (  r <= AutoBrakeDistanceCm ) {
        log("!BRAKE|\n");
        // Brake! (short way)
        powerFunction.combo_pwm(PWM_BRK, PWM_BRK);
        //analogWrite(blueLed, ledValue);
      } else {
        // TODO: Push the old one (lastDistance)
        // Serial.print(F(".."));
      }
      /// PUT HERE Other low priorty housekeeping
        
      lastDistance = r;
      log("\n");
    }
     
  }
  
}



