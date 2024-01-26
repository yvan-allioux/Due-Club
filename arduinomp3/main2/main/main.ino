const int ledPin = 13; // Led pin

// Array to store commands to send to the MP3 module
static uint8_t cmdbuf[8] = {0};

// Define commands for the MP3 module
#define CMD_NEXT 0x01    // Play the next track
#define CMD_PREV 0x02    // Play the previous track
#define CMD_PLAYN 0x03   // Play the track with the specified number
#define CMD_SET_VOL 0x06 // Define the volume level
#define CMD_SEL_DEV 0x09 // Select the device (SD card)
#define CMD_RESET 0x0C   // Reset the module
#define CMD_PLAY 0x0D    // Begin playback
#define CMD_PAUSE 0x0E   // Pause playback

const int minVolume = 0;         // Minimum volume level
const int maxVolume = 9;         // Maximum volume level
const int maxVolumeHex = 0x001E; // Maximum volume level in hexadecimal
int currentVol = 4;              // Current volume level

// Set the volume based on the specified level
void setVolume(int volumeLevel)
{
  // Check that the volume level stays within the allowed range
  volumeLevel = constrain(volumeLevel, minVolume, maxVolume);

  // Convert the volume level to a hexadecimal value
  int volumeHex = map(volumeLevel, minVolume, maxVolume, 0, maxVolumeHex);

  // Send the command to set the volume
  command(CMD_SET_VOL, volumeHex);
}

void command(int8_t cmd, int16_t dat)
{
  delay(20);
  cmdbuf[0] = 0x7e;               // Begin byte
  cmdbuf[1] = 0xFF;               // Version
  cmdbuf[2] = 0x06;               // Number of bytes in the command
  cmdbuf[3] = cmd;                // The command
  cmdbuf[4] = 0x00;               // 0x00 = no return, 0x01 =  with return
  cmdbuf[5] = (int8_t)(dat >> 8); // First byte of the data
  cmdbuf[6] = (int8_t)(dat);      // Second byte of the data
  cmdbuf[7] = 0xef;               // Last byte

  for (uint8_t i = 0; i < 8; i++)
  {
    Serial1.write(cmdbuf[i]); // Send each byte of the command
  }
}

void setup()
{

  Serial2.begin(38400); // Communication with Phone
  pinMode(ledPin, OUTPUT);
  delay(500); // Wait for the module to initialize

  Serial1.begin(9600); // Communication with MP3 module
  delay(200);
  delay(500);                   // Wait for the module to initialize
  command(CMD_SEL_DEV, 0x0002); // Select the SD card
  delay(200);
  setVolume(5); // Set the volume to 5

  command(CMD_PLAYN, 0x0001); // Play the first track
}

void loop()
{
  // Get Phone commands
  if (Serial2.available())
  {
    char command = Serial2.read();
    handleCommand(command); // Handle Phone commands
  }
}

// Function to handle commands received on Phone
void handleCommand(char cmd)
{
  switch (cmd)
  {
  case 'A':
    digitalWrite(ledPin, HIGH); // Turn on the LED on pin 13
    command(CMD_PLAY, 0);       // Start playback
    break;
  case 'B':
    digitalWrite(ledPin, LOW); // Turn off the LED on pin 13
    command(CMD_PAUSE, 0);     // Stop playback
    break;
  case '1':
    command(CMD_NEXT, 0); // Play the next track
    break;
  case '2':
    command(CMD_PREV, 0); // Play the previous track
    break;
  case 'C': // Increase the volume
    if (currentVol < 10)
    {
      currentVol = currentVol + 1;
      setVolume(currentVol); // Set the volume
    }
    break;
  case 'D': // Decrease the volume
    if (currentVol > 0)
    {
      currentVol = currentVol - 1;
      setVolume(currentVol); // Set the volume
    }
    break;
  case '5':
    command(CMD_RESET, 0); // Reset the module
    break;
  }
}