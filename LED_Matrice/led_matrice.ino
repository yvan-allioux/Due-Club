#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8
#define CS_PIN 10

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  myDisplay.begin();
  myDisplay.setIntensity(4);
  myDisplay.displayClear();
  
  // Affiche le premier message avec un fondu
  myDisplay.displayText("Due Club", PA_CENTER, 0, 0, PA_NO_SCROLL, PA_FADE);

  // Attends un peu avant de commencer la transition
  delay(2000);
}

void loop() {
  // Affiche le deuxième message avec un fondu
  myDisplay.displayText("Welcome To The Party", PA_CENTER, 0, 0, PA_NO_SCROLL, PA_FADE);

  // Attends un peu avant de recommencer le défilement
  delay(2000);
  myDisplay.displayClear();  // Efface l'affichage après le fondu
}
