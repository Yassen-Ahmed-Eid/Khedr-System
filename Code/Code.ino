#include <Servo.h>                                                                       
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(0, 1);
Servo shoulderServo; 
Servo elbowServo;    
Servo gripServo;   
Servo camServo;
int gasSensorPin = A0;
int watersensor = A1;
int soilsensor = A2;
int armAngle ;  
int speed = 150;    
int speedsec;
#define in1 5 
#define in2 6
#define in3 10
#define in4 11
#define LED 13
#define Buzzer 12
#define Airpump 9
int command;  
int speedArm = 10;  
void setup() {
 Serial.begin(9600);  
 shoulderServo.attach(2); 
 elbowServo.attach(3);    
 gripServo.attach(7);      
 camServo.attach(4);
 bluetooth.begin(9600);
 pinMode(gasSensorPin, INPUT);
 pinMode(soilsensor, INPUT);
 pinMode(watersensor, INPUT);
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT);
 pinMode(LED, OUTPUT);  
 pinMode(Buzzer, OUTPUT);
 pinMode(Airpump, OUTPUT);}


void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    char command = bluetooth.read();
    if (receivedChar == 'U' || receivedChar == 'D' || receivedChar == 'V' || 
        receivedChar == 'W' || receivedChar == 'X' || receivedChar == 'Y') {
      processArmCommand(receivedChar);
    } else {
      processRobotCommand(receivedChar);
    }}}
void processArmCommand(char command) {
  switch(command) {
    case 'U':
      moveShoulderUp();
      break;
    case 'D':
      moveShoulderDown();
      break;
    case 'V':
      moveElbowUp();
      break;
    case 'W':
      moveElbowDown();
      break;
    case 'X':
      openGrip();
      break;
    case 'Y':
      closeGrip();
      break;}}
void processRobotCommand(char command) {
  switch(command) {
    case 'F':
      moveForward();
      break;
    case 'B':
      moveBackward();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'G':
  moveForwardLeft();
      break;
    case 'I':
moveForwardRight();
      break;
    case 'H':
      moveBackwardLeft();
      break;
    case 'J':
      moveBackwardRight();
      break;
    case 'S':
      stopRobot();
      break;
    case 'A':
      Gassensor();
      break;
    case 'l':
      Camleft();
      break;
    case 'r':
Camright();
      break;
    case 'w':
      Watersensor();
      break;
    case 'h':
      Soil();
      break;
    case 'M':
      Ledon();
      break;
    case 'f':
      Ledoff();
      break;
    case 'N':
      BUZ();
      break;
    case 'a':
      Air();
      break;  
    case '0':

      speed = 100;
      break;
    case '1':
      speed = 60;
      break;
    case '2':
      speed = 150;
      break;
    case '3':
      speed = 165;
      break;
    case '4':
      speed = 178;
      break;
    case '5':
      speed = 191;
      break;

  case '6':
      speed = 204;
      break;
    case '7':
      speed = 216;
      break;
    case '8':
      speed = 229;
      break;
    case '9':
      speed = 242;
      break;
    case 'q':
      speed = 255;
  break;}}
void moveForward() {
  analogWrite(in1, speed);
  analogWrite(in3, speed);}
void moveBackward() {
  analogWrite(in2, speed);
  analogWrite(in4, speed);}
void turnLeft() {
  analogWrite(in3, speed);
  analogWrite(in2, speed);}
void turnRight() {
  analogWrite(in4, speed);
  analogWrite(in1, speed);}
void moveForwardLeft() {
  analogWrite(in1, speedArm);
  analogWrite(in3, speed);}
void moveForwardRight() {
  analogWrite(in1, speed);
  analogWrite(in3, speedArm);}
void moveBackwardRight() {
  analogWrite(in2, speed);
  analogWrite(in4, speedArm);}
void moveBackwardLeft() {
  analogWrite(in2, speedArm);
  analogWrite(in4, speed);}
void stopRobot() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);}
void Camleft() {
  armAngle = constrain(armAngle + speedArm, 0, 180);
camServo.write(armAngle);}
void Camright() {
  armAngle = constrain(armAngle - speedArm, 0, 180);
camServo.write(armAngle);}
void moveShoulderUp() {
  armAngle = constrain(armAngle + speedArm, 0, 180);
shoulderServo.write(armAngle);}
void moveShoulderDown() {
  armAngle = constrain(armAngle - speedArm, 0, 180);
shoulderServo.write(armAngle);}
void moveElbowUp() {
  armAngle = constrain(armAngle + speedArm, 0, 180);
elbowServo.write(armAngle);}
void moveElbowDown() {
  armAngle = constrain(armAngle - speedArm, 0, 180);
  elbowServo.write(armAngle);}
void openGrip() {
  armAngle = constrain(armAngle + speedArm, 0, 180);
  gripServo.write(armAngle);}
void closeGrip() {
  armAngle = constrain(armAngle - speedArm, 0, 180);
  gripServo.write(armAngle);}
void Ledon() {
 digitalWrite(LED,1);}
void Ledoff() {
 digitalWrite(LED,0);}
void BUZ() {
digitalWrite(Buzzer,1);
  delay(500);
digitalWrite(Buzzer,0);}
void Air() {
digitalWrite(Airpump,255);}
void Soil(){
  int soil = analogRead(soilsensor)
  Serial.println(soil);
  bluetooth.print(soil);  bluetooth.println(soil);
  Serial.print("");
  Serial.println(soil);}
void Gassensor(){
  int gasValue = analogRead(gasSensorPin);
Serial.println(gasValue);
bluetooth.print(gasValue);
bluetooth.println(gasValue);
  Serial.print("");
Serial.println(gasValue);}
void Watersensor(){
  int Water = analogRead(watersensor);
  Serial.println(Water);
bluetooth.print(Water);
bluetooth.println(Water);
  Serial.print("");
 Serial.println(Water);}
