#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
//======================================== 

//======================================== Insert your network credentials.
#define WIFI_SSID "C2"
#define WIFI_PASSWORD "011201302"
//======================================== 

//Provide the token generation process info.
#include "addons/TokenHelper.h"

//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Defines the Digital Pin of the "On Board LED".
#define On_Board_LED 2

// Insert Firebase project API Key
#define API_KEY "AIzaSyCj1YlqwWvWEzcxJfwnrbXcLqPg3_bzK9w"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://test-5136c-default-rtdb.asia-southeast1.firebasedatabase.app/" 

// Define Firebase Data object.
FirebaseData fbdo;

// Define firebase authentication.
FirebaseAuth auth;

// Definee firebase configuration.
FirebaseConfig config;

//======================================== Millis variable to send/store data to firebase database.
unsigned long sendDataPrevMillis = 0;
const long sendDataIntervalMillis = 10000; //--> Sends/stores data to firebase database every 10 seconds.
//======================================== 

// Boolean variable for sign in status.
bool signupOK = false;

float store_random_Float_Val;
int store_random_Int_Val;



#define sensorPin A0 
#define BOX_ONE_PIN 0
#define BOX_TWO_PIN 1

unsigned long lastEvent = 0;



//____________________________ VOID SETUP
void setup() {
    Serial.begin(9600);
    pinMode(sensorPin, INPUT);

  // put your setup code here, to run once:
   pinMode(sensorPin, INPUT);  // Set sensor pin as an INPUT

  Serial.println();

  pinMode(On_Board_LED, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(BOX_ONE_PIN,INPUT);
  pinMode(BOX_TWO_PIN,INPUT);


  //---------------------------------------- The process of connecting the WiFi on the ESP32 to the WiFi Router/Hotspot.
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("---------------Connection");
  Serial.print("Connecting to : ");
  Serial.println(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");

    digitalWrite(On_Board_LED, HIGH);
    delay(250);
    digitalWrite(On_Board_LED, LOW);
    delay(250);
  }
  digitalWrite(On_Board_LED, LOW);
  Serial.println();
  Serial.print("Successfully connected to : ");
  Serial.println(WIFI_SSID);
  //Serial.print("IP : ");
  //Serial.println(WiFi.localIP());
  Serial.println("---------------");
  //---------------------------------------- 

  // Assign the api key (required).
  config.api_key = API_KEY;

  // Assign the RTDB URL (required).
  config.database_url = DATABASE_URL;

  // Sign up.
  Serial.println();
  Serial.println("---------------Sign up");
  Serial.print("Sign up new user... ");
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  Serial.println("---------------");
  
  // Assign the callback function for the long running token generation task.
  config.token_status_callback = tokenStatusCallback; //--> see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}
//____________________________ 

//____________________________ VOID LOOP


void loop() {
  
  
  
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > sendDataIntervalMillis || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    //sound sensor value
     


    
    int randNumber = random(15, 40);
    float f = (float)randNumber / 1.01;
    int i = (int(f*100));
    store_random_Float_Val = float(i) / 100;
    store_random_Int_Val = random(10, 99);
    //---------------------------------------- 

   

    //---------------------------------------- The process of sending/storing data to the firebase database.
    Serial.println();
    Serial.println("---------------Store Data");
    digitalWrite(On_Board_LED, HIGH);
    
    
  
      if (BOX_ONE_PIN == HIGH) {
           Serial.println("BOX ONE IS EMPTY");
           
          if (Firebase.RTDB.setString(&fbdo, "Test/BOX-ONE","BOX ONE IS EMPTY" )) {
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
          }
          else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
          }
      }else{
           Serial.println("BOX ONE IS FULL");
           
          if (Firebase.RTDB.setString(&fbdo, "Test/BOX-ONE","BOX ONE IS FULL" )) {
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
          }
          else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
          }
      }

      if (BOX_TWO_PIN == HIGH) {
           Serial.println("BOX TWO IS EMPTY");
           
          if (Firebase.RTDB.setString(&fbdo, "Test/BOX-TWO","BOX TWO  IS EMPTY" )) {
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
          }
          else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
          }
      }else{
           Serial.println("BOX TWO IS FULL");
           
          if (Firebase.RTDB.setString(&fbdo, "Test/BOX-TWO","BOX TWO IS FULL" )) {
            Serial.println("PASSED");
            Serial.println("PATH: " + fbdo.dataPath());
            Serial.println("TYPE: " + fbdo.dataType());
          }
          else {
            Serial.println("FAILED");
            Serial.println("REASON: " + fbdo.errorReason());
          }
      }
   
    
    
    
    digitalWrite(On_Board_LED, LOW);
    Serial.println("---------------");
    //---------------------------------------- 
  }
}
