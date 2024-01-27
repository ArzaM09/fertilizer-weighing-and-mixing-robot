#define BLYNK_TEMPLATE_ID "TMPL6OlEyzbHx"
#define BLYNK_TEMPLATE_NAME "robotpengaduk"
#define BLYNK_AUTH_TOKEN "EYsiFeMePb5ai5P87Z52C9sOhG3lzAUj"
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
char ssid[] = "Ahmadd";
char pass[] = "12345678";
#define EspSerial Serial
#define ESP8266_BAUD 9600
#include <Arduino.h>
#include "HX711.h"
const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;
HX711 scale;
ESP8266 wifi(&EspSerial);
int ena1 = 9;
int enb1 = 10;
int in1 = 2;
int in2 = 4;
int in3 = 7;
int in4 = 8;
int enb2 = 11;
int ena2 = A0;
int in5 = A1;
int in6 = A2;
int in7 = A3;
int in8 = A4;
int speed = 255;
bool maju = 0;
bool mundur = 0;
bool kiri = 0;
bool kanan = 0;
#include<Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
BlynkTimer timer;
bool servoMoving = false;
float timbangan;

void sensor()
{

}

void setup() {
  // put your setup code here, to run once:
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);
  Serial.begin(9600);
  pinMode(ena1, OUTPUT);
  pinMode(enb1, OUTPUT);
  pinMode(enb2, OUTPUT);
  pinMode(ena2, OUTPUT);
  pinMode(in1 , OUTPUT);
  pinMode(in2 , OUTPUT);
  pinMode(in3 , OUTPUT);
  pinMode(in4 , OUTPUT);
  pinMode(in5 , OUTPUT);
  pinMode(in6 , OUTPUT);
  pinMode(in7 , OUTPUT);
  pinMode(in8 , OUTPUT);
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  scale.set_scale(-459.542);
  scale.tare();
  
}
void loop() {
  Blynk.run();
  gerak();
  timbangan = scale.get_units(10);
  Serial.println(timbangan);
  Blynk.virtualWrite(V1, timbangan);
  if (servoMoving) {
    servo3.write(0);
    delay(500);
    servo3.write(180);
    delay(500);
  }
}
BLYNK_WRITE(V5) {
  int ser1 = param.asInt();  // Membaca karakter dari Blynk
  servo1.write(ser1);
}
BLYNK_WRITE(V6) {
  int ser2 = param.asInt();  // Membaca karakter dari Blynk
  servo2.write(ser2);
}
BLYNK_WRITE(V7) {
  int ser3 = param.asInt();  // Membaca karakter dari Blynk
  if (ser3 == 1) {
    servoMoving = true;
  } else {
    servoMoving = false;
  }
}
// BLYNK_WRITE(V8) {
//   speed = param.asInt();  // Membaca karakter dari Blynk
// }
BLYNK_WRITE(V0) {
  maju= param.asInt();  // Membaca karakter dari Blynk
}
BLYNK_WRITE(V4) {
  mundur= param.asInt();  // Membaca karakter dari Blynk
}
BLYNK_WRITE(V3) {
  kanan= param.asInt();  // Membaca karakter dari Blynk
}
BLYNK_WRITE(V2) {
  kiri= param.asInt();  // Membaca karakter dari Blynk
}
void gerak() {
  if (maju == 1) {
    forward();
  } else if (mundur == 1) {
    backward();
    Serial.println("Backward");
  } else if (kiri == 1) {
    left();
    Serial.println("Left");
  } else if (kanan == 1) {
    right();
    Serial.println("Right");
  } else if (maju == 0 && mundur == 0 && kiri == 0 && kanan == 0) {
    stop();
    Serial.println("Stop");
  }
}
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
  analogWrite(ena1, speed);
  analogWrite(enb1, speed);
  analogWrite(enb2, speed);
  analogWrite(ena2, speed);
}
void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
  analogWrite(ena1, speed);
  analogWrite(enb1, speed);
  analogWrite(enb2, speed);
  analogWrite(ena2, speed);
}
void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
  analogWrite(ena1, speed);
  analogWrite(enb1, speed);
  analogWrite(enb2, speed);
  analogWrite(ena2, speed);
}
void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
  analogWrite(ena1, speed);
  analogWrite(enb1, speed);
  analogWrite(enb2, speed);
  analogWrite(ena2, speed);

}
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}

