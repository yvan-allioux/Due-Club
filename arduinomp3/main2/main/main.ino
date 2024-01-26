#include <SoftwareSerial.h>

SoftwareSerial mainCommandeSerial(2, 3); //commande

SoftwareSerial mp3(5, 6); // Utilisation de SoftwareSerial pour communiquer avec le module MP3 (RX = 5, TX = 6)

static uint8_t cmdbuf[8] = {0}; // Tableau pour stocker les commandes à envoyer au module MP3

// Définition des commandes pour le module MP3
#define CMD_NEXT             0x01 // Jouer la piste suivante
#define CMD_PREV             0x02 // Jouer la piste précédente
#define CMD_PLAYN            0x03 // Jouer la piste numéro 'n'
#define CMD_VOL_UP           0x04 // Augmenter le volume
#define CMD_VOL_DOWN         0x05 // Diminuer le volume
#define CMD_SET_VOL          0x06 // Définir le volume (0-30)
#define CMD_SEL_DEV          0x09 // Sélectionner le périphérique de stockage (ex: carte SD)
#define CMD_SLEEP_MODE       0x0A // Activer le mode sommeil
#define CMD_WAKE_UP          0x0B // Sortir du mode sommeil
#define CMD_RESET            0x0C // Réinitialiser le module MP3
#define CMD_PLAY             0x0D // Commencer la lecture
#define CMD_PAUSE            0x0E // Mettre la lecture en pause
#define CMD_STOP_PLAY        0x16 // Arrêter la lecture
#define CMD_FOLDER_CYCLE     0x17 // Jouer en boucle tous les fichiers d'un dossier spécifique

void command(int8_t cmd, int16_t dat) {
  delay(20);  // Délai pour assurer la stabilité de la communication
  cmdbuf[0] = 0x7e; // Octet de début
  cmdbuf[1] = 0xFF; // Version
  cmdbuf[2] = 0x06; // Nombre d'octets dans la commande
  cmdbuf[3] = cmd;  // La commande
  cmdbuf[4] = 0x00; // 0x00 = pas de retour, 0x01 = avec retour
  cmdbuf[5] = (int8_t)(dat >> 8); // Premier octet de la donnée
  cmdbuf[6] = (int8_t)(dat);      // Deuxième octet de la donnée
  cmdbuf[7] = 0xef; // Octet de fin

  for (uint8_t i = 0; i < 8; i++) {
    mp3.write(cmdbuf[i]); // Envoi de chaque octet de la commande
  }
}

void setup() {
  mp3.begin(9600);     // Communication avec le module MP3
  delay(200); 
  mainCommandeSerial.begin(9600); // Communication avec le main
  delay(500); // Attente pour l'initialisation
  command(CMD_SEL_DEV, 0x0002); // Sélection de la carte SD
  delay(200);
  command(CMD_SET_VOL, 0x0010); // Volume initial à 30
  command(CMD_PLAYN, 0x0001);   // Lecture de la première piste
}

void loop() {
  if (mainCommandeSerial.available() > 0) {
    String commandInput = mainCommandeSerial.readStringUntil('\n'); // Lecture de la commande du port série

    // Analyse et exécution des commandes
    if (commandInput == "next") {
      command(CMD_NEXT, 0); // Commande pour jouer la piste suivante
    } else if (commandInput == "prev") {
      command(CMD_PREV, 0); // Commande pour jouer la piste précédente
    } else if (commandInput.startsWith("play ")) {
      int track = commandInput.substring(5).toInt();
      command(CMD_PLAYN, track); // Jouer la piste numéro 'n'
    } else if (commandInput == "volup") {
      command(CMD_VOL_UP, 0); // Augmenter le volume
    } else if (commandInput == "voldown") {
      command(CMD_VOL_DOWN, 0); // Diminuer le volume
    } else if (commandInput.startsWith("volume ")) {
      int volume = commandInput.substring(7).toInt();
      command(CMD_SET_VOL, volume); // Définir un niveau de volume spécifique
    } else if (commandInput == "P") {
      command(CMD_PAUSE, 0); // Mettre la lecture en pause
    } else if (commandInput == "R") {
      command(CMD_PLAY, 0); // Reprendre la lecture
    } else if (commandInput == "stop") {
      command(CMD_STOP_PLAY, 0); // Arrêter la lecture
    } else if (commandInput == "sleep") {
      command(CMD_SLEEP_MODE, 0); // Activer le mode sommeil
    } else if (commandInput == "wake") {
      command(CMD_WAKE_UP, 0); // Désactiver le mode sommeil
    } else if (commandInput == "reset") {
      command(CMD_RESET, 0); // Réinitialiser le module MP3
    } else if (commandInput.startsWith("folder ")) {
      int folder = commandInput.substring(7).toInt();
      command(CMD_FOLDER_CYCLE, folder); // Jouer en boucle les fichiers d'un dossier
    }
    // Ajoutez ici d'autres commandes au besoin
  }
}
