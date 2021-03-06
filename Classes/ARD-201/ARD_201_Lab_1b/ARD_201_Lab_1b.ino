#define LED_PIN         13
#define LED_BLINK_TIME  5000

uint8_t ledState = 0;
uint32_t nextBlink = 0;

void setup() {                
  pinMode(LED_PIN, OUTPUT); 
  Serial.begin(9600);  
}

void loop() {
  uint32_t currentTime = millis();
  
  if( (int32_t) (currentTime - nextBlink) >= 0) {
    nextBlink = currentTime + LED_BLINK_TIME;
    digitalWrite(LED_PIN, ledState);
    ledState = !ledState;
  }

  while(Serial.available() > 0) {
    Serial.write(Serial.read());
  }            
}
