/*Animatronic Master Code
  Holiday Themed PreCode Testing
*/
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <IRremoteInt.h>
#include <IRremote.h>
//Flame Sensor Variable Setup
  int const FlameSensorPin = A0; //Declare Flame Sensor Pin
  int const FlameThreshold = 100; //Declare threshold for flame considered on
  int FlameValue = 0; //Declare value of flame, later used to determine on or off
  bool FlameOn = false; //Declare flame on or off
//Motor Variable Setup
  int const MotorPin = A1; //Declare pin slot for motor
//Front Spotlight Variable Setup
  int const Spotlight = 1; //Declare pin for LED on front, act as a spotlight
//Remote Control Variable Setup
  int const IRremotePin = A2; //Declare pin for Infared Remote receiver
  int IRValue = 0; //Need to learn how to use this!!!! Remote and Receiver
  bool TrainRun = false; //use on/off button on remote to toggle true and false
//Nice Servo Variable Setup
  Servo NiceServo;
  int const NiceServoPin = 9; //Declare pin of servo controlling nice presents
  int NiceServoStartPos = 0; //Starting position of the servo
  int NiceServoPourPos = 90; //Position to dump present
//Naughty Servo Variable Setup
  Servo NaughtyServo;
  int const NaughtyServoPin = 10; //Declare pin of servo controlling coal
  int NaughtyServoStartPos = 0; //Starting position of the servo
  int NaughtyServoPourPos = 90; //Position to dump coal
//LCD Variable Setup

void setup() // put your setup code here, to run once:
{
//Flame Sensor Setup
  pinMode(FlameSensorPin, INPUT);
//Remote Control Setup
  pinMode(IRremotePin, INPUT);
//Motor Setup
  pinMode(MotorPin, OUTPUT);
//Front Spotlight Setup
  pinMode(Spotlight, OUTPUT);
//LCD Screen Setup
  
//Nice Servo Setup
  NiceServo.attach(NiceServoPin);
  NiceServo.write(NiceServoStartPos);
//Naughty Servo Setup
  NaughtyServo.attach(NaughtyServoPin);
  NaughtyServo.write(NaughtyServoStartPos);

}
void loop() // put your main code here, to run repeatedly:
{
  bool FlameValue = analogRead(FlameSensorPin);
  if (FlameValue > FlameThreshold)
  {
    bool FlameOn = true;
  }

  else
  {
    bool FlameOn = false;
  }
  if (IRValue == 1)
  {
    bool TrainRun = true;
  }
  if (IRValue == 0)
  {
    bool TrainRun = false;
  }
  while (FlameOn == true) //unsure if works because Bool FlameOn changes outside of loop
  {
    digitalWrite(Spotlight, HIGH);
    while (TrainRun == true)
    {
      switch (IRValue)
      {
        case 1:
          //display naughty, and run servo 1 to drop black "coal"
          break;
        case 2:
          //display nice and run servo 2 to drop colorful present
          break;
        default:
          break;
      }
    }
  }
}
