/*Animatronic Master Code
  Holiday Themed PreCode Testing
*/
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <IRremoteInt.h>
#include <IRremote.h>
//Flame Sensor Setup
  int const FlameSensorPin = A0; //Declare Flame Sensor Pin
  int const FlameThreshold = 100; //Declare threshold for flame considered on
  int FlameValue = 0; //Declare value of flame, later used to determine on or off
//Motor Setup
  int const MotorPin = A0; //Declare pin slot for motor
//Front Spotlight Setup
  int const Spotlight = 0; //Declare pin for LED on front, act as a spotlight
//Remote Control Setup
  int const IRremotePin = A0; //Declare pin for Infared Remote receiver
  int IRValue = 0; //Need to learn how to use this!!!! Remote and Receiver
  bool TrainRun = false; //use on/off button on remote to toggle true and false
//Servo Setup
  int const NiceServoPin = A0;
  int NiceServoPos = 0;
  int const NaughtyServoPin = A0;
  int NaughtyServoPos = 0;
//LCD Setup
  int const LCDScreenPin = 0;

bool FlameOn = false; //Declare flame on or off
void setup() // put your setup code here, to run once:
{
  pinMode(FlameSensorPin, INPUT);
  pinMode(IRremotePin, INPUT);
  pinMode(MotorPin, OUTPUT);
  pinMode(Spotlight, OUTPUT);
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
        case 3:
          bool TrainRun = false; //not sure if i need this, already stated outside
          break;
        default:
          break;
      }
    }
  }
  //digitalWrite(Spotlight, HIGH); //Turns off spotlight, maybe use spotlight?
  //  analogWrite(MotorPin, 0);
  //  else if (FlameOn == 1 && PresentIn == 1)
  //  {
  //    digitalWrite(LEDPin, HIGH);
  //    digitalWrite(Spotlight, HIGH);
  //    analogWrite(MotorPin, 125);
  //  }
  //  else
  //  {
  //    digitalWrite(Spotlight, LOW); //Turns off spotlight, maybe use spotlight?
  //    analogWrite(MotorPin, 0);
  //  }

}
