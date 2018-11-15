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
  #include <LiquidCrystal_I2C.h>
//Flame Sensor Variable Setup
  int const FlameSensorPin = A0; //Declare Flame Sensor Pin
  int const FlameThreshold = 400; //Declare threshold for flame considered on
  int FlameValue = 0; //Declare value of flame, later used to determine on or off
  bool FlameOn = false; //Declare flame on or off
//Motor Variable Setup
  int const MotorPin = A1; //Declare pin slot for motor
  int const TrainRunStop = 0;
  int const TrainRunSpeed = 100;
//Spotlight Variable Setup
  int const Spotlight = 2; //Declare pin for LED on front, act as a spotlight
//Remote Control Variable Setup
  int const IRremotePin = 11; //Declare pin for Infared Remote receiver
  unsigned long IRValue = 0x000000; //Need to learn how to use this!!!! Remote and Receiver
  bool TrainRun = false; //use on/off button on remote to toggle true and false
  unsigned long const PowerButtonHex = 0xFD00FF; //Hex Code for power button, button labled power
  unsigned long const NiceButtonHex = 0xFFFAFA; //Hex Code for nice button, button labeled
  unsigned long const NaughtyButtonHex = 0xF0FFF0; //Hex Code for naughty button, button labeled
  IRrecv irrecv(IRremotePin);
  decode_results results;
//Servo Variable Setup
  Servo PresentServo;
  int const PresentServoPin = 9; //Declare pin of servo controlling nice presents
  int const ServoDefaultPos = 90; //Starting position of the servo
  int const ServoNicePourPos = 180; //Position to dump present
  int const ServoNaughtyPourPos = 0; //Position to dump coal
  int ServoPos = 90;

//LCD Variable Setup
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
  pinMode(MotorPin, OUTPUT); //Assigns Pin for the drive motor
//Front Spotlight Setup
  pinMode(Spotlight, OUTPUT); //Assigns pin for the LED Front light
//LCD Screen Setup
  
//Servo Setup
  PresentServo.attach(PresentServoPin); //Assigns pin for the "Nice" Servo
  PresentServo.write(ServoDefaultPos); //Sets servo to starting position

}
void loop() // put your main code here, to run repeatedly:
{
  int FlameValue = analogRead(FlameSensorPin); //Equates variable "FlameValue" to the data read by flame sensor
  unsigned long IRValue = irrecv.decode(&results);
//Turn on flame if higher than threshold
  if (FlameValue > FlameThreshold) //Do if the flame value is greater than its threshold
  {
    bool FlameOn = true; //Write FlameOn as true
  }
  else //Do if the flame value is less than its threshold
  {
    bool FlameOn = false; //Write FlameOn as false
  }
  
  while (FlameOn == true) //Runs while the flame is lit
  {
    //display Merry Christmas
    digitalWrite(Spotlight, HIGH); //Turn on the spotlight while flame is lit
    /*if(irrecv.decode(&results)) //Not sure if necessary*************************************************/
    if (IRValue == PowerButtonHex) //Do if power button is pressed
    {
      bool TrainRun = !TrainRun; //Toggle train as on/off
    }
    while (TrainRun == true) //Do while train was turned "on" and the flame is lit
    {
      //Display Merry Christmas and HO HO HO, alternating and scrolling
      if(irrecv.decode(&results))
      {
        switch (IRValue) //Use the remote to run different codes
        {
          case NaughtyButtonHex: //Press __ button to run scenario
            analogWrite(MotorPin, TrainRunStop); //fill out action          //display naughty on LCD, blinking, and run servo naughty to drop black "coal"
            for (; ServoPos <= ServoNaughtyPourPos; ServoPos = ServoPos + 1)
            {
              analogWrite(PresentServoPin, ServoPos);
              delay(20);
            }
            delay(1000);
            for (; ServoPos >= ServoDefaultPos; ServoPos = ServoPos - 1)
            {
              analogWrite(PresentServoPin, ServoPos);
              delay(20);
            }
            delay(1000);
            analogWrite(MotorPin, TrainRunSpeed);
            //display naughty on LCD, blinking, and run servo naughty to drop black "coal"
            break; //ends case statement if case 1 is run
          case NiceButtonHex: //Press __ button to run scenario
            analogWrite(MotorPin, TrainRunStop);
            for (; ServoPos >= ServoNicePourPos; ServoPos = ServoPos - 1)
            {
            analogWrite(PresentServoPin, ServoPos);
            delay(20);
            }
            delay(1000);
            for (; ServoPos <= ServoDefaultPos; ServoPos = ServoPos + 1)
            {
            analogWrite(PresentServoPin, ServoPos);
            delay(20);
            }
            delay(1000);
            analogWrite(MotorPin, TrainRunSpeed);
            //display nice on LCD, and run servo nice to drop colorful present
            break; //ends case statement if case 2 is run
         default: //default action if neither case 1 nor case 2 happens
            break; //ends code if default code runs
        }
        irrecv.resume();
      }
    }
  }
}
