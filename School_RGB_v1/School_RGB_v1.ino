int ledRed = 3;           // the PWM pin the LED is attached to RED Leg
int ledGreen = 5;           // the PWM pin the LED is attached to GREEN Leg
int ledBlue = 9;           // the PWM pin the LED is attached to BLUE Leg

//String this is where the data that I type in will get stored
String whatCameIn = "";

void setup() {

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  //Sets up the serial Speed  
  Serial.begin(9600);
}


//Program will just keep looping around here looking for work to do !
void loop() {

 //Id the serial line is good to go
 while(Serial.available())
 {

  //Read what I am typing in to the computer 
  whatCameIn = Serial.readString();

  //Display back what I typed
  Serial.println("What Came in:" + whatCameIn); 

  //Check to see what I typed in !
  if(whatCameIn.indexOf("R") == 0)           //If first Letter Contain A 
  {
    //Display back if what I typed back was equal to the letter A
    Serial.println("Got R");          
    analogWrite(ledRed, 0);
    analogWrite(ledGreen, 255);
    analogWrite(ledBlue, 255);    
  }
  else if (whatCameIn.indexOf("G") == 0)     //If first Letter Contain B
  {
    //Display back if what I typed back was equal to the letter B
    Serial.println("Got G");    
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 0);
    analogWrite(ledBlue, 255);         
  }
  else if (whatCameIn.indexOf("B") == 0)     //If first Letter Contain B
  {
    //Display back if what I typed back was equal to the letter B
    Serial.println("Got B");    
    analogWrite(ledRed, 255);
    analogWrite(ledGreen, 255);
    analogWrite(ledBlue, 0);         
  }
  
 }
     
}
