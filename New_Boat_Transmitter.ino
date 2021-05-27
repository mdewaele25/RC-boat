#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

const byte address[6] = "00001";


String readString;  //Defines the string readString - also might be a command idk

void setup() {

  
  Serial.begin(9600); //Starts serial gathering
  Serial.println("Happy Boating!"); //Displays a happy message
    
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {

  while (Serial.available()) { //Asks for serial input
    char state = Serial.read(); //Defines state as the serial input
    Serial.println(Serial.read());
    readString += state; //Sets readString to the serial input
    delay(2); //Some delay idk
  }

  if (readString.length() >0) { //Checks if the input is actually a number
    readString.remove(0, 2);  //Removes the first 2 indexes of the garbage input from garbage app
    int speedy = readString.toInt();  //Sets speedy to the integer input
    speedy = (speedy - 128) * 2;  //Math genius to make garbage app work better
    radio.write(&speedy, sizeof(speedy));
  
    readString.remove(0, 6);      //Removing first garbage to reveal second number from garbage app
    int angle = readString.toInt();   //Set angle to second integer input
    radio.write(&angle, sizeof(angle));
    readString = "";
    }
  }






