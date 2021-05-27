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
    int state = Serial.read(); //Defines state as the serial input
    Serial.println(Serial.read());
    readString += state; //Sets readString to the serial input
    delay(2); //Some delay idk
  }

  if (Serial.available() > 0) {

    int speedy =  -1 * (50 - Serial.read());
    radio.write(&speedy, sizeof(speedy));
    int angle = -1 * (Serial.read() - 50);
    radio.write(&angle, sizeof(angle));

    
    Serial.print("X: ");
    Serial.print(speedy);
    Serial.print("  Y: ");
    Serial.println(angle);
  }


  
  delay(10);

}
