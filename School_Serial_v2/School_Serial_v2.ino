

//String this is where the data that I type in will get stored
String whatCameIn = "";


String extractNumberAsString = "";
int    extractNumberAsInteger = 0;

int iNumberToCheckFor = 99;

void setup() {

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
  if(whatCameIn.indexOf("A") == 0)           //If first Letter Contain A 
  {
    //Display back if what I typed back was equal to the letter A
    Serial.println("Got A");          
  }
  else if (whatCameIn.indexOf("B") == 0)     //If first Letter Contain B
  {
    //Display back if what I typed back was equal to the letter B
    Serial.println("Got B");          
  }
  else if (whatCameIn.indexOf("C") == 0)     //If first Letter Contain C
  {
      //Basics of an IF statement - Ex 1
      if(iNumberToCheckFor == 100)
      {
        Serial.println("Number is = 100");          
      }
      else if(iNumberToCheckFor != 100)
      {
        Serial.println("Number is != 100");          
      }
    
  }
  else if (whatCameIn.indexOf("D") == 0)     //If first Letter Contain D
  {
      //Example how to extract data out of a string and convert to a Value    

      //Get all string data past index 1 of string
      extractNumberAsString = whatCameIn.substring(1);
      Serial.println(extractNumberAsString);          

      //Convert string value to a number or integer using toInt();
      extractNumberAsInteger = extractNumberAsString.toInt();

      //Display to number but this has to be conveted back to a String due to 'Serial.println'
      Serial.println(String(extractNumberAsInteger));          
      
      //Basics of an IF statement - Ex 1
      if(extractNumberAsInteger == 10)
      {
        Serial.println("Number is = 10");
      }
      else
      {
        Serial.println("Number is != 10");
      }
      
  }
     
 }
     
}
