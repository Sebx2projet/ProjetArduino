#include<NewPing.h> 
#include <SPI.h>  
#include <Pixy.h>
#include <Servo.h>

//-- SERVO MOTEURS --

Servo Servo1;
Servo Servo2;
Servo Servo3;


//-- MOTEUR A --
  int ENA=5; //Connecté à Arduino pin 5(sortie pwm)
  int IN1=2; //Connecté à Arduino pin 2
  int IN2=3; //Connecté à Arduino pin 3

//-- MOTEUR B --
  int ENB=6; //Connecté à Arduino pin 6(Sortie pwm)
  int IN3=4; //Connecté à Arduino pin 4
  int IN4=7; //Connecté à Arduino pin 7
  
// This is the main Pixy object 
Pixy pixy;

int MAX_DE_COUPS=20000;

  static int premiercoup=1;
  static int phase_detection=1;
  static int phase_alignement = 0;
  static int phase_rapprochement=0;
  static int phase_prehension = 0;
  static int nb_coup_sans_detection=0;
  
  uint16_t nb_blocks;
  char buf[32];

  
// controle du module ultra son 
NewPing sonar(14,15,500);
int d=0; 

void setup()
{

 pinMode(ENA,OUTPUT);//Configurer les broches comme sortie
 pinMode(ENB,OUTPUT);
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);


  Serial.begin(9600);
  // initialisation des servos
  Servo1.attach(17,544,2400);
  Servo2.attach(18,544,2400);
  Servo3.attach(19,544,2400);

  Servo2.write(180);
  delay(1000);
  Servo1.write(60);
  delay(1000);
  Servo3.write(73);
  delay(1000);
  
  // initialison pixy cam
  pixy.init();
}

void loop()
{
  int position_x;

  if (premiercoup) // permet d'initialiser la caméra, qui me un peu de temps à se synchroniser
  {
    delay(250);
    premiercoup=0;
  }
  
  // Pixy configuré pour ne détecter qu'un seul block pour une signature
  nb_blocks = pixy.getBlocks();
  position_x = pixy.blocks[0].x;
  
  //Serial.println(nb_blocks);
  if(phase_detection)
  {
    if(nb_blocks==0)
    { 
      //Serial.println(position_x);
      Serial.println("je recherche");
      // Aucun objet visible, on tourne un peu pour explorer la scène
     // Serial.println("Retour de recherche");     
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      analogWrite(ENB,0);
      analogWrite(ENA,200);
      delay(200);
        // on éteint les moteurs 
      analogWrite(ENA,0);
      analogWrite(ENB,0);
    }
    else //1ère fois que je détecte quelque chose
    {
      //Serial.println("Je detecte quelque chose");
      phase_detection = 0;
      // phase de detection terminée, l'objet est dans le champ de la caméra, on essaie de le mettre au centre de la scène
      phase_alignement = 1;
    }
  }
  else if (phase_alignement)  
  {
    if(nb_blocks > 0)
    {
      if (position_x < 140 && position_x > 0) // 160 correspond au milieu de la scène
      {
        // L'objet est à gauche de la caméra, il faut tourner à gauche
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        //Serial.println(position_x);
        Serial.println("je dois tourner à gauche");
        analogWrite(ENA,0);
        analogWrite(ENB,200);
        delay(200);
        // on éteint les moteurs 
        analogWrite(ENA,0);
        analogWrite(ENB,0);
      }
      else if (position_x > 180 && position_x < 319) // il faut tourner à droite
      {
         digitalWrite(IN1,LOW);
         digitalWrite(IN2,HIGH);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         //Serial.println(position_x);
         Serial.println("je dois tourner à droite");
         analogWrite(ENA,200);
         analogWrite(ENB,0);
         delay(200);
            // on éteint les moteurs 
         analogWrite(ENA,0);
         analogWrite(ENB,0);
      }
      else if (position_x<=180 && position_x>=140) // il ne faut plus tourner, il ne reste plus qu'à avancer vers l'objet
      { 
        phase_alignement = 0;
        phase_rapprochement = 1;
      }
    }
    else // aucun bloc détecté en phase de poursuite
    {
        nb_coup_sans_detection++;
        if(nb_coup_sans_detection == MAX_DE_COUPS)
        {
          // Objet perdu, il faut reprendre la recherche du début -> reinitialisation
          phase_detection = 1;
          nb_coup_sans_detection=0;
        }
     }    
  }
  else if(phase_rapprochement)
  {
    //Serial.println(d);
    d = 0;
    while(d > 20 || d == 0){
        // Avance tout droit
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        analogWrite(ENA,180);
        analogWrite(ENB,180);
        d = sonar.ping_cm();
        Serial.println("je dois avancer");
        Serial.println(d);
    }
    analogWrite(ENA,0);
    analogWrite(ENB,0);
    phase_rapprochement = 0;
    phase_prehension = 1;
  }
  else if (phase_prehension)
  {
      // TBD : commande de la pice
      Serial.println("je dois attraper l'objet");
      Servo3.write(20);
      delay(1500);
      Servo2.write(130);
      delay(1500);
      Servo3.write(70);
      delay(1500);
      Servo2.write(180);
      delay(100000);
  } 
}
