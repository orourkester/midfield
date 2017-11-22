int ledRed = 3;           // the PWM pin the LED is attached to RED Leg
int ledGreen = 5;           // the PWM pin the LED is attached to GREEN Leg
int ledBlue = 9;           // the PWM pin the LED is attached to BLUE Leg

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

int lightPin = A1;    // select the input pin for the potentiometer
int lightValue = 0;  // variable to store the value coming from the sensor

//String this is where the data that I type in will get stored
String whatCameIn = "";

void setup() {

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  analogWrite(ledRed, 255);
  analogWrite(ledGreen, 255);
  analogWrite(ledBlue, 255);

  //Sets up the serial Speed
  Serial.begin(9600);
}


//Program will just keep looping around here looking for work to do !
void loop() {

   lightValue = analogRead(lightPin);   
   Serial.print("lightValue:");
   Serial.println(lightValue);

   sensorValue = analogRead(sensorPin);   
   Serial.print("sensorValue:");
   Serial.println(sensorValue);
   delay(100);


  //Id the serial line is good to go
  while (Serial.available())
  {
   
    //Read what I am typing in to the computer
    whatCameIn = Serial.readString();

    //Display back what I typed
    Serial.println("What Came in:" + whatCameIn);

    //Check to see what I typed in !
    if (whatCameIn.indexOf("R") == 0)          //If first Letter Contain R
    {
      //Display back if what I typed back was equal to the letter R
      Serial.println("Got Red");
      DoRed();
    }
    else if (whatCameIn.indexOf("G") == 0)     //If first Letter Contain G
    {
      //Display back if what I typed back was equal to the letter G
      Serial.println("Got Green");
      DoGreen();

    }
    else if (whatCameIn.indexOf("B") == 0)     //If first Letter Contain B
    {
      //Display back if what I typed back was equal to the letter B
      Serial.println("Got Blue");
      DoBlue();
    }
    else if (whatCameIn.indexOf("F") == 0)     //If first Letter Contain F for Flash
    {
      //Display back if what I typed back was equal to the letter B
      Serial.println("Got Flash signal");
      DoRed();
      delay(300);
      DoGreen();
      delay(300);
      DoBlue();
      delay(300);
    }
    else if (whatCameIn.indexOf("L") == 0)     //If first Letter Contain L for Loop
    {
      //Display back if what I typed back was equal to the letter B
      Serial.println("Got Loop signal");

      for (int iLoop = 0; iLoop < 10; iLoop++)
      {
        DoRed();
        delay(100);
        DoGreen();
        delay(100);
        DoBlue();
        delay(100);
      }
    }
    else if (whatCameIn.indexOf("S") == 0)     //If first Letter Contain S for read sensor Value
    {
      for (int iLoop = 0; iLoop < 1000; iLoop++)
      {
          //read AO value
        sensorValue = analogRead(sensorPin);

        //Just do for Red
        analogWrite(ledRed, map(sensorValue, 0, 697, 0, 255));
        Serial.println(sensorValue);

        analogWrite(ledGreen, 255);
        analogWrite(ledBlue, 255);
      }
    }

  }

}

//use of a function block
void DoRed()
{
  analogWrite(ledRed, 0);
  analogWrite(ledGreen, 255);
  analogWrite(ledBlue, 255);
}
void DoGreen()
{
  analogWrite(ledRed, 255);
  analogWrite(ledGreen, 0);
  analogWrite(ledBlue, 255);
}
void DoBlue()
{
  analogWrite(ledRed, 255);
  analogWrite(ledGreen, 255);
  analogWrite(ledBlue, 0);
}


