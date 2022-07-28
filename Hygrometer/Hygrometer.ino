#define A0  A0

void setup() {
  
pinMode(A0, INPUT);
Serial.begin(9600);

}

void loop() {
  Serial.println(1023-analogRead(A0));
  delay(10);

}
