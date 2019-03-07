#include <Keypad.h>
#include <SoftwareSerial.h>
#include <Servo.h>


        //**********DIGICODE**********//
      
const byte rows = 4; //quatre lignes
const byte cols = 4; //quatre colonnes
char password[6] = "7352B"; //mot de passe
char mdp[6] = "";
int i_digi=0;

char keys[cols][rows] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {4, 7, 8, A4}; 
byte colPins[cols] = {10, 11, 12, 13}; 
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

Servo servo;

        //**********TRANSMISSION ESP**********//
        
 SoftwareSerial mySerial(3, A5); // RX, TX 
        
String cle="";
String oldKey="";
int contenu;
int oldContent;
String recu="";


        //**********BUZZER**********//
        
#define buzzer A0 // Borne de sortie
        
        
        //**********CHAUFFAGE**********//

boolean chauffageAuto = true;
#define ledPin 6


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  
        //**********DIGICODE**********//
  myKeypad.setHoldTime(4); 
  myKeypad.setDebounceTime(4); 

        //**********BUZZER**********//
        
  pinMode(buzzer,OUTPUT);

  servo.attach(9);
  servo.write(90);
  delay(200);
  servo.detach();

}


      

void loop() {
  
        //**********TRANSMISSION ESP**********//

  while (mySerial.available()){   
    recu += char(mySerial.read());
  }
  
  delay(50);//Delay : necéssaire pour finir de lire 7 caractères.
  
  if(recu!=""){
    Serial.println(recu);
    cle=recu[0];
    contenu=recu.substring(1,4).toInt();//
    recu="";
  }
        //**********DIGICODE**********//
        
  char key = myKeypad.getKey();
  if(key != 0) {
    if (i_digi<5) {
       mdp[i_digi] = key;  
       i_digi = i_digi+1 ;
       tone(buzzer,1000,100);
     }
     if (i_digi == 5) {
      if(strcmp(mdp,password) == 0) {
        tone(buzzer,200,500);
        delay(400);
        tone(buzzer,1000,100);
        Serial.println("Porte ouverte !");
        i_digi=0;
        servo.attach(9);
        servo.write(0);
        delay(3000);
        servo.write(90);
        delay(500);
        servo.detach();
      }
      else {
        tone(buzzer,400,400);
        delay(600);
        tone(buzzer,400,400);
        delay(600);
        tone(buzzer,400,400);
        Serial.println("Mauvais mot de passe");
        i_digi=0;
      }
     }
  }

        //**********CHAUFFAGE**********//

    if(cle=="C" && oldContent!=contenu) {
      oldKey=cle;
      oldContent=contenu;
      Serial.println(contenu);
      analogWrite(ledPin,contenu);
    }

    if(cle=="P" && oldContent!=contenu) {
      oldKey=cle;
      oldContent=contenu;
      Serial.println(contenu);
      servo.attach(9);
      servo.write(contenu);
      delay(500);
      servo.detach();
    }

}
