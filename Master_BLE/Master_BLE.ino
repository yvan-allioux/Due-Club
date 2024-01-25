void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Utiliser Serial1 pour le module Bluetooth 1
  Serial2.begin(9600); // Utiliser Serial2 pour le module Bluetooth 2
}

void loop() {
  // Si des données sont disponibles sur le module Bluetooth 1, les envoyer au module 2
  if (Serial1.available()) {
    char data = Serial1.read();
    Serial.print("Module 1 -> Module 2: ");
    Serial.println(data);
    Serial2.write(data);
  }

  // Si des données sont disponibles sur le module Bluetooth 2, les envoyer au module 1
  if (Serial2.available()) {
    char data = Serial2.read();
    Serial.print("Module 2 -> Module 1: ");
    Serial.println(data);
    Serial1.write(data);
  }
}
