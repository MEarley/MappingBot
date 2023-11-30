#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"
#include <Servo.h>

#define PI 3.1415926535897932384626433832795

DeviceDriverSet_Motor AppMotor;
Application_xxx Application_SmartRobotCarxxx0;
Servo servo;  // create servo object to control a servo
// Define Pins
const int ECHOPIN = 12;
const int TRIGPIN = 13;
const int SERVOPIN = 10;  // Ultra Sonic Servo

int pos = 0;
bool isScanning = true;
bool start = false;

void setup() {
  AppMotor.DeviceDriverSet_Motor_Init();
  delay(2000);
  //for (Application_SmartRobotCarxxx0.Motion_Control = 0; Application_SmartRobotCarxxx0.Motion_Control < 9; Application_SmartRobotCarxxx0.Motion_Control = Application_SmartRobotCarxxx0.Motion_Control + 1)
  //{
  //  ApplicationFunctionSet_SmartRobotCarMotionControl(Application_SmartRobotCarxxx0.Motion_Control /*direction*/, 200 /*speed*/);
  //  delay(1000);
  //}

  Serial.begin(115200);     // set up Serial monitor with 9600 baud rate
  Serial.println("Setting up");

  // Sets Pins for Senors
  pinMode(ECHOPIN, INPUT);
  Serial.print("Echo Pin set to: ");
  Serial.println(ECHOPIN);

  pinMode(TRIGPIN, OUTPUT);
  Serial.print("TRIG Pin set to: ");
  Serial.println(TRIGPIN);

  servo.attach(SERVOPIN);  // attaches the servo on pin 9 to the servo object
  Serial.print("SERVO Pin set to: ");
  Serial.println(SERVOPIN);
  servo.write(pos);
  delay(2000);
}

void loop() {
  if(!start){
    start = true;
    Serial.println("Start!");
  }
  while(isScanning == true){
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);

    float duration_us = pulseIn(ECHOPIN, HIGH);
    float distance_cm = 0.017 * duration_us;

    //Serial.println(distance_cm);
    if(distance_cm > 400){
      //Serial.println("Out of maximum range of 400 cm");
      distance_cm = 450;
    }

    if(pos < 180){
      servo.write(pos++);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }

    // Cosθ = x / r | x = rCosθ = x 
    // Sinθ = y / r | y = rSinθ
    // degrees to radians = degrees * pi / 180
    float radians = pos * PI / 180;
    //Serial.print(PI);
    //Serial.print(", ");
    //Serial.println(pos);
    float x = distance_cm * cos(radians); 
    float y = distance_cm * sin(radians);

    //Serial.print(x);
    //Serial.print(",");
    //Serial.print(y);
    //Serial.print(",");
    //Serial.println(pos);
    Serial.println(String(x) + "," + String(y) + "," + String(pos));
    //Serial.println("");

    delay(100);
  
    if(pos >= 180){
      isScanning = false;
      Serial.println("Done.");
    }
  }
  delay(10000);




}
