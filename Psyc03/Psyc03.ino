/*
 __    _  _____   ___      ___ _  _     __    _ ______ _    
/__|_|/ \(_  |     | |\|    | |_)|_||\|(_ |  |_| |  | / \|\|
\_|| |\_/__) |    _|_| |    | | \| || |__)|__| | | _|_\_/| |

If you enjoy my work and music please consider donating.

https://www.ghostintranslation.com/
https://ghostintranslation.bandcamp.com/
https://www.instagram.com/ghostintranslation/
https://www.youtube.com/channel/UCcyUTGTM-hGLIz4194Inxyw
https://github.com/ghostintranslation
*/

#include <Audio.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE(); // MIDI library init

#include "Motherboard9.h"
#include "Psyc03.h"

// 0 = empty, 1 = button, 2 = potentiometer, 3 = encoder
byte controls[9] = {2,2,2, 2,2,2, 2,2,2};
Motherboard9 device(controls);

Psyc03 psyc03(&device);

AudioOutputI2S  i2s2;
AudioConnection patchCord1(*psyc03.getOutput(), 0, i2s2, 0);
AudioConnection patchCord2(*psyc03.getOutput(), 0, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1;
    
void setup() {
  Serial.begin(115200);
  
  device.init();
  
  MIDI.setHandleNoteOn(onNoteOn);
  MIDI.setHandleNoteOff(onNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  
  usbMIDI.setHandleNoteOn(onNoteOn);
  usbMIDI.setHandleNoteOff(onNoteOff);

  // Audio connections require memory to work.
  AudioMemory(40);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.1);
  
  while (!Serial && millis() < 2500); // wait for serial monitor

  // Starting sequence
  Serial.println("Ready!");
}

void loop() {
  device.update();
  
  MIDI.read();
  usbMIDI.read();
  
  psyc03.update();
}


// TODO: The following should be handled by Motherboard9

/**
 * Midi note on callback
 */
void onNoteOn(byte channel, byte note, byte velocity) {
  psyc03.noteOn(note);
  device.setDisplay(0, 1);
}

/**
 * Midi note off callback
 */
void onNoteOff(byte channel, byte note, byte velocity) {
  psyc03.noteOff(note);
  device.setDisplay(0, 0);
}
