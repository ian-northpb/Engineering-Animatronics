/*Animatronic Master Code Holiday Themed PreCode Testing*/


/*To Do List
 * Make LCD Say Merry Christmas and Ho Ho Ho while not doign anythign
 * 
 * Fill out case statement, run servo, and display naughty/nice
 * 
 * figure out how to use Infared Remote and sensor
 */
//Included Libraries
  #include <SoftwareSerial.h> //Library to use serial monitor
  #include <LiquidCrystal.h> //Library to use LCD Display
  #include <Servo.h> //Library to use and control Servos
  #include <IRremoteInt.h> //Library to control Infared Remote Control
  #include <IRremote.h> //Library used to control Infared Remote Control cont.
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
  pinMode(FlameSensorPin, INPUT); //Assigns pin for the Flame Sensor
//Remote Control Setup
  pinMode(IRremotePin, INPUT); //Assigns pin for the Infared Remote receiver
//Motor Setup
  pinMode(MotorPin, OUTPUT); //Assigns Pin for the drive motor
//Front Spotlight Setup
  pinMode(Spotlight, OUTPUT); //Assigns pin for the LED Front light
//LCD Screen Setup
  
//Nice Servo Setup
  NiceServo.attach(NiceServoPin); //Assigns pin for the "Nice" Servo
  NiceServo.write(NiceServoStartPos); //Sets servo to starting position
//Naughty Servo Setup
  NaughtyServo.attach(NaughtyServoPin); //Assigns pin for the "Naughty" Servo
  NaughtyServo.write(NaughtyServoStartPos); //Sets servo to starting position

}
void loop() // put your main code here, to run repeatedly:
{
  int FlameValue = analogRead(FlameSensorPin); //Equates variable "FlameValue" to the data read by flame sensor
  if (FlameValue > FlameThreshold) //Do if the flame value is greater than its threshold
  {
    bool FlameOn = true; //Write FlameOn as true
  }

  else //Do if the flame value is less than its threshold
  {
    bool FlameOn = false; //Write FlameOn as false
  }
  if (IRValue == 0/******POWER BUTTON*********Need to configure the remote data******************/) //Do if off button is pressed
  {
    bool TrainRun = !TrainRun; //Toggle train as on/off
  }
  while (FlameOn == true) //unsure if works because Bool FlameOn changes outside of loop //Do while the flame is lit
  {
    digitalWrite(Spotlight, HIGH); //Turn on the spotlight while flame is lit
    while (TrainRun == true) //Do while train was turned "on" and the flame is lit
    {
      switch (IRValue) //Use the remote to run different codes
      {
        case 1: //Press __ button to run scenario
//fill out action          //display naughty on LCD, and run servo naughty to drop black "coal"
          break; //ends case statement if case 1 is run
        case 2: //Press __ button to run scenario
//fill out action          //display nice on LCD, and run servo nice to drop colorful present
          break; //ends case statement if case 2 is run
        default: //default action if neither case 1 nor case 2 happens
          break; //ends code if default code runs
      }
    }
  }
}
