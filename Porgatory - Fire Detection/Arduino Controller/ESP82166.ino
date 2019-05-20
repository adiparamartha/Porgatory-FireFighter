#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>


// Set these to run example.
#define FIREBASE_HOST "FIREBASE-DATABASE"
#define FIREBASE_AUTH "FIREBASE-AUTH"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

SoftwareSerial NodeMCU(D2,D3);

void setup(){
	Serial.begin(9600);

    NodeMCU.begin(115200);

    pinMode(D7,INPUT);

    pinMode(D8,OUTPUT);


   // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

void loop(){

  String content = "";

char character;

  while(NodeMCU.available() > 0) {

      character = NodeMCU.read();

      content.concat(character);
  }

  if (content != "") {
       String Light1 = getValue(content, '-', 0);
       String Light2 = getValue(content, '-', 1);
       String MQ2_1 = getValue(content, '-', 2);
       String MQ2_2 = getValue(content, '-', 3);
       String Condition = getValue(content, '-', 4);    
      
       Serial.println("Light1: " + Light1);
       Serial.println("Light2: " + Light2); 
       Serial.println("MQ2-1: " + MQ2_1);
       Serial.println("MQ2-2: " + MQ2_2);
       Serial.println("Condition: " + Condition);
       Serial.println("- - - - - - - - - - -");

       if (Condition == "Normal"){
        
             Firebase.setString("Left_Light", Light1);
              // handle error
              if (Firebase.failed()) {
                  Serial.print("LL /number failed:");
                  Serial.println(Firebase.error());  
                  return;
              }
        
               Firebase.setString("Right_Light", Light2);
               // handle error
              if (Firebase.failed()) {
                  Serial.print("RL /number failed:");
                  Serial.println(Firebase.error());  
                  return;
              }
        
               Firebase.setString("Left_MQ2", MQ2_1);
               // handle error
              if (Firebase.failed()) {
                  Serial.print("LMQ2 /number failed:");
                  Serial.println(Firebase.error());  
                  return;
              }
        
               Firebase.setString("Right_MQ2", MQ2_2);
               // handle error
              if (Firebase.failed()) {
                  Serial.print("RMQ2 /number failed:");
                  Serial.println(Firebase.error());  
                  return;
              }
        
               Firebase.setString("Status", Condition);
              // handle error
              if (Firebase.failed()) {
                  Serial.print("Normal Status failed:");
                  Serial.println(Firebase.error());  
                  return;
              }
          }
          
       else{
              Firebase.setString("Status", Condition);
              // handle error
              if (Firebase.failed()) {
                  Serial.print(" Not Normal Status failed:");
                  Serial.println(Firebase.error());  
                  return;
              }
          }
  
  }

 delay(5000);

}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void firebaseupdate(String light1, String light2, String mq2_1, String mq2_2, String condition){

  Serial.println("AAA : " + condition);
  
  
}
