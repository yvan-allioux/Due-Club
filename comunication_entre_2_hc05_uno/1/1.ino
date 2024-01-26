const int ledPin = 13; 

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); // Configure le pin 13 comme sortie
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char received = Serial.read();
    if (received == 'A') {
      // Boucle pour faire clignoter la LED 10 fois
      for (int i = 0; i < 10; i++) {
        digitalWrite(ledPin, HIGH);   // Allume la LED
        delay(200);                   // Attend 200 ms
        digitalWrite(ledPin, LOW);    // Éteint la LED
        delay(200);                   // Attend 200 ms
      }
    }
  }
}
