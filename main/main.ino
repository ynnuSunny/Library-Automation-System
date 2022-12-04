#include <Servo.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(19, 18, 5, 4, 3, 2);


#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   

int count = 0 ;
int t = 0 ;
char c ,c1;
String id ;
String id1 ;
Servo myservo,yourservo;
String userId[3];
bool cond = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();      
  mfrc522.PCD_Init();
  myservo.attach(6);
  myservo.write(0);
  yourservo.attach(7);
  yourservo.write(0);
  //pinMode(13, OUTPUT);
  
  //Serial.println("Please scan your RFID TAG");

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to Library");
  

  
  

}



void loop() {

   
 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  
  
  //Serial.print("UID tag :");
  //String content= "";
  byte letter;
  id = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     id.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     id.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  //Serial.println();
  //Serial.print("Message : ");
  id.toUpperCase();
  
  //Serial.print("ID : ");
  //Serial.println(id);
  
  
  if(id.compareTo(userId[1])==0){
       
       //Serial.println("User 1 takes bag");
       //Serial.print("ID : ");
       //Serial.println(id);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("User 1 takes bag");
       lcd.setCursor(0, 1);
       lcd.print("ID : ");
       lcd.setCursor(6, 1);
       lcd.print(id);
       
       myservo.write(180);
       delay(3000);
       myservo.write(0);
       userId[1]=""; 
       cond = true;
  }
  else if(id.compareTo(userId[2])==0){
       
//       Serial.println("User 2 takes bag");
//       Serial.print("ID : ");
//       Serial.println(id);

       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("User 2 takes bag");
       lcd.setCursor(0, 1);
       lcd.print("ID : ");
       lcd.setCursor(6, 1);
       lcd.print(id);
      
       yourservo.write(180);
       delay(3000);
       yourservo.write(0);
       userId[2]=""; 
       cond = true;
  }
  else if(userId[1].length()==0){
//       Serial.println("User 1 register");
//       Serial.print("ID : ");
//       Serial.println(id);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("User 1 register");
       lcd.setCursor(0, 1);
       lcd.print("ID : ");
       lcd.setCursor(6, 1);
       lcd.print(id);
       
       userId[1] = id;
       myservo.write(180);
       delay(3000);
       myservo.write(0);
  }
  else if(userId[2].length()==0){
//       Serial.println("User 2 register");
//       Serial.print("ID : ");
//       Serial.println(id);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("User 2 register");
       lcd.setCursor(0, 1);
       lcd.print("ID : ");
       lcd.setCursor(6, 1);
       lcd.print(id);
       
       userId[2] = id;
       yourservo.write(180);
       delay(3000);
       yourservo.write(0);
  }
  else{
       if(userId[1].length()!=0 && userId[2].length()!=0 ){
          if(cond){
             //Serial.println("There is no space!!!");
             lcd.clear();
             lcd.setCursor(0, 0);
             lcd.print("There is no space!!!");
       
             cond = false;
          }
          
      }
      else{
         digitalWrite(13, LOW);
         Serial.println("Invalid TAG");
         myservo.write(0);
      }
  }
  
  


}
