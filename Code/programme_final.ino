#include <SPI.h>  
#include <Pixy.h>
#include <Servo.h>
#include<SoftwareSerial.h> 

// module bluetooth
#define RX 8
#define TX 9
#define sensor A0
SoftwareSerial BlueT(RX,TX);
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
  int couleur=0;
  
  uint16_t nb_blocks;
  char buf[32];

  
// controle du module de distance
#define sensor A0 
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
  BlueT.begin(9600);
  //initialisation du bluetooth
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

int choix_Couleur(){
  while(!BlueT.available()) {
    delay(200);
    Serial.println("j'attend une instruction");
  }
    char couleur = char(BlueT.read());
    Serial.println(couleur);
    if(couleur == 'A'){// boite rouge
      return 0;
      Serial.println("je dois prendre le rouge");
    }
    if(couleur == 'B'){ //boite verte 
      return 1;
      Serial.println("je dois prendre le vert");
    }
}
void loop()
{
  int position_x;
  
  if (premiercoup) // permet d'initialiser la caméra, qui me un peu de temps à se synchroniser et d'attendre le choix de l'objet à récuperer
  { 
    couleur = choix_Couleur();
    delay(250);
    premiercoup=0;
    Serial.println(couleur);
    
        
  }
  // Pixy configuré pour ne détecter qu'un seul block pour une signature, la signature 0 correspond à la boite rouge et la signature 1 à la boite Bleue
  nb_blocks = pixy.getBlocks();
  position_x = pixy.blocks[couleur].x; //actualisation à chaque tour de boucle de la position de l'objet sur l'axe x
  
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
      analogWrite(ENA,195);
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
      if (position_x < 150 && position_x > 0) // 160 correspond au milieu de la scène
      {
        // L'objet est à gauche de la caméra, il faut tourner à gauche
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        //Serial.println(position_x);
        Serial.println("je dois tourner à gauche");
        analogWrite(ENA,0);
        analogWrite(ENB,195);
        delay(200);
        // on éteint les moteurs 
        analogWrite(ENA,0);
        analogWrite(ENB,0);
      }
      else if (position_x > 170 && position_x < 319) // il faut tourner à droite
      {
         digitalWrite(IN1,LOW);
         digitalWrite(IN2,HIGH);
         digitalWrite(IN3,HIGH);
         digitalWrite(IN4,LOW);
         //Serial.println(position_x);
         Serial.println("je dois tourner à droite");
         analogWrite(ENA,195);
         analogWrite(ENB,0);
         delay(200);
            // on éteint les moteurs 
         analogWrite(ENA,0);
         analogWrite(ENB,0);
      }
      else if (position_x<=170 && position_x>=150) // il ne faut plus tourner, il ne reste plus qu'à avancer vers l'objet
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
    float d = analogRead(sensor)/204.8;
    Serial.println(d);
    while(d < 1.01){
        // Avance tout droit
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        analogWrite(ENA,145);
        analogWrite(ENB,145);
        float d = analogRead(sensor)/204.8;
        Serial.println("je dois avancer");
        Serial.println(d);
        delay(100);
        if(d>1.01){
          analogWrite(ENA,0);
          analogWrite(ENB,0);
          Serial.println("je dois attraper l'objet");
          Servo3.write(10);
          delay(1500);
          Servo2.write(88);
          delay(1500);
          Servo3.write(49);
          delay(1500);
          Servo2.write(180);
          delay(2500);
          Servo1.write(30);
          delay(1500);
          Servo2.write(88);
          delay(1500);
          Servo3.write(10);
          delay(100000);
        }
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
      Servo3.write(10);
      delay(1500);
      Servo2.write(88);
      delay(1500);
      Servo3.write(70);
      delay(1500);
      Servo2.write(180);
      delay(1500);
      Servo1.write(30);
      delay(1500);
      Servo2.write(88);
      delay(1500);
      Servo3.write(10);
      delay(100000);
  } 
}
