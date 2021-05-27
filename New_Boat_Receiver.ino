#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

const byte address[6] = "00001";

int flag = 1;
  int speedy = 0;  
  int angle = 128;
int  speed1 = 0;

#define enA 5 //
#define in1 2 //
#define in2 4 //
#define enB 6  //Setting all of the motor drive pins
#define in3 3  //
#define in4 9  //

void setup() {
  pinMode(enA, OUTPUT); //
  pinMode(enB, OUTPUT); //
  pinMode(in1, OUTPUT); //Designating all of the pins as output
  pinMode(in2, OUTPUT); //
  pinMode(in3, OUTPUT); //
  pinMode(in4, OUTPUT); //
  
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
}

void loop() {
  
  if (radio.available() && flag == 1) {
    radio.read(&speedy, sizeof(speedy));
    Serial.print("Speedy:  ");
    Serial.println(speedy);
    flag = 2;
  }
   if (radio.available() && flag == 2)  {
    radio.read(&angle, sizeof(angle));
    Serial.print("Angle:   ");
    Serial.println(angle);
    

    flag = 1;
      }
      


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
    else if (speedy >= 256 || speedy == -256)  {               //
      analogWrite(enA, 255);   //Setting speed to max in case of max throttle
      analogWrite(enB, 255);   //
    }
    else if (speedy == 0) {
      analogWrite(enA, speedy); //Setting speed to 0
      analogWrite(enB, speedy); //
    }

  if (speedy != 0)  {    
    if (angle < 128 && angle > 0) {         //
      speed1 = (angle / 128.0) * speedy;    //Setting one motor to a fraction of the total speed
      analogWrite(enB, speed1);
    }
    else if (angle > 128 && angle < 256) {        //
      speed1 = ((256 - angle) / 128.0) * speedy;  //Setting one motor to a fraction of the total speed
      analogWrite(enA, speed1);                   //
    }
    else if (angle == 0)  {         //
      speed1 = 0;                   //Setting one motor to zero speed in case of max turn
      analogWrite(enB, speed1);     //
    }
    else if (angle == 256)  {   //
      speed1 = 0;               //Setting one motor to zero speed in case of max turn
      analogWrite(enA, speed1); //
    }
    }

  }

