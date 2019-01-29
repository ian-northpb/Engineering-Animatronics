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
  #include <Servo.h> //Library to use and control Servos
  #include <IRremote.h> //Library to use and control infrared
  #include <LiquidCrystal_I2C.h> //Library used to setup and control the LCD Screen
//Flame Sensor Variable Setup
  int const FlameSensorPin = A0; //Declare Flame Sensor Pin
  int const FlameThreshold = 400; //Declare threshold for flame considered on
  int FlameValue = 0; //Declare value of flame, later used to determine on or off
  bool FlameOn = false; //Declare flame on or off
//Motor Variable Setup
  Servo MotorServo;
  int const MotorPin = 8; //Declare pin slot for motor
  int const TrainRunStop = 0;
  int const TrainSpeedInterval = 10;
  int const TrainMaxSpeed = 125;
  int const TrainMinSpeed = 25;
  unsigned long const TrainFaster = /*Not Correct Yet*/0xFFFFFF;
  unsigned long const TrainSlower = /*Not Correct Yet*/0xF5FFFA;
  int TrainRunSpeed = 100;
//Spotlight Variable Setup
  int const SpotlightPin = 2; //Declare pin for LED on front, act as a spotlight
//Remote Control Variable Setup
  int const IRremotePin = 11; //Declare pin for Infared Remote receiver
  unsigned long IRValue = 0x000000; //Need to learn how to use this!!!! Remote and Receiver
  bool TrainRun = false; //use on/off button on remote to toggle true and false
  unsigned long const PowerButtonHex = /*Not correct yet*/ 0xFD00FF; //Hex Code for power button, button labled power
  unsigned long const NiceButtonHex = /*Not correct yet*/ 0xFFFAFA; //Hex Code for nice button, button labeled
  unsigned long const NaughtyButtonHex = /*Not correct yet*/0xF0FFF0; //Hex Code for naughty button, button labeled
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
//Servo Setup
  PresentServo.attach(PresentServoPin); //Assigns pin for the Servo
  PresentServo.write(ServoDefaultPos); //Sets servo to starting position
}
void loop() // put your main code here, to run repeatedly:
{
  lcd.setCursor(3, 0);
  lcd.print("Ho Ho Ho");
  lcd.setCursor(0, 1);
  lcd.print("Merry Christmas");
  int FlameValue = analogRead(FlameSensorPin); //Equates variable "FlameValue" to the data read by flame sensor
  unsigned long IRValue = irrecv.decode(&results);
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
    if (IRValue == PowerButtonHex) //Do if power button is pressed
    {
      bool TrainRun = !TrainRun; //Toggle train as on/off
    }
    while (TrainRun == true) //Do while train was turned "on" and the flame is lit
    {
      //Display Merry Christmas and HO HO HO, alternating and scrolling
/*Necessary because of statement on line 80??*/      if (irrecv.decode(&results))
      {
        switch (IRValue) //Use the remote to run different codes
        {
          case NaughtyButtonHex: //Press __ button to run scenario
            MotorServo.write(TrainRunStop);
            lcd.clear(); //Laura used blink and noblink?
            lcd.setCursor(0, 0);
            lcd.print("Naughty");
            lcd.setCursor(1, 9);
            lcd.print("Naughty");
/* Fixed? */for (int ServoPos = ServoDefaultPos; ServoPos < ServoNaughtyPourPos; ServoPos = ServoPos + 1)
///*Fix this*/for (int ServoPos = ServoDefaultPos; ServoPos < ServoNaughtyPourPos; ServoPos = ServoPos + 1)
            {
/*Fix this*///analogWrite(/*Name of servo or servo pin????*/PresentServoPin, ServoPos);
              PresentServo.write(ServoPos); //Moves servo to current servo position
              delay(ServoDispenseInterval); //moves servo at controlled speed
            }
            delay(1000);
/* Fixed? */for (int ServoPos = ServoNaughtyPourPos; ServoPos > ServoDefaultPos; ServoPos = ServoPos - 1)
///*Fix this*/for (int ServoPos = ServoNaughtyPourPos; ServoPos > ServoDefaultPos; ServoPos = ServoPos - 1)
            {
/*Fix this*///analogWrite(/*Name of servo or servo pin????*/PresentServoPin, ServoPos);
              PresentServo.write(ServoPos); //Moves servo to current servo position
              delay(ServoDispenseInterval);
            }
            delay(1000);
            MotorServo.write(TrainRunSpeed);
            break; //ends case statement if case 1 is run
          case PowerButtonHex: //case for power button to turn off
            bool TrainRun = !TrainRun; //Toggle train as on/off
            break; // ends case statement if power button case is run
          case NiceButtonHex: //Press __ button to run scenario
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
            break; //ends case statement if case 2 is run
          case TrainFaster: //Press plus button to increase speed of train
            TrainRunSpeed =+ TrainSpeedInterval;
            if(TrainRunSpeed > TrainMaxSpeed)
              {
              int TrainRunSpeed = TrainMaxSpeed;
              }
            MotorServo.write(TrainRunSpeed);
            break;
          case TrainSlower:
            TrainRunSpeed =- TrainSpeedInterval;
            if(TrainRunSpeed < TrainMinSpeed)
            {
              int TrainRunSpeed = TrainMinSpeed;
            }
          MotorServo.write(TrainRunSpeed);
            break;
          default: //default action if neither case 1 nor case 2 happens
            break; //ends code if default code runs
        }
        irrecv.resume();
      }
    }
  }
}
