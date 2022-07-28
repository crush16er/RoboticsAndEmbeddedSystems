#include "TimerOne.h"
#define BEEPER 13
#include "PinChangeInterrupt.h"
#include <Servo.h>
#include "IRremote.h"
int input_pin = 2; // wpisujemy nazwę pinu, po którym nastepuje komunikacja
IRrecv irrecv(input_pin);
decode_results signals;

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

long int intPeriod = 500000;

#define E1 11
#define E2 5
#define I1 7
#define I2 8
#define I3 6
#define I4 9

volatile char cmd = 'w';
int t = 1000;
volatile int carSpeed = 75;

void setup() {
    Serial.begin(9600);

    pinMode(4, OUTPUT);
    digitalWrite(4, HIGH);
    
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

    Serial.println("forward255");
    moveForward();
    delay(1000);
    Serial.println("backward0");
    carSpeed = 0;
    backward();
    delay(1000);
    Serial.println("backward254");
    carSpeed = 60;
    backward();
    delay(1000);
    carSpeed = 0;
    moveForward();

    /* rozejrzyj się w zakresie od 0 stopni (patrz na jedną burtę)
     *  do 180 stopni (patrz na prawą burtę). Wydrukuj na konsoli
     *  kierunek patrzenia i najbliżej widziany obiekt (pojedynczy pomiar)
     */
    /*for(byte angle = 0; angle < 180; angle+= 20)
    {
       lookAndTellDistance(angle);
       delay(100);
    }*/
  
    /* patrz przed siebie */
    //serwo.write(79);


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
    
    irrecv.enableIRIn(); // włączenie odbierania danych
}
 
void loop()
{
  if (irrecv.decode(&signals)) {
        Serial.println(signals.decode_type); // typ nadajnika
        Serial.print(F("wynik = 0x"));
        Serial.println(signals.value); // wynik w systemie szesnatkowym
        Serial.println(signals.bits); // ilość przesłanych danych
        irrecv.blink13(true); // mrugamy diodami w arduino
        
        // Przykładowe porównanie:
        
        if (signals.value == 16753245 || signals.value == 1033561079)
        {
          Serial.println("Wcisnieto klawisz 1");
          carSpeed -=25;
          updateSpeed(1, 2);
          Serial.println("ffff");
          Serial.println(analogRead(10));
          Serial.println(analogRead(5));
        }
        else if (signals.value == 16736925)
        {
          Serial.println("Wcisnieto klawisz 2");
          if(carSpeed + 25 <=255)
          {
            carSpeed +=25;
            updateSpeed(1, 2);
          }
          
          Serial.println("gggg");
          Serial.println(analogRead(10));
          Serial.println(analogRead(5));
          
        }
        else if(signals.value == 16718055)
        {
          //forward();
          Serial.println("Wcisnieto strzalke w przod");
        }
        else if(signals.value == 16730805)
        {
          backward();
        }
        else if(signals.value == 16716015)
        {
          turnLeft();
          Serial.println("Wcisnieto strzalke w lewo");
        }
        else if(signals.value == 16734885)
        {
          turnRight();
          Serial.println("Wcisnieto strzalke w prawo");
        }
        else if(signals.value == 1217346747 || signals.value == 16726215)
        {
          stopCar();
          Serial.println("Wcisnieto klawisz ok");
        }
        
        //4294967295
        // ... i tak dalej
        
        irrecv.resume(); // nasłuchujemy na następne nadanie     
    }
 /* while(Serial.available())
  {
    cmd = Serial.read();
    switch(cmd)
    {
      case 'w': forward(); break;
      case 'y': x = 1; break;
      case 's': backward(); break;
      case 'p': stopCar(); break;
      case 'a': turnLeft(); break;
      case 'd': turnRight(); break;
      case '+' : carSpeed += 25; updateSpeed(carSpeed, 1); break;
      case '-' : carSpeed -= 25; updateSpeed(carSpeed, 2); break;
    }
    Serial.println(intPeriod);
    Serial.print(cnt0);
    Serial.print(" ");
    Serial.println(cnt1);
  }


  if(x == 1)
  {
    forward();
    x = 0;
    y = 1;
    cnt0 = 0;
    cnt1 = 1;
  }

  if(y == 1)
  {
    if(cnt0 >= 60 || cnt1 >= 60)
    {
      stopCar();
      y = 0;
      cnt0 = 0;
      cnt1 = 1;
    }
  }*/

  
  
  /*Serial.print(cnt0);
  Serial.print(" ");
  Serial.println(cnt1);
  delay(500);*/

  
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


void moveForward()
{
  doNotBeep();
  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
  digitalWrite(I4, HIGH);
  analogWrite(E1, carSpeed);
  analogWrite(E2, carSpeed);
}

void backward()
{
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
  analogWrite(E1, carSpeed);
  analogWrite(E2, carSpeed);
  Timer1.start();
  doBeep();
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
  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
  analogWrite(E1, carSpeed);
  analogWrite(E2, 0);
}

void turnRight()
{
  doNotBeep();
  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
  analogWrite(E1, 0);
  analogWrite(E2, carSpeed);
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
