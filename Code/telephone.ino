#include<SoftwareSerial.h> 
#define RX 8
#define TX 9
//-- MOTEUR A --
int ENA=5; //Connecté à Arduino pin 9(sortie PWM) 
int IN1=2; //Connecté à Arduino pin 4
int IN2=3; //Connecté à Arduino pin 5

//-- MOTEUR B --
int ENB=6; //Connecté à Arduino pin 10(Sortie PWM) 
int IN3=4; //Connecté à Arduino pin 6
int IN4=7; //Connecté à Arduino pin 

char Data;
SoftwareSerial BlueT(RX,TX);
int vitA=0;
int vitB=0;

void setup() {
Serial.begin(9600); 
BlueT.begin(9600);
pinMode(ENA,OUTPUT); //configurer
pinMode(ENB,OUTPUT); //les broches
pinMode(IN1,OUTPUT); //comme sortie
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner 
digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner
// Direction du Moteur B
digitalWrite(IN3,HIGH); 
digitalWrite(IN4,LOW);
// Direction du Moteur A
digitalWrite(IN1,LOW); 
digitalWrite(IN2,HIGH);
}

void loop() {
if (BlueT.available()){
    Data=char(BlueT.read());
    Serial.println(char(Data));
    if (Data=='A') {
      Serial.println(Data);
      vitA=BlueT.parseInt();
      Serial.println(vitA);
      analogWrite(ENA,vitA);
    }
    if (Data=='B') {
      Serial.println(Data);
      vitB=BlueT.parseInt();
      Serial.println(vitB);
      analogWrite(ENB,vitB);
    }
    if (Data=='C') {
      digitalWrite(IN1,LOW); 
      digitalWrite(IN2,HIGH);
    }
    if (Data=='c') {
      digitalWrite(IN1,HIGH); 
      digitalWrite(IN2,LOW);
    }
    if (Data=='D') {
      digitalWrite(IN3,HIGH); 
      digitalWrite(IN4,LOW);
    }
    if (Data=='d') {
      digitalWrite(IN3,LOW); 
      digitalWrite(IN4,HIGH);
    }
}    
}
