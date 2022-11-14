#include <LiquidCrystal.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>


#define DHTTYPE DHT11 // 습도센서 종류: DHT11
#define DHTPIN 2 // 습도센서 Signal 선 연결
#define BUTTON1 3 //button1 Signal 선 연결
#define BUTTON2 4 //button2 Signal 선 연결
#define RELAY 5   //릴레이 Signal 선 연결
#define buzzerPin 9 //부저 Signal 선 연결


DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 16, 2); // LCD주소: 0x27 또는 0x3F , UNO:SCL->A5 SDA->A4
virtuabotixRTC myRTC(6, 7, 8); //시계모듈 핀6,7,8


float hum; // 습도값 저장 변수
float temp; // 온도값 저장 변수
int ONTIME = 9; //점등시간
int OFFTIME = 18; //소등시간

void setup() {
  Serial.begin(9600);
  Serial.print("1");
  pinMode(RELAY, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  dht.begin();
  delay(500);
  Serial.print("1");
  lcd.init();
  Serial.print("1");
  lcd.backlight();
  Serial.print("1");
  lcd.setCursor(2, 0);
  delay(500);
  lcd.clear();
  Serial.print("1");
  //myRTC.setDS1302Time(50, 2, 19, 2, 15, 9, 2020); // 초,분,시, 요일, 일,월,년 순서입니다.

}

void loop() {
  myRTC.updateTime();
  hum = dht.readHumidity();//온도값 읽기
  temp = dht.readTemperature(); //습도값 읽기

  //시간에 따른 UVB램프 릴레이제어
  if (digitalRead(BUTTON1) == LOW)
    ONTIME += 1;
  if (ONTIME >= 24)
  {
    ONTIME = 0;
  }
  
  if (digitalRead(BUTTON2) == LOW)
    OFFTIME += 1;
  if (OFFTIME >= 24)
  {
    OFFTIME = 0;
  }

  if (myRTC.hours >= ONTIME && myRTC.hours <= OFFTIME)
  {
    digitalWrite(RELAY, HIGH);
  } else {
    digitalWrite(RELAY, LOW);
  }


  //lcd 출력 부분
  lcd.setCursor(0, 0); // LCD Cursor 원점
  lcd.print("T:"); // LCD에 "temp" 표시
  float t = temp; // 온도값을 t에 할당
  lcd.print(t, 1); // 온도값 LCD로 출력
  lcd.print("C "); // 온도 단위 표시
  lcd.print("H:"); //LCD 2번째 줄에 "humidity:" 출력
  int h = hum; //습도값 h에 할당
  lcd.print(h); //습도값 LCD에 출력
  lcd.print("%"); //습도 단위 출력

  lcd.setCursor(0, 1); //LCD 커서 줄바꿈
  lcd.print("ON:");
  lcd.print(ONTIME);
  lcd.print(" OFF:");
  lcd.print(OFFTIME);
  lcd.print("\n");

  delay(1000); // 샘플링 간격 1초

  Serial.print("HUMIDITY: "); // "HUMIDITY:" 출력
  Serial.print(hum, 0); // 습도 값 소수점 이하 자리 없음
  Serial.print(" %, TEMPERATURE: "); //"%"(습도단위) "TEMPERATURE:" 출력
  Serial.print(temp, 1);//온도값은 소수점 이하 1자리까지 표시
  Serial.println("ºC"); //"ºC" 온도 단위 표시
  Serial.print(myRTC.year);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.dayofmonth);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(" ");
  Serial.print(myRTC.seconds);
  Serial.println(".");
  //부저제어
  if ( (t < 26) || (t > 28) ) { //온도에 따른 부저음 변화
    tone(buzzerPin, 261.6, 1000);
    tone(buzzerPin, 329.7, 2000);
    tone(buzzerPin, 392.4, 1000);
    delay(100);
    noTone(7);
  }

  if ( (h < 46) || (h > 70) ) { //습도에 따른 부저음 변화
    tone(buzzerPin, 400, 1000);
    tone(buzzerPin, 500, 2000);
    tone(buzzerPin, 600, 1000);
    delay(100);
    noTone(7);
  }
}
