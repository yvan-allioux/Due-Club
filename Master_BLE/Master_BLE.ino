void setup() {
  Serial1.begin(9600); // Communication with Light
  Serial2.begin(9600); // Communication with Phone
  Serial3.begin(9600); // Communication with Sound
}

void loop() {

  // Send Light info to Phone
  if (Serial1.available()) {
    char data = Serial1.read(); // Get Light data
    Serial2.write(data); // Send to phone
  }

  // Send Phone commands to Light and Sound
  if (Serial2.available()) {
    char data = Serial2.read(); // Get Phone data
    Serial1.write(data); // Send to Light
    Serial3.write(data); // Send to Sound
  }
}