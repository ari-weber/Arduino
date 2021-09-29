#include <Servo.h>

#define joyX A0
#define joyY A1

#define potPin A2

const int SWPin  = 4;        //Switch not working
const int buttonPin = 2;     // the number of the pushbutton pin

Servo xServo;
Servo yServo;

int potVal = 0;
int xValue, yValue, xMap, yMap;
int RANGE;
int buttonState = 0;         // variable for reading the pushbutton status
int SW = 0;

void setup() {
  Serial.begin(9600);
  xServo.attach(11);
  yServo.attach(9);
  pinMode(buttonPin, INPUT);
  pinMode(SWPin, INPUT);
  RANGE = 1;
}

void loop(){
  buttonState = digitalRead(buttonPin);
  SW = digitalRead(SWPin);
  potVal = analogRead(potPin);
  RANGE = map(potVal, 0, 1000, 10, 100);
  if(SW == HIGH){
    JoystickLoop();
  }else{
   RandLoop(); 
  }
}
 
void RandLoop() {
  // put your main code here, to run repeatedly:

  int xValue = random(0, 1000);
  int yValue = random(0, 1000);
  
  //print the values with to plot or view
  Serial.print(xValue);
  Serial.print("\t");
  Serial.println(yValue);
 
  xMap = map(xValue, 0,1000, (90 - RANGE), (90 + RANGE));
  xServo.write(xMap);
  yMap = map(yValue, 0,1000, (90 - RANGE), (90 + RANGE));
  yServo.write(yMap);

  delay(random(100, 600));
}

void JoystickLoop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  SW = digitalRead(SWPin);
 
  //print the values with to plot or view
  Serial.print(xValue);
  Serial.print("\t");
  Serial.print(yValue);
  Serial.print("\tSW = ");
  Serial.println(SW);
 
  xMap = map(xValue, 0,1023, (90 - RANGE), (90 + RANGE));
  xServo.write(xMap);
  yMap = map(yValue, 0,1023, (90 - RANGE), (90 + RANGE));
  yServo.write(yMap);

  delay(100);
}
