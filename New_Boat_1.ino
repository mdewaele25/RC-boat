#define enA 5 //
#define in1 7 //
#define in2 8 //
#define enB 11  //Setting all of the motor drive pins
#define in3 12  //
#define in4 13  //

String readString;  //Defines the string readString - also might be a command idk

void setup() {
  pinMode(enA, OUTPUT); //
  pinMode(enB, OUTPUT); //
  pinMode(in1, OUTPUT); //Designating all of the pins as output
  pinMode(in2, OUTPUT); //
  pinMode(in3, OUTPUT); //
  pinMode(in4, OUTPUT); //
  
  Serial.begin(9600); //Starts serial gathering
  Serial.println("Happy Boating!"); //Displays a happy message
  


}

void loop() {

  while (Serial.available()) { //Asks for serial input
    char state = Serial.read(); //Defines state as the serial input
    readString += state; //Sets readString to the serial input
    delay(2); //Some delay idk
  }

  if (readString.length() >0) { //Checks if the input is actually a number
    readString.remove(0, 2);  //Removes the first 2 indexes of the garbage input from garbage app
    int speedy = readString.toInt();  //Sets speedy to the integer input
    speedy = (speedy - 128) * 2;  //Math genius to make garbage app work better
    if (speedy > 0 && speedy < 256)  { 
      digitalWrite(in1,HIGH);   //
      digitalWrite(in2,LOW);    //Determining the rotation direction (forwards)
      digitalWrite(in3,HIGH);   //
      digitalWrite(in4,LOW);    //
      analogWrite(enA, speedy); //Setting speed to input speed
      analogWrite(enB, speedy); //
    }
    else if  (speedy > -256 && speedy < 0)  {
      digitalWrite(in1,LOW);    //
      digitalWrite(in2,HIGH);   //Determining the rotation direction (backwards)
      digitalWrite(in3,LOW);    //
      digitalWrite(in4,HIGH);   //
      analogWrite(enA, -speedy);  //Setting speed to input speed
      analogWrite(enB, -speedy);  //
    }
    else if (speedy >= 256 || speedy == -256)  {
      speedy = 255;               //
      analogWrite(enA, speedy);   //Setting speed to max in case of max throttle
      analogWrite(enB, speedy);   //
    }
    else if (speedy == 0) {
      analogWrite(enA, speedy); //Setting speed to 0
      analogWrite(enB, speedy); //
    }
    
    readString.remove(0, 6);      //Removing first garbage to reveal second number from garbage app
    int angle = readString.toInt();   //Set angle to second integer input
    if (speedy != 0)  {    
    if (angle < 128 && angle > 0) {         //
      speedy = (angle / 128.0) * speedy;    //Setting one motor to a fraction of the total speed
      analogWrite(enA, speedy);             //
    }
    else if (angle > 128 && angle < 256) {        //
      speedy = ((256 - angle) / 128.0) * speedy;  //Setting one motor to a fraction of the total speed
      analogWrite(enB, speedy);                   //
    }
    else if (angle == 0)  {         //
      speedy = 0;                   //Setting one motor to zero speed in case of max turn
      analogWrite(enA, speedy);     //
    }
    else if (angle == 256)  {   //
      speedy = 0;               //Setting one motor to zero speed in case of max turn
      analogWrite(enB, speedy); //
    }
    readString="";  //No fucking clue
    }
    else if (speedy == 0) {     //
      analogWrite(enB, 0);      //Setting both speeds to zero if main throttle is zero (safety protocol)
      analogWrite(enA, 0);      //
      readString="";            //No clue
    }
  }
  }






