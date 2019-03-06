#include <SoftwareSerial.h>

char message[2];
String cle="";
String cont="";
String recu="";

 SoftwareSerial mySerial(12, 13); // RX, TX 

 void setup() {       

  Serial.begin(9600);  
   
  mySerial.begin(9600);   
  
 }  

 
 void loop() {
  
  while (mySerial.available()){   
    recu += char(mySerial.read());
  }
  
  
  if(recu!=""){
    
    Serial.println("Message :");
    Serial.println(recu);
    
    cle=recu[0];
    cont=recu.substring(2,6);

    Serial.print("Composant = ");
    Serial.print(cle);
    Serial.print("    Contenu = ");
    Serial.println(cont);
    
    delay(200);
  } 
    
 }  
