#include <Keypad.h>
#include <Servo.h>


//***DIGICODE***//
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

byte rowPins[rows] = {2, 3, 4, 5}; 
byte colPins[cols] = {6, 7, 8, 12}; 
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );


Servo servo;


void setup() {
  Serial.begin(9600);
  
  //***DIGICODE***//
  myKeypad.setHoldTime(4); 
  myKeypad.setDebounceTime(4); 

  //***SERVO***//
  servo.attach(9);
  servo.write(100);
}

      

void loop() {
  char key = myKeypad.getKey();
  if(key != 0) {
    if (i_digi<5) {
       mdp[i_digi] = key;  
       i_digi = i_digi+1 ;
     }
     if (i_digi == 5) {
      if(strcmp(mdp,password) == 0) {
        Serial.println("Porte ouverte !");
        servo.write(0);
        delay(5000);
        servo.write(100);
        i_digi=0;
      }
      else {
        Serial.println("Mauvais mot de passe");
        i_digi=0;
      }
     }
  }
}
