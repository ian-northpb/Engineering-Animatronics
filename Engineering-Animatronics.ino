/*Animatronic Master Code Holiday Themed PreCode Testing*/

/*To Do List
   Configure the correct values for the remote buttons
   Check variable identifiers in case statements. Arduino fails to compiled when some variables are identified.
*/
//Included Libraries
#include <SoftwareSerial.h> //Library to use serial monitor
#include <Servo.h> //Library to use and control Servos
#include <IRremote.h> //Library to use and control infrared
#include <LiquidCrystal_I2C.h> //Library used to setup and control the LCD Screen
//Flame Sensor Variable Setup
int const FlameSensorPin = A0; //Declare Flame Sensor Pin
int const FlameThreshold = 600; //Declare threshold for flame considered on
int FlameValue = 0; //Declare value of flame, later used to determine on or off
bool FlameOn = false; //Declare flame on or off
//Motor Variable Setup
Servo MotorServo;
int const MotorPin = 10; //Declare pin slot for motor
int const TrainRunStop = 0;
int const TrainSpeedInterval = 5;
int const TrainMaxSpeed = 58; //93 is mid
int const TrainMinSpeed = 85; // 58 is fastest forwards, 128 fastest backwards
int const TrainFaster = 0xFD609F; // Fast Forward
int const TrainSlower = 0xFD20DF; // Rewind
int TrainRunSpeed = 100;
//Spotlight Variable Setup
int const SpotlightPin = 2; //Declare pin for LED on front, act as a spotlight
//Remote Control Variable Setup
int const IRremotePin = 11; //Declare pin for Infared Remote receiver
bool TrainRun = false; //use on/off button on remote to toggle true and false
int const PowerButtonHex = 0xFD00FF; //Power Button //Hex Code for power button, button labled power
int const NiceButtonHex = 0xFFFAFA; // Vol + //Hex Code for nice button, button labeled
int const NaughtyButtonHex = 0xFD906F; // Vol - //Hex Code for naughty button, button labeled
IRrecv irrecv(IRremotePin);
decode_results results;
//Present Servo Variable Setup
Servo PresentServo;
int const PresentServoPin = 9; //Declare pin of servo controlling nice presents
int const ServoDefaultPos = 90; //Starting position of the servo
int const ServoNicePourPos = 180; //Position to dump present
int const ServoNaughtyPourPos = 0; //Position to dump coal
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
    bool FlameOn = true; //Write FlameOn as true
    digitalWrite(SpotlightPin, HIGH); //Turn on the spotlight while flame is lit
  }
  else //Do if the flame value is less than its threshold
  {
    bool FlameOn = false; //Write FlameOn as false
    digitalWrite(SpotlightPin, LOW); //Turn off the spotlight while flame is lit
  }

  while (FlameOn == true) //Runs while the flame is lit
  {
    //display Merry Christmas
    /*if(irrecv.decode(&results)) {} //Not sure if necessary*************************************************/
    if (results.value == PowerButtonHex) //Do if power button is pressed
    {
      bool TrainRun = !TrainRun; //Toggle train as on/off
    }
    while (TrainRun == true && FlameOn == true) //Do while train was turned "on" and the flame is lit
    {
      //Display Merry Christmas and HO HO HO, alternating and scrolling
      if (irrecv.decode(&results))
      {
        Serial.println(results.value, HEX);

        if (results.value == NaughtyButtonHex) //Press __ button to run scenario
        {
          MotorServo.write(TrainRunStop);
          lcd.clear(); //Laura used blink and noblink?
          lcd.setCursor(0, 0);
          lcd.print("Naughty");
          lcd.setCursor(9, 1);
          lcd.print("Naughty");
          /* Fixed? */for (int ServoPos = ServoDefaultPos; ServoPos < ServoNaughtyPourPos; ServoPos = ServoPos + 1)
          {
            PresentServo.write(ServoPos); //Moves servo to current servo position
            delay(ServoDispenseInterval); //moves servo at controlled speed
          }
          delay(1000);
          /* Fixed? */for (int ServoPos = ServoNaughtyPourPos; ServoPos > ServoDefaultPos; ServoPos = ServoPos - 1)
          {
            PresentServo.write(ServoPos); //Moves servo to current servo position
            delay(ServoDispenseInterval);
          }
          delay(1000);
          MotorServo.write(TrainRunSpeed);
        }
        else if (results.value == PowerButtonHex) //case for power button to turn off
        {
          TrainRun = !TrainRun; //Toggle train as on/off
        }
        else if (results.value == NiceButtonHex) //Press __ button to run scenario
        {
          lcd.clear(); //clears display and set cursor to 0,0
          lcd.setCursor(0, 0);
          lcd.print("Nice!!  Nice!!");
          lcd.setCursor(6, 1);
          lcd.print("Nice!!");
          MotorServo.write(TrainRunStop);
          /* Fixed? */for (int ServoPos = ServoDefaultPos; ServoPos > ServoNicePourPos; ServoPos = ServoPos - 1)
            ///*Fix this*/for (int ServoPos = ServoDefaultPos; ServoPos > ServoNicePourPos; ServoPos = ServoPos - 1)
          {
            /*Fix this*///analogWrite(/*Name of servo or servo pin????*/PresentServoPin, ServoPos);
            PresentServo.write(ServoPos); //Moves servo to current servo position
            delay(ServoDispenseInterval);
          }
          delay(1000);
          /* Fixed? */for (int ServoPos = ServoNicePourPos; ServoPos < ServoDefaultPos; ServoPos = ServoPos + 1)
            ///*Fix this*/for (int ServoPos = ServoNicePourPos; ServoPos < ServoDefaultPos; ServoPos = ServoPos + 1)
          {
            /*Fix this*///analogWrite(/*Name of servo or servo pin????*/PresentServoPin, ServoPos);
            PresentServo.write(ServoPos); //Moves servo to current servo position
            delay(ServoDispenseInterval);
          }
          delay(1000);
          MotorServo.write(TrainRunSpeed);
        }
        else if (results.value == TrainFaster) //Press plus button to increase speed of train
        {
          TrainRunSpeed = - TrainSpeedInterval;
          if (TrainRunSpeed < TrainMaxSpeed)
          {
            int TrainRunSpeed = TrainMaxSpeed;
          }
          MotorServo.write(TrainRunSpeed);
        }
        else if (results.value == TrainSlower)
        {
          TrainRunSpeed = + TrainSpeedInterval;
          if (TrainRunSpeed > TrainMinSpeed)
          {
            int TrainRunSpeed = TrainMinSpeed;
          }
          MotorServo.write(TrainRunSpeed);
        }
        irrecv.resume();
      }
    }
  }
}
