//BASIC RC CONTROLS

#include <Servo.h>

Servo servo;

int ControlPin = 3;  
int state = 0;
int flag = 0; 
int speedy = 0;
int angle = 0;

void setup() {
    // sets the pins as outputs:
    pinMode(ControlPin, OUTPUT);
    analogWrite(ControlPin, 0);
    servo.attach(9);
    servo.write(75);
    Serial.begin(9600); // Default connection rate for my BT module
}

void loop() {
    //if some data is sent, read it and save it in the state variable
    if(Serial.available() > 0){
      state = Serial.read();
      flag=0;
    }

    if (state == '0') {
        if(flag == 0 && speedy > 0){
          speedy = speedy - 50;
          analogWrite(ControlPin, speedy);
          Serial.println("Speed Down");
          Serial.println(speedy);
          flag = 1;
        }
    }

    else if (state == '1') {     
        if(flag == 0 && speedy < 250){
          speedy = speedy + 50;
          analogWrite(ControlPin, speedy);
          Serial.println("Speed Up");
          Serial.println(speedy);
          flag = 1;
        }
    }
    else if (state == '2')  {
      if(flag == 0 && angle < 200){
        angle = angle + 40;
        servo.write(angle);
        Serial.println("Angle Left");
        Serial.println(angle);
        flag = 1;
      }      
    }
    else if (state == '3')  {
        if(flag == 0 && angle > 0){
        angle = angle - 40;
        servo.write(angle);
        Serial.println("Angle Right");
        Serial.println(angle);
        flag = 1;
      }
    }
    else if (state == '4')  {
      if (flag == 0)  {
      angle = 75;
      speedy = 0;
      analogWrite(ControlPin, speedy);
      servo.write(angle);
      Serial.println("Full Stop");
      flag = 1;
      }
    }
}
