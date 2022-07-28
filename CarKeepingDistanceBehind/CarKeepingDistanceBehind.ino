#include "TimerOne.h"
#define BEEPER 13
#include "PinChangeInterrupt.h"
#include <Servo.h>

// piny dla sonaru (HC-SR04)
#define TRIG A4
#define ECHO A5

// pin kontroli serwo (musi być PWM)
#define SERVO 3

Servo serwo;


#define INTINPUT0 A0
#define INTINPUT1 A1

volatile int cnt0, cnt1;
volatile int x = 0;
volatile int y = 0;
volatile int dist = 0;

long int intPeriod = 500000;

#define E1 10
#define E2 9
#define I1 8
#define I2 7
#define I3 6
#define I4 5

volatile char cmd = 'w';
int t = 1000;
volatile int carSpeed = 255;

void setup() {
    Serial.begin(9600);
    
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
 
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);

    analogWrite(E1, 0);
    analogWrite(E2, 0);

    pinMode(TRIG, OUTPUT);    // TRIG startuje sonar
    pinMode(ECHO, INPUT);     // ECHO odbiera powracający impuls


    serwo.attach(SERVO);

    /* rozejrzyj się w zakresie od 0 stopni (patrz na jedną burtę)
     *  do 180 stopni (patrz na prawą burtę). Wydrukuj na konsoli
     *  kierunek patrzenia i najbliżej widziany obiekt (pojedynczy pomiar)
     */
    for(byte angle = 0; angle < 100; angle+= 10)
    {
       lookAndTellDistance(angle);
       delay(100);
    }
  
    /* patrz przed siebie */
    //lookAndTellDistance(79);
    


    pinMode(BEEPER, OUTPUT);
    Timer1.initialize();
    TimerUpdate();
    doNotBeep();

    pinMode(INTINPUT0, INPUT);
    pinMode(INTINPUT1, INPUT);
  
    cnt0=0;
    cnt1=0;
  
    PCICR  = 0x02;  // włącz pin change interrupt dla 1 grupy (A0..A5)
    PCMSK1 = 0x03;  // włącz przerwanie dla A0, A1
    forward();
}
 
void loop()
{
  dist = lookAndTellDistance(79);
  
  if(dist > 105)
  {
    forward();
    /*if(dist > 200)
    {*/
      analogWrite(E1, 150);
      analogWrite(E2, 150);
      
    /*}
    else
    {
      analogWrite(E1, 255-(200-dist));
      analogWrite(E2, 255-(200-dist));
    }*/

    
  }
  if(dist <= 105 && dist >= 95)
  {
    analogWrite(E1, 0);
    analogWrite(E2, 0);
  }
  if(dist < 95)
  {
    backward();
    analogWrite(E1, 255);
    analogWrite(E2, 255);
  }
      
}


ISR(PCINT1_vect){
 if( (PINC & (1 << PC0)) ) 
 cnt0++;

 if( (PINC & (1 << PC1)) )
 cnt1++;
}

void updateSpeed(int s, int p)
{
  analogWrite(E1, carSpeed);
  analogWrite(E2, carSpeed); 

  if(p == 1)
  {
    intPeriod += 100000;
  }
  else
  {
    intPeriod -= 100000;
  }
}


void forward()
{
  doNotBeep();
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
  analogWrite(E1, carSpeed);
  analogWrite(E2, carSpeed);
}

void forwardRange()
{
  doNotBeep();
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
  analogWrite(E1, carSpeed);
  analogWrite(E2, carSpeed);
  
}

void turnLeft()
{
  doNotBeep();
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);
  digitalWrite(I3, LOW);
  digitalWrite(I4, HIGH);
  analogWrite(E1, carSpeed*1.5);
  analogWrite(E2, 0);
}

void turnRight()
{
  doNotBeep();
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
  analogWrite(E1, 0);
  analogWrite(E2, carSpeed*1.5);
}

void backward()
{
  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
  digitalWrite(I4, HIGH);
  analogWrite(E1, carSpeed);
  analogWrite(E2, carSpeed);
  Timer1.start();
  doBeep();
}

void stopCar()
{
  doNotBeep();
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}

void TimerUpdate() {
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(doBeep, intPeriod);
}

void doBeep() {
  digitalWrite(BEEPER, digitalRead(BEEPER) ^ 1);
}

void doNotBeep() {
  digitalWrite(BEEPER, LOW);
  Timer1.stop();
}

int lookAndTellDistance(byte angle) {
  
  unsigned long tot;      // czas powrotu (time-of-travel)
  unsigned int distance;

  Serial.print("Patrzę w kącie ");
  Serial.print(angle);
  serwo.write(angle);
  
/* uruchamia sonar (puls 10 ms na `TRIGGER')
 * oczekuje na powrotny sygnał i aktualizuje
 */
  digitalWrite(TRIG, HIGH);
  delay(10);
  digitalWrite(TRIG, LOW);
  tot = pulseIn(ECHO, HIGH);

/* prędkość dźwięku = 340m/s => 1 cm w 29 mikrosekund
 * droga tam i z powrotem, zatem:
 */
  distance = tot/58;

  Serial.print(": widzę coś w odległości ");
  Serial.println(distance);

  return distance;
}
