#include <Wicked_DCMotor.h> 
// N.B: Initializes motors to clockwise BRAKED condition
#include <math.h>

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
float theta;
int direction;
float magnitude;
float duration;
byte brake;

//void printCurrentSensing(void);

//int num_motors = 3;
Wicked_DCMotor mL(M1);
Wicked_DCMotor mF(M2);
Wicked_DCMotor mR(M3);

//Wicked_DCMotor *m[] = {&mL, &mF, &mR};


void setup(void){
  Serial.begin(9600);
}

void loop(void){
  // Section for taking commands from Serial Input
  // N.B.  Need to comment out one bracket at end for the autonomous loop below
    /* if (Serial.available() > 0) { */
    /*   direction = Serial.parseInt(); */
    /*   theta = ( M_PI * direction ) / 180. ; */
    /*   magnitude = Serial.parseInt(); */
    /*   duration = Serial.parseInt(); */
    /* }  */

  // Autonomous loop for driving in a square
  for ( byte leg = 1; leg < 6; leg++ ) {
    duration = 2;
    magnitude = 75;
    brake = 0; // No braking
    switch (leg) {
    case 2: // Move right
      direction = 90.;
      break;
    case 3: // Move backward
      direction = 180.;
      break;
    case 4: // Move left
      direction = -90.;
      break;
    case 1: // Move forward
      direction = 0.;
      break;
    default: // Stop and pause at starting point
      magnitude = 0;
      duration = 4;
      direction = 0;
      brake = 1; // hard stop
    }
    theta = ( M_PI * direction ) / 180. ; 

  if( duration > 0 ) {
    Serial.print("direction = ");
    Serial.print(direction);
    Serial.print(", theta = ");
    Serial.print(theta);
    Serial.print(", magnitude = ");
    Serial.print(magnitude);
    Serial.print(" and duration = ");
    Serial.println(duration);
      
    float vx = magnitude * sin(theta);
    float vy = magnitude * cos(theta);
    Serial.print("vx, vy = ");
    Serial.print(vx);
    Serial.print(", ");
    Serial.println(vy);
      
    const float sqrt3o2 = 1.0*sqrt(3)/2;
    //STEP 3. Find wheel vectors
    float wF = -vx * .95 ;  // Multiply by fudge factor to prevent rotation if needed
    float wL = 0.5*vx - sqrt3o2 * vy; 
    float wR = 0.5*vx + sqrt3o2 * vy; 
   
    byte wF_speed = (byte) map(abs(wF), 0, 100, 0, 255);
    byte wL_speed = (byte) map(abs(wL), 0, 100, 0, 255);
    byte wR_speed = (byte) map(abs(wR), 0, 100, 0, 255);
    /* Set Motor directions: 
         1 is Clockwise (Positive motor direction)
         0 is Counterclockwise (Negative vector direction)
	 so we can use a logic test since TRUE = 1 and FALSE = 0
    */
    mF.setDirection(wF > 0) ;
    mL.setDirection(wL > 0);
    mR.setDirection(wR > 0);

    // Set the brakes
    mF.setBrake(brake);
    mL.setBrake(brake);
    mR.setBrake(brake);

    // Set the speeds
    mF.setSpeed(wF_speed);
    mL.setSpeed(wL_speed);
    mR.setSpeed(wR_speed);
    
    //Print out motor control details
    Serial.print("Speeds F,L,R = ");
    Serial.print(copysign(wF_speed,wF));
    Serial.print(", ");
    Serial.print(copysign(wL,wL_speed));
    Serial.print(", ");
    Serial.println(copysign(wR,wR_speed));

    // Run motors for the duration requested
    delay(1000*duration);
    
  }
  else{ // no duration entered, so stop all motors
    mF.setSpeed(0);
    mL.setSpeed(0);
    mR.setSpeed(0);
  }
  }  

}


/*
 SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
/* void serialEvent() { */
/*   while (Serial.available()) { */
/*     // get the new byte: */
/*     char inChar = (char)Serial.read();  */
/*     // add it to the inputString: */
/*     inputString += inChar; */
/*     // if the incoming character is a newline, set a flag */
/*     // so the main loop can do something about it: */
/*     if (inChar == '\n') { */
/*       stringComplete = true; */
/*     }  */
/*   } */
/* } */
