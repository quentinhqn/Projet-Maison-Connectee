#include <Keypad.h>
#include <Servo.h>

      //***DIGICODE***//
const byte rows = 4; //quatre lignes
const byte cols = 4; //quatre colonnes
const String password = "7352B"; //mot de passe
int i_digi=0;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {37,36,35,34}; //Lignes
byte colPins[cols] = {33,32,31,30}; //Colonnes
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );


      //***SERVO***//
Servo servo;


      //***PORTE & FENETRE***//
int pin_porte = 3;
int val_porte=0;
int etat_porte=0;

int pin_fenetre = 4;
int val_fenetre=0;
int etat_fenetre=0;


      //***SONETTE***//
int pin_sonette=2;
int val_sonette=0;

      //***DETECTEUR DE MOUVEMENT***//
int pin_detecteur=6;
int val_detecteur=0;
      
void setup() {
    Serial.begin(9600); //Serial monitor
  

      //***DIGICODE***//
  keypad.setHoldTime(4); 
  keypad.setDebounceTime(4); 


      //***SERVO***//
  servo.attach(5);
  servo.write(0);


      //***PORTE & FENETRE***//
  pinMode(pin_porte,INPUT);
  pinMode(pin_fenetre,INPUT);


      //***SONETTE***//
  pinMode(pin_sonette,INPUT);


      //***DETECTEUR DE MOUVEMENT***//
  pinMode(pin_detecteur,INPUT);
}

      

void loop() {
      //***DIGICODE***//
  String mdp = "";

  char key = keypad.getKey();
  if (key != NO_KEY){
    mdp+=key;
    i_digi++;
  }
  if((mdp==password) && (i_digi<5)){
    Serial.println("Porte ouverte !");
    i_digi=0;
  }else if(i_digi==5){
    Serial.println("Mauvais mot de passe");
    i_digi=0;
  }


      //***SERVO***//
    //servo.write(180);

      //***PORTE & FENETRE***//
  val_porte=digitalRead(pin_porte);
  if(val_porte==LOW){
    if (etat_porte==0){
      delay(200); 
    } else {
      Serial.println("La porte a été fermée.");
      etat_porte=0;
    }
  }
  else if(etat_porte==0) {
    Serial.println("La porte a été ouverte !");
    etat_porte=1;
  }

  val_fenetre=digitalRead(pin_fenetre);
  if(val_fenetre==LOW){
    if (etat_fenetre==0){
      delay(200); 
    } else {
      Serial.println("La fenetre a été fermée.");
      etat_fenetre=0;
    }
  }
  else if(etat_fenetre==0) {
    Serial.println("La fenetre a été ouverte !");
    etat_fenetre=1;
  }


      //***SONETTE***//



      //***DETECTEUR DE MOUVEMENT***//
  val_detecteur=digitalRead(pin_detecteur);
  if(val_detecteur!=0){
    Serial.println("Mouvement dans la maison");
    delay(1000);  
  }
}
