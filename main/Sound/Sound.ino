const int buzzer = 5; //buzzer to arduino pin 10
#define sensorPin 4 //sound sensor to arduino pin 4


// Variable to store the time when last event happened
unsigned long lastEvent = 0;


void setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(sensorPin, INPUT);  // Set sensor pin as an INPUT

  
  Serial.begin(9600);

}

void loop(){

  // Read Sound sensor
  int sensorData = digitalRead(sensorPin);

  // If pin goes LOW, sound is detected
  if (sensorData == LOW) {
    
    // If 25ms have passed since last LOW state, it means that
    // the clap is detected and not due to any spurious sounds
    if (millis() - lastEvent > 25) {
       Serial.println("Table 1 making noice");
       tone(buzzer, 500); // Send 1KHz sound signal...
       delay(500);        // ...for 1 sec
       noTone(buzzer);     // Stop sound...
       delay(500);        // ...for 1sec
    }
    
    // Remember when last event happened
    lastEvent = millis();
  }
  
  

  
}
