#define LED_PIN 13

void setup() {                
  pinMode(LED_PIN, OUTPUT); 
  Serial.begin(9600);  
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(5000);               
  digitalWrite(LED_PIN, LOW);   
  delay(5000);

  while(Serial.available() > 0) {
    Serial.write(Serial.read());
  }            
}

