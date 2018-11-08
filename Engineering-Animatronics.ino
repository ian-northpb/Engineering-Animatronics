/*Animatronic Master Code
  Holiday Themed PreCode Testing
*/
int const FlameSensorPin = A0; //set pin //Declare Flame Sensor Pin
//int const (Sensor)SensorPin = 0; //set pin //Present sensor (pressure, proximity, light?)
int const LEDFrontPin = 0; //set pin //Declare pin slot for front LED
int const LEDBackPin = 0; //set pin //Declare pin slot for back car LED
int const MotorPin = A0; //set pin //Declare pin slot for motor
int const Spotlight = 0; //set pin //
int const FlameThreshold = 100; //figure out good threshold //Declare threshold for flame considered on
int FlameValue = 0; //Declare value of flame, later used to determine on or off
int FlameOn = 0; //Declare flame on or off
//Only use if present sensor is analog int const PresentThreshold = 100; //Declare threshold for presents in car
//Only use if present sensor is analog int PresentValue = 0; //Declare value of presents in
int PresentIn = 0; //Declare presents in or out

void setup() // put your setup code here, to run once:
{
  pinMode(FlameSensorPin, INPUT);
  //pinMode(/*Present Sensor Pin*/, INPUT);
  pinMode(LEDFrontPin, OUTPUT);
  pinMode(LEDBackPin, OUTPUT);
  pinMode(MotorPin, OUTPUT);
  //pinMode(Spotlight, OUTPUT);
}

void loop() // put your main code here, to run repeatedly:
{
  //  int PresentValue = analogRead(/*presentSensor*/);
  //  if(PresentValue > PresentThreshold)
  //  {
  //    int PresentIn = 1;
  //  }
  //  else
  //  {
  //    int PresentIn = 0;
  //  }
  int FlameValue = analogRead(FlameSensorPin);
  if (FlameSensorPin > FlameThreshold)
  {
    int FlameOn = 1;
  }
  else
  {
    int FlameOn = 0;
  }
  if (FlameOn == 1 && PresentIn == 0)
  {
    digitalWrite(LEDFrontPin, HIGH);
    digitalWrite(LEDBackPin, LOW);
    digitalWrite(Spotlight, LOW); //Turns off spotlight, maybe use spotlight?
    analogWrite(MotorPin, 0);
  }
  else if (FlameOn == 0 && PresentIn == 1)
  {
    digitalWrite(LEDFrontPin, LOW);
    digitalWrite(LEDBackPin, HIGH);
    digitalWrite(Spotlight, LOW); //Turns off spotlight, maybe use spotlight?
    analogWrite(MotorPin, 0);
  }
  else if (FlameOn == 1 && PresentIn == 1)
  {
    digitalWrite(LEDFrontPin, HIGH);
    digitalWrite(LEDBackPin, HIGH);
    digitalWrite(Spotlight, HIGH);
    analogWrite(MotorPin, 125);
  }
  else
  {
    digitalWrite(LEDFrontPin, LOW);
    digitalWrite(LEDBackPin, LOW);
    digitalWrite(Spotlight, LOW); //Turns off spotlight, maybe use spotlight?
    analogWrite(MotorPin, 0);
    
  }

}
