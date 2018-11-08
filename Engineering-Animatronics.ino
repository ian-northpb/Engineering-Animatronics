/*Animatronic Master Code
  Holiday Themed PreCode Testing
*/
#include <LiquidCrystal.h>
#include <Servo.h>
#include <IRremoteInt.h>
#include <IRremote.h>
int const FlameSensorPin = A0; //Declare Flame Sensor Pin
int const MotorPin = A0; //Declare pin slot for motor
int const Spotlight = 0; //Declare pin for LED on front, act as a spotlight
int const IRremotePin = A0;
int const FlameThreshold = 100; //Declare threshold for flame considered on
int FlameValue = 0; //Declare value of flame, later used to determine on or off
bool FlameOn = false; //Declare flame on or off
void setup() // put your setup code here, to run once:
{
  pinMode(FlameSensorPin, INPUT);
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
    int FlameOn = 0;
  }
  while (FlameOn == true) //unsure if works because Bool FlameOn changes outside of loop
  {
    digitalWrite(Spotlight, HIGH)
    switch 
    
  }
digitalWrite(Spotlight, HIGH); //Turns off spotlight, maybe use spotlight?
  analogWrite(MotorPin, 0);
  else if (FlameOn == 1 && PresentIn == 1)
  {
    digitalWrite(LEDPin, HIGH);
    digitalWrite(Spotlight, HIGH);
    analogWrite(MotorPin, 125);
  }
  else
  {
    digitalWrite(LEDPin, LOW);
    digitalWrite(Spotlight, LOW); //Turns off spotlight, maybe use spotlight?
    analogWrite(MotorPin, 0);

  }

}
