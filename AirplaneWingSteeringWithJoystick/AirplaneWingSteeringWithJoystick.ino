#include <Servo.h>

volatile char cmd;
const int OX = 0;
volatile int val = 0;

volatile int val2 = 0;
Servo wingLeft; 
Servo wingRight;

void setup()
{
  Serial.begin(9600);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  wingLeft.attach(11);
  wingRight.attach(10);
}

void loop()
{
  val = analogRead(OX);
  Serial.println(val); // reads the value of the potentiometer (value between 0 and 1023)
  
  val2 = map(val, 0, 142, 40, 140);
  val = map(val, 0, 142, 40, 140);     // scale it to use it with the servo (value between 0 and 180)
  val2 = abs(180 - val2)-20;
  Serial.println(val);
  wingLeft.write(val);
  wingRight.write(val2);
  
  delay(10);
}
