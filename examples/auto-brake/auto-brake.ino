// -*- mode:c++; mode: flymake -*-
/**
 * This Small examples uses a 
 * HC RS04 ultrasonic sensor on pin 7,8 to 
 * show an auto brake function.
 * Mount the arduino with the sensor on the car.
 * Define the Security distance (based on your project)
 * 
 * The system will issue a power function brake on  first channel 
 * if the sensor detect a object in a range <= AutoBrakeDistanceCm
 */
// CONFIG
const int triggerPort = 7;
const int echoPort = 8;
const int PowerFunctionPort=12;
const int AutoBrakeDistanceCm=10;

const int blueLed=11;
//const int blueLed2=11;
const int redLed=2;     // SIGNAL A slowness in the main loop (=Arduino take too time to response, i.e. brake could be ineffective)

// Depends from sensor. See its datasheet.
const int maxDistCm=28; 
const int minDistCm=10;



#include <PowerFunctions.h>  
  
  
#define log(x)  Serial.println(F(x))


PowerFunctions powerFunction(12, 0);

void setup() {
   
  pinMode( triggerPort, OUTPUT );
  pinMode( echoPort, INPUT );
  pinMode( blueLed, OUTPUT);
  pinMode(redLed,OUTPUT);
  Serial.begin( 9600 );
  Serial.println( F( "AutoBrake "));

}
 
void loop() {

  // Ultrasonic Scan
  static long lastDistance=0;
  analogWrite(blueLed, 255);

  // Wait two seconds to let human seattle down?
  delay(2000);

  
  while(true) {
    unsigned long startTime=millis();
    //porta bassa l'uscita del trigger
    digitalWrite( triggerPort, LOW );
   
    //invia un impulso di 10microsec su trigger
    digitalWrite( triggerPort, HIGH );
    delayMicroseconds( 10 ); 
    
    
    digitalWrite( triggerPort, LOW );

    // Reads a pulse (either HIGH or LOW) on a pin.
    // Returns the length of the pulse (in microseconds) or 0 if no pulse is completed before the timeout
    // Note: there are 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second.
    const  unsigned long MicrosecondsPulseTimeout=38000;  // 38ms
    unsigned long duration = pulseIn( echoPort, HIGH,MicrosecondsPulseTimeout );
    if(duration == 0 ){
      log("PULSE TIMEOUT");
      continue;
    }
    float r = 0.034 * duration / 2;
    if(r != lastDistance){
    
      log("dur: ");
      Serial.print( duration );
      log("> ") ;
     
      //After 38ms it is out of sensor range:
      if( duration > 38000 ) {
        log("out of range");
      } else {       
        Serial.print( r ); log("cm") ;
        long rlong=(long)r*10;      
        log(" >Res");
        Serial.print(rlong);
        
        //int ledValue=map(rlong,minDistCm*10,maxDistCm*10,0,255);
        //Serial.print(F(" "));
        //Serial.print( ledVaue );
        if(r>=minDistCm && r<= AutoBrakeDistanceCm ){
          log("!");
          // Brake! (short way)
          powerFunction.combo_pwm(PWM_BRK,PWM_BRK);
          //analogWrite(blueLed, ledValue);
        }else{
          // TODO: Push the old one (lastDistance)
          // Serial.print(F(".."));
        }
        /// PUT HERE Other low priorty housekeeping
      }
      lastDistance=r;
    }
  
    /* POST DELAY
       From sensor data sheet:
       -----
       we suggest to use over 60ms
       measurement cycle, in order to prevent trigger signal 
       to the echo signal

       60*5 --> too slow
       60*2 --> good until 28 cm
       ----
       NB: Interrupt could lead to fake measure, so we delay 60ms
       
    */
    
    unsigned long endTime=millis()-startTime;
    if(endTime < 60*2 ){
      // DELTA DELAY: add a 1 millis for overhead
      delay( endTime+1 );
      digitalWrite(redLed,LOW);
    }else {
      // SIGNAL a bad condition and pause a bit
      digitalWrite(redLed,HIGH);
      delay(1000);
    }
    
  } // main while loop
}



