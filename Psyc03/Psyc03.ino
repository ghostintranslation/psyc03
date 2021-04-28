/*
 __    _  _____   ___      ___ _  _     __    _ ______ _    
/__|_|/ \(_  |     | |\|    | |_)|_||\|(_ |  |_| |  | / \|\|
\_|| |\_/__) |    _|_| |    | | \| || |__)|__| | | _|_\_/| |

PSYC03
v1.1.0

Support my work:
https://www.paypal.com/paypalme/ghostintranslation

https://www.ghostintranslation.com/
https://ghostintranslation.bandcamp.com/
https://www.instagram.com/ghostintranslation/
https://www.youtube.com/channel/UCcyUTGTM-hGLIz4194Inxyw
https://github.com/ghostintranslation
*/

#include <Audio.h>

#include "Motherboard9.h"
#include "Psyc03.h"

// Instanciation of Psyc03
Psyc03 * psyc03 = Psyc03::getInstance();

AudioOutputI2S  i2s2;
AudioOutputUSB usb;
AudioConnection patchCord1(*psyc03->getOutput(), 0, i2s2, 0);
AudioConnection patchCord2(*psyc03->getOutput(), 0, i2s2, 1);
AudioConnection patchCord3(*psyc03->getOutput(), 0, usb, 0);
AudioConnection patchCord4(*psyc03->getOutput(), 0, usb, 1);
AudioControlSGTL5000 sgtl5000_1;
    
void setup() {
  Serial.begin(115200);
  
  while (!Serial && millis() < 2500); // wait for serial monitor

  psyc03->init();

  // Audio connections require memory to work.
  AudioMemory(40);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  
  // Starting sequence
  Serial.println("Ready!");
}

void loop() {
  psyc03->update();
}
