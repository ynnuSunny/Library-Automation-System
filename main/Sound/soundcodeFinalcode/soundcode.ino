#define sensorPin 7
#define buzzerpin 6
#define outPin 5


unsigned long lastEvent = 0;
void soundWorks(){
  int sensorData = digitalRead(sensorPin);

  if (sensorData == LOW) {
    
    if (millis() - lastEvent > 25) {
      digitalWrite(outPin,HIGH);
      Serial.println("Clap detected!");
       tone(buzzerpin, 1200);
       delay(600);       
       noTone(buzzerpin); 

    }
    
     lastEvent = millis();
  }
}
void setup() {

  
  pinMode(sensorPin, INPUT); 
  pinMode(buzzerpin, OUTPUT);  
  pinMode(outPin, OUTPUT);  

  Serial.begin(9600);

  
}



  
void loop() {
  soundWorks();
  
}
