#include <SoftwareSerial.h>

SoftwareSerial ArduinoUno(2,3);

#include <Servo.h>

Servo myservo;

int smoke = A5;
int smoke2 = A1;
int light = A4;
int light2 = A0;
int pump = 7;
int led = 8;
String msg;

int position = 0;

void setup() {
  pinMode(smoke, INPUT);
  pinMode(light, INPUT);
  pinMode(smoke2, INPUT);
  pinMode(light2, INPUT);
  pinMode(pump,OUTPUT);
  pinMode(led,OUTPUT);
  
  myservo.attach(9);
  
  Serial.begin(9600);
  ArduinoUno.begin(115200);

  myservo.write(77);
}

void loop() {
  int analogSensorMQ2 = analogRead(smoke);
  int analogLight = analogRead(light);
  int analogSensorMQ2_2 = analogRead(smoke2);
  int analogLight_2 = analogRead(light2);
  
  Serial.print("Light (A4): ");
  Serial.print("\t\t ");
  Serial.print("Light (A0): ");
  Serial.print("\t\t");
  
  Serial.print("Smoke (A5): ");
  Serial.print("\t\t ");
  Serial.print("Smoke (A1): ");
  Serial.println();
  
  Serial.print(analogLight);
  Serial.print("\t\t\t ");
  Serial.print(analogLight_2);
  Serial.print("\t\t\t ");
  Serial.print(analogSensorMQ2);
  Serial.print("\t\t\t ");
  Serial.print(analogSensorMQ2_2);  
  Serial.println();

  msg = String(analogLight) + "-" +String(analogLight_2)+ "-" + String(analogSensorMQ2)+ "-" + String(analogSensorMQ2_2);
  
  //Left Side
  if (analogLight < 100 || analogSensorMQ2 > 150){
    Serial.println("Left Side Fire");
    ledblink();
    servomoving(175);
    digitalWrite(pump,LOW);
    msg = msg+ "-" + "LeftSide"+"-";
}

  //Right Side 
  
  else if (analogLight_2 < 225 || analogSensorMQ2_2 > 1000){
    Serial.println("Right Side Fire");
    ledblink();
    servomoving(-25);
    digitalWrite(pump,LOW);
    msg = msg+ "-" + "RightSide"+"-";
}

else {
  digitalWrite(led,LOW);
  myservo.write(77);
  digitalWrite(pump,HIGH);
  msg = msg+ "-" + "Normal"+"-";
}

ArduinoUno.println(msg);
delay(2000);
}


void servomoving(int pos){
    myservo.write(pos);
    delay(2000);
}

void ledblink(){
  for(int time = 0 ; time<10; time++){
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
  }
}
