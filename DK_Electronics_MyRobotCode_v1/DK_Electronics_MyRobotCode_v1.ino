//http://sribasu.com/programming-tutorials/creating-an-obstacle-avoiding-robot-with-arduino-adafruit-motor-shield-v1-and-ultra-sonic-sensor.html

#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>
  
#define TRIG_PIN A4 // Pin A4 on the Motor Drive Shield connected to the ultrasonic sensor
#define ECHO_PIN A5 // Pin A5 on the Motor Drive Shield connected to the ultrasonic sensor
#define MAX_DISTANCE_POSSIBLE 1000 // sets maximum useable sensor measuring distance to 1000cm
#define MAX_SPEED 265 // sets speed of DC traction motors to 120/256 or about 47% of full speed - to reduce power draining.
#define MOTORS_CALIBRATION_OFFSET 5 // this sets offset to allow for differences between the two DC motors
#define COLL_DIST 20 // sets distance at which the Obstacle avoiding Robot stops and reverses to 10cm
#define TURN_DIST COLL_DIST+10 // sets distance at which the Obstacle avoiding Robot looks away from object (not reverse) to 20cm (10+10)
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_POSSIBLE); // sets up sensor library to use the correct pins to measure distance.
  
AF_DCMotor leftMotor(1, MOTOR12_1KHZ); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor rightMotor(4, MOTOR34_1KHZ); // create motor #2, using M2 output, set to 1kHz PWM frequency
Servo neckControllerServoMotor;  // create servo object to control a servo
  
int pos = 0; // this sets up variables for use in the sketch (code)
int maxDist = 0;
int maxAngle = 0;
int maxRight = 0;
int maxLeft = 0;
int maxFront = 0;
int course = 0;
int curDist = 0;
String motorSet = "";
int speedSet = 0;
  
//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  neckControllerServoMotor.attach(9);  // attaches the servo on pin 9 (SERVO_2 on the Motor Drive Shield to the servo object
  neckControllerServoMotor.write(90); // tells the servo to position at 90-degrees ie. facing forward.
  delay(2000);
  /*
  delay(2000); // delay for two seconds
  checkRoute(); // run the CheckRoute routine to find the best Route to begin travel
  motorSet = "FORWARD"; // set the director indicator variable to FORWARD
  neckControllerServoMotor.write(90); // ensure servo is still facing forward
  moveForward(); // run function to make Obstacle avoiding Robot move forward
  */

  Serial.begin(9600);
}
//------------------------------------------------------------------------------------------------------------------------------------
  
//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
  
  //checkForward(); // check that if the Obstacle avoiding Robot is supposed to be moving forward, that the drive motors are set to move forward - this is needed to overcome some issues with only using 4 AA NiMH batteries
  //checkRoute(); // set ultrasonic sensor to scan for any possible obstacles 
  

  scanHead();  
  curDist = readPing();
  Serial.println("Ping is:"); 
  Serial.println(curDist); 

  speedSet = 230;

  //If distance become small - Stop 
  if(curDist > 5 and curDist < 30)
  {
    
    moveStop();   
    delay(1000);
    
    moveBackward();
    delay(1000);    
        
    turnRight();
    delay(400);    

    curDist = readPing();

    //If the distance is still small then turn Left
    if(curDist > 5 and curDist < 30)
    {
      turnLeft();
      delay(600);    
    }
        
  }
  else
  {
    //Begin to slow things down
    if(curDist > 5 and curDist < 70)
    {
      speedSet = 160;
    }
    MyMoveForward();  
  }

   
}

void scanHead() {

  for (pos = 144; pos >= 60; pos -= 18) // loop to sweep the servo (& sensor) from 144-degrees left to 36-degrees right at 18-degree intervals.
  {    
    neckControllerServoMotor.write(pos);  // tell servo to go to position in variable 'pos'
    delay(80);
  }

}

//-------------------------------------------------------------------------------------------------------------------------------------

  
int readPing() { // read the ultrasonic sensor distance
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS / US_ROUNDTRIP_CM;

  Serial.println(cm); 
  
  return cm;
}
//-------------------------------------------------------------------------------------------------------------------------------------
void checkForward() {
  if (motorSet == "FORWARD") {
    leftMotor.run(FORWARD);  // ensure motors are going forward
    rightMotor.run(FORWARD);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void checkBackward() {
  if (motorSet == "BACKWARD") {
    leftMotor.run(BACKWARD);  // ensure motors are going backward
    rightMotor.run(BACKWARD);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------
  
// In some cases, the Motor Drive Shield may just stop if the supply voltage is too low (due to using only four NiMH AA cells).
// The above functions simply remind the Shield that if it's supposed to go forward, then ensure it is going forward and vice versa.
  
//-------------------------------------------------------------------------------------------------------------------------------------
void moveStop() {
  leftMotor.run(RELEASE);  // stop the motors.
  rightMotor.run(RELEASE);
}

//-------------------------------------------------------------------------------------------------------------------------------------
void MyMoveForward() {
  motorSet = "FORWARD";
  leftMotor.run(FORWARD);      // turn it on going forward
  rightMotor.run(FORWARD);      // turn it on going forward

  leftMotor.setSpeed(speedSet + MOTORS_CALIBRATION_OFFSET);
  rightMotor.setSpeed(speedSet);

}

//-------------------------------------------------------------------------------------------------------------------------------------
void moveForward() {
  motorSet = "FORWARD";
  leftMotor.run(FORWARD);      // turn it on going forward
  rightMotor.run(FORWARD);      // turn it on going forward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    leftMotor.setSpeed(speedSet + MOTORS_CALIBRATION_OFFSET);
    rightMotor.setSpeed(speedSet);
    delay(5);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveBackward() {
  motorSet = "BACKWARD";
  leftMotor.run(BACKWARD);      // turn it on going forward
  rightMotor.run(BACKWARD);     // turn it on going forward
  
  leftMotor.setSpeed(speedSet + MOTORS_CALIBRATION_OFFSET);
  rightMotor.setSpeed(speedSet);  
}
//-------------------------------------------------------------------------------------------------------------------------------------
void turnRight() {
  
  leftMotor.run(FORWARD);      // turn motor 1 forward
  rightMotor.run(BACKWARD);     // turn motor 2 backward   
  leftMotor.setSpeed(speedSet + MOTORS_CALIBRATION_OFFSET);
  rightMotor.setSpeed(speedSet);   

}
//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() {
  
  leftMotor.run(BACKWARD);     // turn motor 1 backward
  rightMotor.run(FORWARD);      // turn motor 2 forward
  leftMotor.setSpeed(speedSet + MOTORS_CALIBRATION_OFFSET);
  rightMotor.setSpeed(speedSet);   
  
}
//-------------------------------------------------------------------------------------------------------------------------------------
void lookRight() {
  rightMotor.run(BACKWARD);  // looking right? set right motor backwards for 400ms
  delay(400);
  rightMotor.run(FORWARD);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void lookLeft() {
  leftMotor.run(BACKWARD);  // looking left? set left motor backwards for 400ms
  delay(400);
  leftMotor.run(FORWARD);
}
//-----------------
