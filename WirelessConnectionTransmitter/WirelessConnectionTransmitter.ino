#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


int OX1 = 0;
int OY1 = 1;
int OX2 = 2;
int OY2 = 3;

volatile int valX1 = 0;
volatile int valY1 = 0;
volatile int valX2 = 0;
volatile int valY2 = 0;

RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
boolean buttonState = 0;


void setup()
{
  //pinMode(12, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
   
  
  Serial.begin(9600);

}

void loop()
{
  delay(5);
  radio.stopListening();
  int potValue = analogRead(A0);
  int angleValue = map(potValue, 0, 1023, 0, 180);
  Serial.println(angleValue);
  radio.write(&angleValue, sizeof(angleValue));
  delay(5);
  /*radio.startListening();
  while (!radio.available());
  radio.read(&buttonState, sizeof(buttonState));*/
  /*if (buttonState == HIGH) {
    //digitalWrite(led, HIGH);
    Serial.println("HIGH");
  }
  else {
    //digitalWrite(led, LOW);
    
    Serial.println("LOW");
  }*/

  /*
  valX1 = analogRead(OX1);
  valY1 = analogRead(OY1);
  valX2 = analogRead(OX2);
  valY2 = analogRead(OY2);

  Serial.println(valX1);
  Serial.println(valY1);
  Serial.println(valX2);
  Serial.println(valY2);

  delay(2000);*/

}
