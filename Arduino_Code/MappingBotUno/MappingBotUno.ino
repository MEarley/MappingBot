#include <Servo.h>

Servo servo;  // create servo object to control a servo

// Define Pins
const int ECHOPIN = 12;
const int TRIGPIN = 13;
const int SERVOPIN = 10;  // Ultra Sonic Servo

/*
const int ECHOPIN = 8;
const int TRIGPIN = 9;
const int LIGHTPIN = 10;
const int SERVOPIN = 11;
*/

int pos = 0;

int i = 0;
void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
  if (Serial.available())
    Serial.write( "hello\n");
    Serial.println(i++);

  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  float duration_us = pulseIn(ECHOPIN, HIGH);
  float distance_cm = 0.017 * duration_us;

  Serial.println(distance_cm);
  if(distance_cm > 400){
    Serial.println("Out of maximum range of 400 cm");
  }

  if(pos < 360){
    servo.write(pos++);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  

  delay(500);
  
}
