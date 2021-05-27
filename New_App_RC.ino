#include <Servo.h> //Imports the server library
Servo servo; //Defines the servo

String readString;  //Defines the string readString - also might be a command idk
int ControlPin = 3; //Defines the integer ControlPin to 3

void setup() {
  pinMode(ControlPin, OUTPUT);  //Tells the arduino that the pin is an output
  analogWrite(ControlPin, 0); //Sets the motor to 0 speed
  Serial.begin(9600); //Starts serial gathering
  servo.attach(9);  //Determines port of servo
  servo.write(75);  //Determines starting angle of servo
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
    if (speedy >= 0 && speedy < 256)  { //
      analogWrite(ControlPin, speedy);  //
    }                                   //
    else if  (speedy < 0)  {            //
      analogWrite(ControlPin, 0);       //Getting rid of outliers and setting motor speed
    }                                   //
    else if (speedy >= 256)  {          //
      analogWrite(ControlPin, 255);     //
    }                                   //
    
    readString.remove(0, 6);  //Removing first garbage to reveal second number from garbage app
    int angle = readString.toInt(); //Set angle to second integer input
    angle = angle - 53; //More math to make garbage app work with cheap servo
    servo.write(angle); //Set servo angle
    readString="";  //No clue
  } 
}
