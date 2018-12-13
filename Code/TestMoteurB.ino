//-- MOTEUR A --
int ENA=5; //Connecté à Arduino pin 9(sortie PWM) 
int IN1=2; //Connecté à Arduino pin 4
int IN2=3; //Connecté à Arduino pin 5

//-- MOTEUR B --
int ENB=6; //Connecté à Arduino pin 10(Sortie PWM) 
int IN3=4; //Connecté à Arduino pin 6
int IN4=7; //Connecté à Arduino pin 


void setup() {
pinMode(ENA,OUTPUT); //configurer
pinMode(ENB,OUTPUT); //les broches
pinMode(IN1,OUTPUT); //comme sortie
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner 
digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner
}

void loop() {
analogWrite(ENB,0);
// Direction du Moteur B
digitalWrite(IN3,HIGH); 
digitalWrite(IN4,LOW);
// Moteur B - Mi régime 
analogWrite(ENB,150);
}
