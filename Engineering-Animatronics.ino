/*Animatronic Master Code Holiday Themed PreCode Testing*/

//Included Libraries
#include <SoftwareSerial.h> //Library to use Serial monitor
#include <Servo.h> //Library to use and control Servos
#include <IRremote.h> //Library to use and control infrared
#include <LiquidCrystal_I2C.h> //Library used to setup and control the LCD Screen
//Flame Sensor Variable Setup
int const FlameSensorPin = A0; //Declare Flame Sensor Pin
int const FlameThreshold = 600; //Declare threshold for flame considered on
int FlameValue = 0; //Declare value of flame, later used to determine on or off
bool FlameOn = false; //Declare flame on or off
//bool FlameOverride = false;
//Motor Variable Setup
Servo MotorServo;
int const MotorPin = 10; //Declare pin slot for motor
int const TrainRunStop = 0;
int const TrainSpeedInterval = 5;
int const TrainMaxSpeed = 58; //93 is mid
int const TrainMinSpeed = 78; // 58 is fastest forwards, 128 fastest backwards
int const TrainSpeedDefault = 58;
//int const TrainFaster = 0xFD6097F; // Fast Forward
//int const TrainSlower = 0xFD20DF; // Rewind
int TrainRunSpeed = 58;
//Spotlight Variable Setup
int const SpotlightPin = 2; //Declare pin for LED on front, act as a spotlight
//Remote Control Variable Setup
int const IRremotePin = 11; //Declare pin for Infared Remote receiver
bool TrainRun = false; //use on/off button on remote to toggle true and false
unsigned long LastValue = 0x000000;
//int const PowerButtonHex = 0xFD00FF; //Power Button //Hex Code for power button, button labled power
//int const NiceButtonHex = 0xFD807F; // Vol + //Hex Code for nice button, button labeled
//int const NaughtyButtonHex = 0xFD906F; // Vol - //Hex Code for naughty button, button labeled
IRrecv irrecv(IRremotePin);
decode_results results;
//Present Servo Variable Setup
Servo PresentServo;
int const PresentServoPin = 9; //Declare pin of servo controlling nice presents
int const ServoDefaultPos = 80; //Starting position of the servo
int const ServoNicePourPos = 125; //Position to dump present
int const ServoNaughtyPourPos = 35; //Position to dump coal
int const ServoDispenseInterval = 20; //Interval to adjust servo dispensing speed
int ServoPos = 90;
//LCD Variable Setup
LiquidCrystal_I2C lcd(0x20, 16, 2); // set the LCD address to 0x20(Cooperate with 3 short circuit caps) for a 16 chars and 2 line display
//Werid Setup, figure it out

void setup() // put your setup code here, to run once:
{
  //Serial Setup
  Serial.begin(9600);
  //Flame Sensor Setup
  pinMode(FlameSensorPin, INPUT); //Assigns pin for the Flame Sensor
  //Remote Control Setup
  irrecv.enableIRIn();
  //Motor Setup
  MotorServo.attach(MotorPin); //Assigns the Motor to be controlled using servo controls
  //Front Spotlight Setup
  pinMode(SpotlightPin, OUTPUT); //Assigns pin for the LED Front light
  //LCD Screen Setup
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.home();

  lcd.setCursor(4, 0);
  lcd.print("Ho Ho Ho");
  lcd.setCursor(1, 1);
  lcd.print("Merry Christmas");
  Serial.println("LCD should be on");
  //Servo Setup
  PresentServo.attach(PresentServoPin); //Assigns pin for the Servo
  PresentServo.write(ServoDefaultPos); //Sets servo to starting position
}

