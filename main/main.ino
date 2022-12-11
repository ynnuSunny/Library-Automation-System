#include <Servo.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SPI.h>
#include <MFRC522.h>
//#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>  // Library for LCD
#include <Wire.h>               // Library for I2C communication

//LiquidCrystal lcd(3, 2, 8, 17, 18, 19); // rs, en, d4, d5, d6, d7


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);


#define LED1 14
#define LED2 15
#define LED3 16

#define button 8

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int buzzer = 5; //buzzer to arduino pin 10
#define sensorPin 4 //sound sensor to arduino pin 9
// Variable to store the time when last event happened
unsigned long lastEvent = 0;


int count = 0;
int t = 0;
char c, c1;
String id;
String id1;
Servo myservo, yourservo;
String userId[3];
bool cond = true;
int i=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  myservo.attach(6);
  myservo.write(0);
  yourservo.attach(7);
  yourservo.write(0);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(sensorPin, INPUT);  // Set sensor pin as an INPUT

  //Serial.println("Please scan your RFID TAG");

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Welcome to");
  lcd.setCursor(1, 1);
  lcd.print("Library Locker");

  delay(2000);
}



void loop() {
  

  byte buttonState = digitalRead(button);
  // Read Sound sensor
  int sensorData = digitalRead(sensorPin);

  //if (buttonState == LOW) {
    //Serial.println("Button is pressed");

    //if (i == 1) {
//      lcd.clear();
//      lcd.setCursor(2, 0);
//      lcd.print("Please Scan");
//      lcd.setCursor(1, 1);
//      lcd.print("Your RFID Card");
//      delay(2000);

      i=0;
    //}

    if (!mfrc522.PICC_IsNewCardPresent()) {
      return;
    }

    if (!mfrc522.PICC_ReadCardSerial()) {
      return;
    }



    //Serial.print("UID tag :");

    byte letter;
    id = "";


    for (byte i = 0; i < mfrc522.uid.size; i++) {
      //    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      //    Serial.print(mfrc522.uid.uidByte[i], HEX);
      id.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      id.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    // Serial.println();
    // Serial.print("Message : ");
    id.toUpperCase();

    // Serial.print("ID : ");
    // Serial.println(id);


    if (id.compareTo(userId[1]) == 0) {

      Serial.println("User 1 takes bag");
      Serial.print("ID : ");
      Serial.println(id);

      digitalWrite(LED1, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("User 1 takes bag");
      lcd.setCursor(0, 1);
      lcd.print("ID: ");
      lcd.setCursor(3, 1);
      lcd.print(id);

      delay(4000);
      lcd.clear();

      myservo.write(180);
      delay(3000);
      myservo.write(0);
      userId[1] = "";
      cond = true;
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Please Scan");
      lcd.setCursor(1, 1);
      lcd.print("Your RFID Card");
    } else if (id.compareTo(userId[2]) == 0) {

      Serial.println("User 2 takes bag");
      Serial.print("ID : ");
      Serial.println(id);

      digitalWrite(LED2, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("User 2 takes bag");
      lcd.setCursor(0, 1);
      lcd.print("ID: ");
      lcd.setCursor(3, 1);
      lcd.print(id);
    //  delay(4000);
    //  lcd.clear();

      yourservo.write(180);
      delay(3000);
      yourservo.write(0);
      userId[2] = "";
      cond = true;
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Please Scan");
      lcd.setCursor(1, 1);
      lcd.print("Your RFID Card");
    } else if (userId[1].length() == 0) {
      Serial.println("User 1 register");
      Serial.print("ID : ");
      Serial.println(id);


      digitalWrite(LED1, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("User 1 register");
      lcd.setCursor(0, 1);
      lcd.print("ID: ");
      lcd.setCursor(3, 1);
      lcd.print(id);
    //  delay(4000);
    //  lcd.clear();

      userId[1] = id;
      myservo.write(180);
      delay(3000);
      myservo.write(0);
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Please Scan");
      lcd.setCursor(1, 1);
      lcd.print("Your RFID Card");
    } else if (userId[2].length() == 0) {
      Serial.println("User 2 register");
      Serial.print("ID : ");
      Serial.println(id);

      digitalWrite(LED2, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("User 2 register");
      lcd.setCursor(0, 1);
      lcd.print("ID : ");
      lcd.setCursor(3, 1);
      lcd.print(id);
    //  delay(4000);
    //  lcd.clear();

      userId[2] = id;
      yourservo.write(180);
      delay(3000);
      yourservo.write(0);    
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Please Scan");
      lcd.setCursor(1, 1);
      lcd.print("Your RFID Card");  
    } else {
      if (userId[1].length() != 0 && userId[2].length() != 0) {
        if (cond) {
          Serial.println("There is no space!!!");

          lcd.clear();
          lcd.setCursor(2, 0);
          lcd.print("There is no");
          lcd.setCursor(4, 1);
          lcd.print("space!!!");

          delay(5000);
          lcd.clear();

          digitalWrite(LED3, HIGH);
          delay(3000);
          digitalWrite(LED3, LOW);
          

          cond = false;
        }

      } else {
        digitalWrite(13, LOW);
        Serial.println("Invalid TAG");
        myservo.write(0);
      }
    }
//  }
//  else{
//  
//     if(i==0){
//       i=1;
//     }
//     else{
//       lcd.clear();
//     }
//  }

 

}
