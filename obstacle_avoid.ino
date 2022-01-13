#include<Servo.h>
Servo myservo;
int pin = 2;
int rmf = 4;
int lmf = 8;
int rspeed = 5;
int lspeed = 6;
int rmb = 7;
int lmb = 3;
int trig = 10;
int ech1 = 11;
int val = 90;
int pin1;
int sten;
int flag;
int left;
int right;
bool block;
int motortime=1000;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(pin);
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(ech1, INPUT);
  pinMode(rmf, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rspeed, OUTPUT);
  pinMode(lspeed, OUTPUT);
  digitalWrite(rspeed, HIGH);
  digitalWrite(lspeed, HIGH);
}
void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(val);
  delay(250);
  pin1=ping();
  Serial.println(pin1);
  flag=1;
  forward();
  if (pin1 > 0 && pin1 < 800 && flag==1) {
    wait();
    right=lookright();
    left=lookleft();
    Serial.print(right);
    Serial.print(" :: ");
    Serial.println(left);
    sten=1;
    if(right>left && sten==1){
      myservo.write(val);
      pingstop();
      backup();
      turnright();
      sten=0;
      flag=0;
      }
    if(left>right && sten==1){
       myservo.write(val);
       pingstop();
       backup();
       turnleft();
       sten=0;
       flag=0;
      }
  }
  while (block) {
  }
}
int ping(){
  delay(125);
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  int pulse = pulseIn(ech1, HIGH);
  return pulse;
  
  }
int lookright(){
  myservo.write(0);
  delay(1000);
  int rdistance = ping();
  return rdistance;
  }
int lookleft(){
  myservo.write(180);
  delay(1000);
  int ldistance = ping();
  return ldistance;
  }
void forward(){
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb,LOW);
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb,LOW);
  }
void wait(){
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, LOW);
  }
void turnright(){
  digitalWrite(lmf, HIGH);
  digitalWrite(rmb, LOW);
  digitalWrite(rmf, LOW);
  digitalWrite(lmb, LOW);
  delay(motortime);
  wait();
  }
void turnleft(){
  digitalWrite(rmf, HIGH);
  digitalWrite(lmb, LOW);
  digitalWrite(rmb, LOW);
  digitalWrite(lmf, LOW);
  delay(motortime);
  wait();
  }
void pingstop(){
  digitalWrite(trig,LOW);
  }
  void backup(){
  digitalWrite(rmf, LOW);
  digitalWrite(rmb,HIGH);
  digitalWrite(lmf, LOW);
  digitalWrite(lmb,HIGH);
  delay(500);
    
    }
