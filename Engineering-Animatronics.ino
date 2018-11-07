/*Animatronic Master Code
  Holiday Themed PreCode Testing
*/
int const FlameSensorPin = 0; //ANALOG //Add a pin slot //Declare Flame Sensor Pin
//int const (Sensor)SensorPin = 0; //Present sensor (pressure, proximity, light?)
int const LEDFrontPin = 0; //Declare pin slot for front LED
int const LEDBackPin = 0; //Declare pin slot for back car LED
int const MotorPin = 0; //Declare pin slot for
int FlameThreshold = 100;//Declare threshold for flame considered on
int FlameValue = 0; //Declare value of flame, later used to determine on or off
int FlameOn = 0; //Declare flame on or off
//Only use if present sensor is analog int PresentThreshold =100; //Declare threshold for presents in car
//Only use if present sensor is analog int PresentValue = 0; //Declare value of presents in
int PresentIn = 0; //Declare presents in or out

void setup() // put your setup code here, to run once:
{ 
pinMode(FlameSensorPin, INPUT);
pinMode(/*Present Sensor Pin*/, INPUT);
pinMode(LEDFrontPin, OUTPUT);
pinMode(LEDBackPin, OUTPUT);
pinMode(MotorPin, OUTPUT);
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
  if(FlameSensorPin > FlameThreshold)
  {
      int FlameOn = 1;
  }
  else
  {
      int FlameOn = 0;
  }
  
  
}
