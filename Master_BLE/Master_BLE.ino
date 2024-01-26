void setup() {
  Serial1.begin(9600); // Communication avec le téléphone (maître)
  Serial2.begin(9600); // Communication avec l'esclave
  Serial3.begin(9600); // Communication avec Musique
  Serial.begin(9600); // Communication avec l'esclave
}

void loop() {
  // Lire les données du téléphone (maître) et les envoyer à l'esclave
  if (Serial1.available()) {
    char data = Serial1.read();
    Serial2.write(data);
  }

  // Lire les données de l'esclave et les envoyer au téléphone (maître)
  if (Serial2.available()) {
    char data = Serial2.read();
    Serial1.write(data);
  }
  
  if (Serial3.available()) {
    char data = Serial3.read();
    Serial.write(data);
    Serial1.write(data);
    Serial2.write(data);
    Serial3.write(data);
  }
}