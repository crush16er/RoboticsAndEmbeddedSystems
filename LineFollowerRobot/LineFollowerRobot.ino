#define E1 11
#define E2 5
#define I1 7
#define I2 8
#define I3 6
#define I4 9
#define sensorLeftLong A0
#define sensorLeftShort A1
#define sensorMiddle A2
#define sensorRightShort A3
#define sensorRightLong A4


volatile int carSpeed = 60;
volatile int carSpeedLeft = carSpeed + 15;
volatile int carSpeedRight = carSpeed;
volatile int sLL = 0;
volatile int sSL = 0;
volatile int sM = 0;
volatile int sSR = 0;
volatile int sLR = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  analogWrite(E1, 0);
  analogWrite(E2, 0);
  
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);

  moveForward();
    
  delay(10000);
}

void loop()
{
  sLL = leftLongSensor();
  sSL = leftShortSensor();
  sM = middleSensor();
  sSR = rightShortSensor();
  sLR = rightLongSensor();


  if(sLL == 0 && sSL == 0 && sM == 1 && sSR == 0 && sLR == 0)
  {
    stopMotors();
    leftMotor(carSpeedLeft);
    rightMotor(carSpeedRight);
  }
  else if(sLL == 0 && sSL == 1 && sM == 0 && sSR == 0 && sLR == 0)
  {
    stopMotors();
    leftMotor(carSpeedLeft + 15);
    rightMotor(carSpeedRight);
  }
  else if(sLL == 0 && sSL == 0 && sM == 0 && sSR == 1 && sLR == 0)
  {
    stopMotors();
    leftMotor(carSpeedLeft);
    rightMotor(carSpeedRight + 15);
  }
  else if(sLL == 0 && sSL == 1 && sM == 1 && sSR == 0 && sLR == 0)
  {
    stopMotors();
    leftMotor(carSpeedLeft + 15);
    rightMotor(carSpeedRight);
  }
  else if(sLL == 0 && sSL == 0 && sM == 1 && sSR == 1 && sLR == 0)
  {
    stopMotors();
    leftMotor(carSpeedLeft);
    rightMotor(carSpeedRight + 15);
  }
  else if(sLL == 1 && sSL == 1 && sM == 0 && sSR == 0 && sLR == 0)
  {
    stopMotors();
    leftMotor(carSpeedLeft);
    rightMotor(carSpeedRight - 10);
  }
  else if(sLL == 0 && sSL == 0 && sM == 0 && sSR == 1 && sLR == 1)
  {
    stopMotors();
    leftMotor(carSpeedLeft - 10);
    rightMotor(carSpeedRight);
  }
  else if(sLL == 1 && sSL == 0 && sM == 0 && sSR == 0 && sLR == 0)
  {
    stopMotors();
    leftMotor(carSpeedLeft);
    rightMotor(0);
  }
  else if(sLL == 0 && sSL == 0 && sM == 0 && sSR == 0 && sLR == 1)
  {
    stopMotors();
    leftMotor(0);
    rightMotor(carSpeedRight);
  }
}

boolean leftLongSensor()
{
  if (analogRead(sensorLeftLong) < 100)
  {
    return 1;
  }
  else
  {
    return 0;
  } 
}

boolean leftShortSensor()
{
  if (analogRead(sensorLeftShort) < 100)
  {
    return 1;
  }
  else
  {
    return 0;
  } 
}

boolean middleSensor()
{
  if (analogRead(sensorMiddle) < 100)
  {
    return 1;
  }
  else
  {
    return 0;
  } 
}

boolean rightShortSensor()
{
  if (analogRead(sensorRightShort) < 100)
  {
    return 1;
  }
  else
  {
    return 0;
  } 
}

boolean rightLongSensor()
{
  if (analogRead(sensorRightLong) < 100)
  {
    return 1;
  }
  else
  {
    return 0;
  } 
}


void leftMotor(int V)
{
  analogWrite(E2, V);
}

void rightMotor(int V)
{
  analogWrite(E1, V);
}

void moveForward()
{
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
}

void stopMotors()
{
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}
