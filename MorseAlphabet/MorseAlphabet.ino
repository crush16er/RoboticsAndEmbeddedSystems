#define LED 13

volatile char serialInput;
int delayFast;
int delaySlow;


void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  delayFast = 100;
  delaySlow = 3*delayFast;
}


void loop()
{
  while(Serial.available())
  {
    serialInput = Serial.read();
    switch(serialInput)
    {
      case 'a' : Serial.println(serialInput);
                  doFastBlink(1);
                  doSlowBlink(1);
                  break;
      case 'b' : Serial.println(serialInput);
                  doSlowBlink(1);
                  doFastBlink(3);
                  break;
      case 'c' : Serial.println(serialInput);
                  doSlowBlink(1);
                  doFastBlink(1);
                  doSlowBlink(1);
                  doFastBlink(1);
                  break;
      case 'd' : Serial.println(serialInput);
                  doSlowBlink(1);
                  doFastBlink(1);
                  doFastBlink(1);
                  break;
      case 'e' : Serial.println(serialInput);
                  doFastBlink(1);
                  break;
      case 'f' : Serial.println(serialInput);
                  doFastBlink(2);
                  doSlowBlink(1);
                  doFastBlink(1);
                  break;
      case 'g' : Serial.println(serialInput);
                  doSlowBlink(2);
                  doFastBlink(1);
                  break;
      case 'h' : Serial.println(serialInput);
                  doFastBlink(4);
                  break;
      case 'i' : Serial.println(serialInput);
                  doFastBlink(2);
                  break;
      case 'j' : Serial.println(serialInput);
                  doFastBlink(1);
                  doSlowBlink(3);
                  break;
      case 'k' : Serial.println(serialInput);
                  doSlowBlink(1);
                  doFastBlink(1);
                  doSlowBlink(1);
                  break;
      case 'l' : Serial.println(serialInput);
                  doFastBlink(1);
                  doSlowBlink(1);
                  doFastBlink(2);
                  break;
      case 'm' : Serial.println(serialInput);
                  doSlowBlink(2);
                  break;
      case 'n' : Serial.println(serialInput);
                  doSlowBlink(1);
                  doFastBlink(1);
                  break;
      case 'o' : Serial.println(serialInput);
                  doSlowBlink(3);
                  break;
      case 'p' : Serial.println(serialInput);
                  doFastBlink(1);
                  doSlowBlink(2);
                  doFastBlink(1);
                  break;
      case 'q' : Serial.println(serialInput);
                  doSlowBlink(2);
                  doFastBlink(1);
                  doSlowBlink(1);
                  break;
      case 'r' : Serial.println(serialInput);
                  doFastBlink(1);
                  doSlowBlink(1);
                  doFastBlink(1);
                  break;
      case 's' : Serial.println(serialInput);
                  doFastBlink(3);
                  break;
      case 't' : Serial.println(serialInput);
                  doSlowBlink(1);
                  break;
      case 'u' : Serial.println(serialInput);
                  doFastBlink(2);
                  doSlowBlink(1);
                  break;
      case 'v' : Serial.println(serialInput);
                  doFastBlink(3);
                  doSlowBlink(1);
                  break;
      case 'w' : Serial.println(serialInput);
                  doFastBlink(1);
                  doSlowBlink(2);
                  break;
      case 'x' : Serial.println(serialInput);
                  doSlowBlink(1);
                  doFastBlink(2);
                  doSlowBlink(1);
                  break;
      case 'y' : Serial.println(serialInput);
                  doSlowBlink(1);
                  doFastBlink(1);
                  doSlowBlink(2);
                  break;
      case 'z' : Serial.println(serialInput);
                  doSlowBlink(2);
                  doFastBlink(2);
                  break;
                  
      default  : Serial.println("Error: symbol out of alphabet.");
    }
  }
  Serial.println(" - ");
}


void doSlowBlink(int n)
{
  for(int i=0; i<n; i++)
  {
    digitalWrite(LED, HIGH);
    delay(delaySlow);
    digitalWrite(LED, LOW);    
    delay(delaySlow);
  }  
}

void doFastBlink(int n)
{
  for(int i=0; i<n; i++)
  {
    digitalWrite(LED, HIGH);
    delay(delayFast);
    digitalWrite(LED, LOW);    
    delay(delaySlow);
  }  
}
