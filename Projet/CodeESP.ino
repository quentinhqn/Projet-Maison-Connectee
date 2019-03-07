#include <SoftwareSerial.h>
#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <HTTPClient.h>


#define FIREBASE_HOST "https://smarthouse-232d7.firebaseio.com/"
#define FIREBASE_AUTH "xxxxx"

#define WIFI_SSID "Galaxy S9"
#define WIFI_PASSWORD "xxxxx"

#define R 5
#define G 18
#define B 19

#define sonette 15
#define pluie 23
#define ouvPorte 0
#define ouvFenetre 4
#define chauff 22
#define ledSonette 21


const int freq = 5000;
const int ledR = 0;
const int ledG = 1;
const int ledB = 2;
const int ledChauff = 3;
const int resolution = 8;


const String key = "key=xxxxxx";
const String contentNotifDebut = "{\"to\":\"xxxxxxx\",\"notification\":{\"body\":\"";
const String contentNotifFin = "\"},\"priority\":\"high\",\"sound\":\"default\"}";

boolean sonetteStatus = true;
boolean alarmeStatus = true;
boolean pluieStatus = true;

SoftwareSerial liaison(16, 17);


void envoyerNotif(String id, String message) {
  Serial.println(message);
  HTTPClient http;   
  http.begin("http://fcm.googleapis.com/fcm/send");
  http.addHeader("Content-Type", "application/json");  
  http.addHeader("Authorization", key);  
  int httpResponseCode = http.POST(contentNotifDebut + message + contentNotifFin);
  http.end();
}

void setup() {
  ledcSetup(ledR, freq, resolution);
  ledcSetup(ledG, freq, resolution);
  ledcSetup(ledB, freq, resolution);
  ledcSetup(ledChauff, freq, resolution);
  ledcAttachPin(R, ledR);
  ledcAttachPin(G, ledG);
  ledcAttachPin(B, ledB);
  ledcAttachPin(chauff, ledChauff);
  Serial.begin(115200);
  liaison.begin(9600);

  pinMode(sonette, INPUT);
  pinMode(pluie, INPUT);
  pinMode(ouvPorte, INPUT);
  pinMode(ouvFenetre, INPUT);
  pinMode(ledSonette, OUTPUT);
  digitalWrite(ledSonette, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("Connected : ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  JsonObject& rgbData = Firebase.get("/rgbSalon/");
  ledcWrite(ledR, rgbData[String("R")].as<int>());
  ledcWrite(ledG, rgbData[String("G")].as<int>());
  ledcWrite(ledB, rgbData[String("B")].as<int>());

  JsonObject& alerts = Firebase.get("/alertes/");
  sonetteStatus = alerts[String("sonette")].as<bool>();
  alarmeStatus = alerts[String("alarme")].as<bool>();
  pluieStatus = alerts[String("pluie")].as<bool>();

  ledcWrite(ledChauff, 255);

  
  Firebase.stream("", [](FirebaseStream stream) {
    if (stream.getEvent() == "put") {
      if(stream.getPath() == "/porte") {
        Serial.println("porte Change");
        liaison.println("porte:" + String(stream.getDataBool()) + ";");
      }
      else if(stream.getPath() == "/chauffageAuto/temp") {
        Serial.println("Temp Change");
        liaison.println("temp:" + String(stream.getDataBool()) + ";");
      }
      else if(stream.getPath() == "/rgbSalon/R") {
        ledcWrite(ledR, stream.getDataInt());
      }
      else if(stream.getPath() == "/rgbSalon/G") {
        ledcWrite(ledG, stream.getDataInt());
      }
      else if(stream.getPath() == "/rgbSalon/B") {
        ledcWrite(ledB, stream.getDataInt());
      }
      else if(stream.getPath() == "/alertes/sonette") {
        sonetteStatus = stream.getDataBool();
      }
      else if(stream.getPath() == "/alertes/alarme") {
        alarmeStatus = stream.getDataBool();
      }
      else if(stream.getPath() == "/alertes/pluie") {
        pluieStatus = stream.getDataBool();
      }
    }
});
}


void loop() {

  if(!digitalRead(pluie)) {
    if(!pluieStatus) {
      envoyerNotif("alertes/pluie", "Il pleut !");
    }
  }
  if(!digitalRead(sonette)) {
    if(!sonetteStatus) {
      envoyerNotif("alertes/sonette", "Quelqu'un sonne à la porte");
      Firebase.setBool("/sonette", true);
    }
    for(int i=0; i<5; i++) {
      Serial.println("test");
      digitalWrite(ledSonette, HIGH);
      delay(150);
      digitalWrite(ledSonette, LOW);
      delay(100);
    }
  }
  if(digitalRead(ouvFenetre) || digitalRead(ouvPorte)) {
    if(!alarmeStatus) {
      envoyerNotif("alertes/alarme", "Porte / fenêtre ouverte !");
    }
  }
  /*if(digitalRead(ouvPorte)) {
    if(!Firebase.getBool("alertes/alarme")) {
      envoyerNotif("alertes/alarme", "Quelqu'un est entré par effraction");
    }
  }*/
  
  /*JsonObject& rgbData = Firebase.get("/rgbSalon/");
  ledcWrite(ledR, rgbData[String("R")].as<int>());
  ledcWrite(ledG, rgbData[String("G")].as<int>());
  ledcWrite(ledB, rgbData[String("B")].as<int>());*/
  //delay(200);

}
