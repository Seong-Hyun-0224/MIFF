//we need to modify a step motors "STEPS" in a real situation. Set a sink of step motors speed.
//#include <Stepper.h>
//#define STEPS 2037    //one circle's step = 2037.
//Stepper stepper1(STEPS, 22, 23, 24, 25); //***********************************
//Stepper stepper2(STEPS, 26, 27, 28, 29); //***********************************
//Stepper stepper3(STEPS, 30, 31, 32, 33); //***********************************

const int stepPin1 = 22;
const int dirPin1 = 23;

const int stepPin2 = 24;
const int dirPin2 = 25;

const int stepPin3 = 26;
const int dirPin3 = 27;

int stopbutton = 10;    //이 밑으로는 버튼 변수들
int onAndoff = 9;

int dooropen3 = 8;
int dooropen2 = 7;
int dooropen1 = 6;

int doorclose3 = 20;
int doorclose2 = 19;
int doorclose1 = 18;

int relayMotor3 = 5;
int relayMotor2 = 4;
int relayMotor1 = 3;
int relayPower = 2;

unsigned long buzzerPreMillis = 0;

void setup() {
  Serial.begin(9600);
  //stepper1.setSpeed(12);                 //rotate speed designate.
  //stepper2.setSpeed(12);                 //rotate speed designate.
  //stepper3.setSpeed(12);                 //rotate speed designate.

  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);

  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);

  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  
  pinMode(stopbutton, INPUT_PULLUP);
  pinMode(onAndoff, INPUT_PULLUP);
  
  pinMode(dooropen1, INPUT_PULLUP);
  pinMode(dooropen2, INPUT_PULLUP);
  pinMode(dooropen3, INPUT_PULLUP);
  attachInterrupt(5,doorstop1,CHANGE);
  attachInterrupt(4,doorstop2,CHANGE);
  attachInterrupt(3,doorstop3,CHANGE);
  
  pinMode(relayMotor3, OUTPUT);
  pinMode(relayMotor2, OUTPUT);
  pinMode(relayMotor1, OUTPUT);
  pinMode(relayPower, OUTPUT);

}

void loop() {
  static unsigned long curMillis = millis();      //static으로 전역/지역 둘 다 기능할 수 있게 했는데 왜 doorstop()함수에서 call이 안되는 거냐고 이런 개같은 ㅅㅂ

  if((digitalRead(doorclose1) == LOW) || (digitalRead(doorclose2) == LOW) || (digitalRead(doorclose3) == LOW)) {
    buzzerPreMillis = curMillis;
  }
  
  if (digitalRead(stopbutton) == LOW) //stop button part.
  {
    digitalWrite(relayMotor3, LOW);
    digitalWrite(relayMotor2, LOW);
    digitalWrite(relayMotor1, LOW);
    delay(5000);
  }

  if (digitalRead(onAndoff) == LOW)   //on & off button part.
  {
    digitalWrite(relayPower, HIGH);
    digitalWrite(relayMotor1, HIGH);
    digitalWrite(relayMotor2, HIGH);
    digitalWrite(relayMotor3, HIGH);
    delay(1000);
  }

//================================================================================
  if (digitalRead(dooropen1) == LOW)  //auto door open button part.
  {
    digitalWrite(relayMotor1, LOW);
    digitalWrite(relayMotor2, LOW);
    digitalWrite(relayMotor3, LOW);
    digitalWrite(dirPin1, HIGH);
    for(int x = 0; x < 400; x++) {
      digitalWrite(stepPin1, HIGH);
      delay(5);
      digitalWrite(stepPin1, LOW);
      delay(5);
    }
    //stepper1.step(STEPS);              //forward direction rotate.
  }
//================================================================================
  if (digitalRead(dooropen2) == LOW)  //auto door open button part.
  {
    digitalWrite(relayMotor1, LOW);
    digitalWrite(relayMotor2, LOW);
    digitalWrite(relayMotor3, LOW);
    digitalWrite(dirPin2, HIGH);
    for(int y = 0; y < 400; y++) {
      digitalWrite(stepPin2, HIGH);
      delay(5);
      digitalWrite(stepPin2, LOW);
      delay(5);
    }
    //stepper2.step(STEPS);              //forward direction rotate.
  }
//================================================================================
  if (digitalRead(dooropen3) == LOW)  //auto door open button part.
  {
    digitalWrite(relayMotor1, LOW);
    digitalWrite(relayMotor2, LOW);
    digitalWrite(relayMotor3, LOW);
    digitalWrite(dirPin3, HIGH);
    for(int z = 0; z < 400; z++) {
      digitalWrite(stepPin3, HIGH);
      delay(5);
      digitalWrite(stepPin3, LOW);
      delay(5);
    }
    //stepper3.step(STEPS);              //forward direction rotate.
  }
//=================================================================================

  if((buzzerPreMillis > 0) && (curMillis - buzzerPreMillis > 120000)) {
    buzzerPreMillis = curMillis;
    digitalWrite(relayMotor1, LOW);
    digitalWrite(relayMotor2, LOW);
    digitalWrite(relayMotor3, LOW);
  }
}

//************************************************************************************
void doorstop1() {
  //stepper1.step(-STEPS);              //reverse direction rotate.
  digitalWrite(dirPin1, LOW);

  for(int a = 0; a < 400; a++) {
    digitalWrite(stepPin1, HIGH);
    delay(5);
    digitalWrite(stepPin1, LOW);
    delay(5);
  }
  
  digitalWrite(relayMotor1, HIGH);
  digitalWrite(relayMotor2, HIGH);
  digitalWrite(relayMotor3, HIGH);
}
//*************************************************************************************
void doorstop2() {
  //stepper1.step(-STEPS);              //reverse direction rotate.
  digitalWrite(dirPin2, LOW);

  for(int a = 0; a < 400; a++) {
    digitalWrite(stepPin2, HIGH);
    delay(5);
    digitalWrite(stepPin2, LOW);
    delay(5);
  }
  
  digitalWrite(relayMotor1, HIGH);
  digitalWrite(relayMotor2, HIGH);
  digitalWrite(relayMotor3, HIGH);
}
//*************************************************************************************
void doorstop3() {
  //stepper1.step(-STEPS);              //reverse direction rotate.
  digitalWrite(dirPin3, LOW);

  for(int a = 0; a < 400; a++) {
    digitalWrite(stepPin3, HIGH);
    delay(5);
    digitalWrite(stepPin3, LOW);
    delay(5);
  }
  
  digitalWrite(relayMotor1, HIGH);
  digitalWrite(relayMotor2, HIGH);
  digitalWrite(relayMotor3, HIGH);
}
//*************************************************************************************