void loop() // put your main code here, to run repeatedly:
{
  int FlameValue = analogRead(FlameSensorPin); //Equates variable "FlameValue" to the data read by flame sensor
  //Turn on flame if higher than threshold
  if (FlameValue > FlameThreshold) //Do if the flame value is greater than its threshold
  {
    FlameOn = true; //Write FlameOn as true
    digitalWrite(SpotlightPin, HIGH); //Turn on the spotlight while flame is lit
    delay(100);
  }
  else //Do if the flame value is less than its threshold
  {
    FlameOn = false; //Write FlameOn as false
    digitalWrite(SpotlightPin, LOW); //Turn off the spotlight while flame is lit
    delay(100);
  }
/*  if (irrecv.decode(&results))
  {
    if (results.value == 0xFDA05F)
    {
      FlameOverride = !FlameOverride;
    }
  }
*/
  //add Serial print commands within each loop to check
  while (FlameOn == true/* || FlameOverride == true*/) //Runs while the flame is lit
  {
    delay(100);
    Serial.println("Inside first loop");
    if (irrecv.decode(&results))
    {
      LastValue = results.value;
      Serial.println("inside second loop, ir received");
      if (results.value == 0xFFFFFF);
      {
        results.value = LastValue;
      }
      if (results.value == 0xFD00FF) //Do if power button is pressed
      {
        Serial.println("Powerbutton has been pressed and read");
        TrainRun = !TrainRun; //Toggle train as on/off
      }
    }
    irrecv.resume();
    while (TrainRun == true && FlameOn == true) //Do while train was turned "on" and the flame is lit
    {
      MotorServo.write(TrainRunSpeed);
      //Display Merry Christmas and HO HO HO, alternating and scrolling
      if (irrecv.decode(&results))
      {
        Serial.println(results.value, HEX);

        if (results.value == 0xFD906F) //Press volume down button to run scenario
        {
          Serial.println("Volume Down button pressed");
          MotorServo.write(TrainRunStop);
          lcd.clear(); //Laura used blink and noblink?
          lcd.setCursor(0, 0);
          lcd.print("Naughty");
          lcd.setCursor(9, 1);
          lcd.print("Naughty");
          PresentServo.write(ServoNaughtyPourPos);
          delay(1000);
          PresentServo.write(ServoDefaultPos);
//          for (int ServoPos = ServoDefaultPos; ServoPos < ServoNaughtyPourPos; ServoPos = ServoPos + 1)
//          {
//            PresentServo.write(ServoPos); //Moves servo to current servo position
//            delay(ServoDispenseInterval); //moves servo at controlled speed
//          }
//          delay(1000);
//          for (int ServoPos = ServoNaughtyPourPos; ServoPos > ServoDefaultPos; ServoPos = ServoPos - 1)
//          {
//            PresentServo.write(ServoPos); //Moves servo to current servo position
//            delay(ServoDispenseInterval);
//          }
//          delay(1000);
          MotorServo.write(TrainRunSpeed);
          lcd.clear();
          lcd.setCursor(4, 0);
          lcd.print("Ho Ho Ho");
          lcd.setCursor(1, 1);
          lcd.print("Merry Christmas");
        }
        else if (results.value == 0xFD00FF) //case for power button to turn off
        {
          Serial.println("Power Button is pressed to turn off train");
          TrainRun = !TrainRun; //Toggle train as on/off
          MotorServo.write(TrainRunStop);
        }
        else if (results.value == 0xFD807F) //Press Volume Up button to run scenario
        {
          
          Serial.println("Volume up pressed to dispense present");
          lcd.clear(); //clears display and set cursor to 0,0
          lcd.setCursor(0, 0);
          lcd.print("Nice!!  Nice!!");
          lcd.setCursor(6, 1);
          lcd.print("Nice!!");
          MotorServo.write(TrainRunStop);
          PresentServo.write(ServoNicePourPos);
          delay(1000);
          PresentServo.write(ServoDefaultPos);
//          for (int ServoPos = ServoDefaultPos; ServoPos > ServoNicePourPos; ServoPos = ServoPos - 1)
//          {
//            Serial.println("Inside For Loop");
//            PresentServo.write(ServoPos); //Moves servo to current servo position
//            delay(ServoDispenseInterval);
//            Serial.println(ServoPos);
//          }
//          Serial.println("Outside For Loop");
//          delay(1000);
//          for (int ServoPos = ServoNicePourPos; ServoPos < ServoDefaultPos; ServoPos = ServoPos + 1)
//          {
//            PresentServo.write(ServoPos); //Moves servo to current servo position
//            delay(ServoDispenseInterval);
//          }
//          delay(1000);
          MotorServo.write(TrainRunSpeed);
          lcd.clear();
          lcd.setCursor(4, 0);
          lcd.print("Ho Ho Ho");
          lcd.setCursor(1, 1);
          lcd.print("Merry Christmas");
        }
        else if (results.value == 0xFD609F) //Press Fast Forward button to increase speed of train
        {
          Serial.println("FF button pressed, and train increases speed");
          TrainRunSpeed = TrainRunSpeed - TrainSpeedInterval;
          if (TrainRunSpeed < TrainMaxSpeed)
          {
            TrainRunSpeed = TrainMaxSpeed;
          }
          MotorServo.write(TrainRunSpeed);
          Serial.println(TrainRunSpeed);
        }
        else if (results.value == 0xFD20DF)
        {
          Serial.println("Rewind button pressed, and train decreases speed");
          TrainRunSpeed = TrainRunSpeed + TrainSpeedInterval;
          if (TrainRunSpeed > TrainMinSpeed)
          {
            TrainRunSpeed = TrainMinSpeed;
          }
          MotorServo.write(TrainRunSpeed);
          Serial.println(TrainRunSpeed);
        }
        irrecv.resume();
      }
    }
  }
}
