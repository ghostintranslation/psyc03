#ifndef Psyc03_h
#define Psyc03_h

#include "Motherboard.h"

/*
// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=65,34
AudioSynthWaveformSine   sine1;          //xy=68,86
AudioSynthWaveformSine   lfo;            //xy=71,146
AudioSynthWaveformModulated sine_fm1;        //xy=88,325
AudioSynthWaveformSineModulated sine_fm2;       //xy=103,393
AudioSynthWaveformSineModulated sine_fm3;       //xy=118,448
AudioAnalyzePeak         peak1;          //xy=156,205
AudioEffectEnvelope      envelope1;      //xy=191,38
AudioMixer4              mixer1;         //xy=252,148
AudioSynthWaveformDc     dc2;            //xy=257,513
AudioMixer4              mixer2;         //xy=259,451
AudioEffectEnvelope      envelope3;      //xy=393,513
AudioEffectEnvelope      envelope2;      //xy=395,456
AudioFilterStateVariable filter;         //xy=562,493
AudioOutputI2S           i2s1;           //xy=692,460
AudioOutputUSB           usb1;           //xy=697,516
AudioConnection          patchCord1(dc1, envelope1);
AudioConnection          patchCord2(sine1, 0, mixer1, 1);
AudioConnection          patchCord3(lfo, peak1);
AudioConnection          patchCord4(sine_fm1, 0, mixer2, 0);
AudioConnection          patchCord5(sine_fm2, 0, mixer2, 1);
AudioConnection          patchCord6(sine_fm3, 0, mixer2, 2);
AudioConnection          patchCord7(envelope1, 0, mixer1, 0);
AudioConnection          patchCord8(mixer1, 0, sine_fm1, 0);
AudioConnection          patchCord9(mixer1, sine_fm2);
AudioConnection          patchCord10(mixer1, sine_fm3);
AudioConnection          patchCord11(dc2, envelope3);
AudioConnection          patchCord12(mixer2, envelope2);
AudioConnection          patchCord13(envelope3, 0, filter, 1);
AudioConnection          patchCord14(envelope2, 0, filter, 0);
AudioConnection          patchCord15(filter, 0, i2s1, 0);
AudioConnection          patchCord16(filter, 0, i2s1, 1);
AudioConnection          patchCord17(filter, 0, usb1, 0);
AudioConnection          patchCord18(filter, 0, usb1, 1);
// GUItool: end automatically generated code

*/


/*
 * Synth
 */
class Psyc03{
  
  private:
    static Psyc03 *instance;
    Psyc03();
    
    AudioSynthWaveformDc        *dc1;
    AudioSynthWaveformSine      *sine1;
    AudioSynthWaveformSine      *lfo;
    AudioAnalyzePeak            *peak1;
    AudioEffectEnvelope         *envelope1;
    AudioSynthWaveformDc        *dc2;
    AudioSynthWaveformModulated *sine_fm1;
    AudioSynthWaveformModulated *sine_fm2;
    AudioSynthWaveformModulated *sine_fm3;
    AudioMixer4                 *mixer1;
    AudioMixer4                 *mixer2;
    AudioEffectEnvelope         *envelope3;
    AudioEffectEnvelope         *envelope2;
    AudioFilterStateVariable    *filter;
    AudioConnection* patchCords[15];
  
    // Output
    AudioMixer4 *output;

    // Motherboard
    Motherboard *device;

    // Params
    unsigned int tune = 30;
    float depth = 0;
    float speed = 0;
    float lfoPeak = 0;
    int fm = 400;
    int decay = 80;
    int attack = 2;
    float sweep = 0.2;
    int cutoff = 3000;
    float drumFilterRes = 4;
    byte shape = 0;
    
    byte shapeInputIndex = 0;
    byte tuneInputIndex = 1;
    byte sweepInputIndex = 2;
    byte fmInputIndex = 3;
    byte attackInputIndex = 4;
    byte decayInputIndex = 5;
    byte cutoffInputIndex = 6;
    byte speedInputIndex = 7;
    byte depthInputIndex = 8;
    
    byte updateMillis = 10;
    elapsedMillis clockUpdate;

    
  public:
    static Psyc03 *getInstance();
    void init();
    void stop();
    void update();
    AudioMixer4 * getOutput();

    // Callbacks
    static void onShapeChange(byte inputIndex, float value, int diffToPrevious);
    static void onTuneChange(byte inputIndex, float value, int diffToPrevious);
    static void onSweepChange(byte inputIndex, float value, int diffToPrevious);
    static void onFmChange(byte inputIndex, float value, int diffToPrevious);
    static void onAttackChange(byte inputIndex, float value, int diffToPrevious);
    static void onDecayChange(byte inputIndex, float value, int diffToPrevious);
    static void onCutoffChange(byte inputIndex, float value, int diffToPrevious);
    static void onSpeedChange(byte inputIndex, float value, int diffToPrevious);
    static void onDepthChange(byte inputIndex, float value, int diffToPrevious);
    // Midi callbacks
    static void onMidiNoteOn(byte channel, byte note, byte velocity);
    static void onMidiNoteOff(byte channel, byte note, byte velocity);
    static void onMidiShapeChange(byte channel, byte control, byte value);
    static void onMidiTuneChange(byte channel, byte control, byte value);
    static void onMidiSweepChange(byte channel, byte control, byte value);
    static void onMidiFmChange(byte channel, byte control, byte value);
    static void onMidiAttackChange(byte channel, byte control, byte value);
    static void onMidiDecayChange(byte channel, byte control, byte value);
    static void onMidiCutoffChange(byte channel, byte control, byte value);
    static void onMidiSpeedChange(byte channel, byte control, byte value);
    static void onMidiDepthChange(byte channel, byte control, byte value);
    
};

// Singleton pre init
Psyc03 * Psyc03::instance = nullptr;

/**
 * Constructor
 */
inline Psyc03::Psyc03(){
  this->peak1 = new AudioAnalyzePeak();

  this->lfo = new AudioSynthWaveformSine();
  this->lfo->amplitude(1);
  this->lfo->frequency(1);
  
  this->sine1 = new AudioSynthWaveformSine();
  this->sine1->amplitude(1);
  this->sine1->frequency(this->fm);
  
  this->sine_fm1 = new AudioSynthWaveformModulated();
  this->sine_fm1->begin(WAVEFORM_SINE);
  this->sine_fm1->amplitude(.4);
  this->sine_fm1->frequency(this->tune);
  this->sine_fm2 = new AudioSynthWaveformModulated();
  this->sine_fm2->begin(WAVEFORM_TRIANGLE);
  this->sine_fm2->amplitude(.4);
  this->sine_fm2->frequency(this->tune);
  this->sine_fm3 = new AudioSynthWaveformModulated();
  this->sine_fm3->begin(WAVEFORM_SQUARE);
  this->sine_fm3->amplitude(.2);
  this->sine_fm3->frequency(this->tune);
  
  this->dc1 = new AudioSynthWaveformDc();
  this->dc1->amplitude(1);
  
  this->envelope1 = new AudioEffectEnvelope();
  this->envelope1->attack(this->attack);
  this->envelope1->decay(this->decay); 
  this->envelope1->sustain(0);
  this->envelope1->hold(1);
  this->envelope1->release(1);
  
  this->envelope2 = new AudioEffectEnvelope();
  this->envelope2->attack(this->attack);
  this->envelope2->decay(this->decay); 
  this->envelope2->sustain(0);
  this->envelope2->hold(1);
  this->envelope2->release(1);

  this->envelope3 = new AudioEffectEnvelope();
  this->envelope3->attack(this->attack);
  this->envelope3->decay(this->decay); 
  this->envelope3->sustain(0);
  this->envelope3->hold(1);
  this->envelope3->release(1);

  this->dc2 = new AudioSynthWaveformDc();
  this->dc2->amplitude(1);
  
  this->filter = new AudioFilterStateVariable();
  this->filter->resonance(this->drumFilterRes);
  this->filter->frequency(this->cutoff);
  this->filter->octaveControl(2.5);

  this->mixer1 = new AudioMixer4();
  this->mixer1->gain(0, this->sweep);
  this->mixer1->gain(1, this->fm);

  this->mixer2 = new AudioMixer4();
  this->mixer2->gain(0, 1);
  this->mixer2->gain(1, 0);
  this->mixer2->gain(2, 0);
  
  this->device = device;

  this->output = new AudioMixer4();
  this->output->gain(0, 1 );
 
  this->patchCords[0] = new AudioConnection(*this->dc1, *this->envelope1);
  this->patchCords[1] = new AudioConnection(*this->sine1, 0, *this->mixer1, 1);
  this->patchCords[2] = new AudioConnection(*this->lfo, *this->peak1);
  this->patchCords[3] = new AudioConnection(*this->envelope1, 0, *this->mixer1, 0);
  this->patchCords[4] = new AudioConnection(*this->mixer1, 0, *this->sine_fm1, 0);
  this->patchCords[5] = new AudioConnection(*this->mixer1, 0, *this->sine_fm2, 0);
  this->patchCords[6] = new AudioConnection(*this->mixer1, 0, *this->sine_fm3, 0);
  this->patchCords[7] = new AudioConnection(*this->sine_fm1, 0, *this->mixer2, 0);
  this->patchCords[8] = new AudioConnection(*this->sine_fm2, 0, *this->mixer2, 1);
  this->patchCords[9] = new AudioConnection(*this->sine_fm3, 0, *this->mixer2, 2);
  this->patchCords[10] = new AudioConnection(*this->mixer2, *this->envelope2);
  this->patchCords[11] = new AudioConnection(*this->dc2, *this->envelope3);
  this->patchCords[12] = new AudioConnection(*this->envelope3, 0, *this->filter, 1);
  this->patchCords[13] = new AudioConnection(*this->envelope2, 0, *this->filter, 0);
  this->patchCords[14] = new AudioConnection(*this->filter, 0, *this->output, 0);
}

/**
 * Singleton instance
 */
inline Psyc03 *Psyc03::getInstance()    {
  if (!instance)
     instance = new Psyc03;
  return instance;
}

inline void Psyc03::init(){
  this->device = Motherboard::init(
    "PSYC03",
    {
      Potentiometer, Potentiometer, Potentiometer,
      Potentiometer, Potentiometer, Potentiometer,
      Potentiometer, Potentiometer, Potentiometer
    }
  );

  // Callbacks
  this->device->setHandlePotentiometerChange(0, onShapeChange);
  this->device->setHandlePotentiometerChange(1, onTuneChange);
  this->device->setHandlePotentiometerChange(2, onSweepChange);
  this->device->setHandlePotentiometerChange(3, onFmChange);
  this->device->setHandlePotentiometerChange(4, onAttackChange);
  this->device->setHandlePotentiometerChange(5, onDecayChange);
  this->device->setHandlePotentiometerChange(6, onCutoffChange);
  this->device->setHandlePotentiometerChange(7, onSpeedChange);
  this->device->setHandlePotentiometerChange(8, onDepthChange);

  // MIDI callbacks
  this->device->setHandleMidiNoteOn(onMidiNoteOn);
  this->device->setHandleMidiNoteOff(onMidiNoteOff);
  device->setHandleMidiControlChange(0, 0, "Shape", onMidiShapeChange);
  device->setHandleMidiControlChange(0, 1, "Tune", onMidiTuneChange);
  device->setHandleMidiControlChange(0, 2, "Sweep", onMidiSweepChange);
  device->setHandleMidiControlChange(0, 3, "FM", onMidiFmChange);
  device->setHandleMidiControlChange(0, 4, "Attack", onMidiAttackChange);
  device->setHandleMidiControlChange(0, 5, "Decay", onMidiDecayChange);
  device->setHandleMidiControlChange(0, 6, "Cutoff", onMidiCutoffChange);
  device->setHandleMidiControlChange(0, 7, "Speed", onMidiSpeedChange);
  device->setHandleMidiControlChange(0, 8, "Depth", onMidiDepthChange);

}

/**
 * Midi Note on
 */
inline void Psyc03::onMidiNoteOn(byte channel, byte note, byte velocity){
  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);

  getInstance()->sine_fm1->frequency(getInstance()->tune + freq); //lfoPeak*1000
  getInstance()->sine_fm2->frequency(getInstance()->tune + freq); //lfoPeak*1000
  getInstance()->sine_fm3->frequency(getInstance()->tune + freq); //lfoPeak*1000
  getInstance()->envelope1->noteOn();
  getInstance()->envelope2->noteOn();
  getInstance()->envelope3->noteOn();
  
  getInstance()->device->setLED(0, 1);
}

/**
 * Midi Note off
 */
inline void Psyc03::onMidiNoteOff(byte channel, byte note, byte velocity){
  getInstance()->device->setLED(0, 0);
}

/**
 * Return the audio output
 */
inline AudioMixer4 * Psyc03::getOutput(){
  return this->output;
}


/**
 * Update
 */
inline void Psyc03::update(){
  this->device->update();
  
  MIDI.read(this->device->getMidiChannel());
  usbMIDI.read(this->device->getMidiChannel());
  
  if(this->clockUpdate > this->updateMillis){
    // Filter folowwing the envelope
    if (this->peak1->available()) {
      this->lfoPeak = this->peak1->read();
      this->filter->frequency((float)this->cutoff + this->lfoPeak*2000);
    }
    
    this->clockUpdate = 0;
  }
}


/**
 * On Shape Change
 */
inline void Psyc03::onShapeChange(byte inputIndex, float value, int diffToPrevious){

  float mix = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    PI
  );

  float voice1Gain = constrain(cos(mix), 0, 1);
  float voice2Gain = constrain(cos(mix+1.5*PI), 0, 1);
  float voice3Gain = constrain(cos(mix+3*PI), 0, 1);

  getInstance()->mixer2->gain(0, voice1Gain);
  getInstance()->mixer2->gain(1, voice2Gain);
  getInstance()->mixer2->gain(2, voice3Gain);
}

/**
 * On MIDI Shape Change
 */
void Psyc03::onMidiShapeChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onShapeChange(control, mapValue, 255);
}

/**
 * On Tune Change
 */
inline void Psyc03::onTuneChange(byte inputIndex, float value, int diffToPrevious){
  // Tune
  unsigned int tune = map(
    value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    500
  );
    
  getInstance()->tune = tune;
}

/**
 * On MIDI Tune Change
 */
void Psyc03::onMidiTuneChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onTuneChange(control, mapValue, 255);
}

/**
 * On Sweep Change
 */
inline void Psyc03::onSweepChange(byte inputIndex, float value, int diffToPrevious){
  // Sweep
  float sweep = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    1
  );

  getInstance()->mixer1->gain(0, sweep);
}

/**
 * On MIDI Sweep Change
 */
void Psyc03::onMidiSweepChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onSweepChange(control, mapValue, 255);
}

/**
 * On FM Change
 */
inline void Psyc03::onFmChange(byte inputIndex, float value, int diffToPrevious){
  float fmLevel = map((float)value, 0, 1023, 0, .6);
  getInstance()->sine1->frequency(value);
  getInstance()->mixer1->gain(1, fmLevel);
}

/**
 * On MIDI FM Change
 */
void Psyc03::onMidiFmChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onFmChange(control, mapValue, 255);
}

/**
 * On Attack Change
 */
inline void Psyc03::onAttackChange(byte inputIndex, float value, int diffToPrevious){
  int attack = map(
    value,
    getInstance()->device->getAnalogMinValue(),
    getInstance()->device->getAnalogMaxValue(),
    2,
    500
  );
  
  getInstance()->envelope2->attack(attack);
  getInstance()->envelope3->attack(attack);
}

/**
 * On MIDI Attack Change
 */
void Psyc03::onMidiAttackChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onAttackChange(control, mapValue, 255);
}

/**
 * On Decay Change
 */
inline void Psyc03::onDecayChange(byte inputIndex, float value, int diffToPrevious){
  int decay = map(
    value,
    getInstance()->device->getAnalogMinValue(),
    getInstance()->device->getAnalogMaxValue(),
    0,
    1000
  );

  getInstance()->envelope1->decay(decay);
  getInstance()->envelope2->decay(decay);
  getInstance()->envelope3->decay(decay);
}

/**
 * On MIDI Decay Change
 */
void Psyc03::onMidiDecayChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onDecayChange(control, mapValue, 255);
}

/**
 * On Cutoff Change
 */
inline void Psyc03::onCutoffChange(byte inputIndex, float value, int diffToPrevious){
  int cutoff = map(
    value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    2000
  );
  
  getInstance()->cutoff = cutoff; 
}

/**
 * On MIDI Cutoff Change
 */
void Psyc03::onMidiCutoffChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onCutoffChange(control, mapValue, 255);
}

/**
 * On Speed Change
 */
inline void Psyc03::onSpeedChange(byte inputIndex, float value, int diffToPrevious){
  float speed = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    1
  );
    
  getInstance()->lfo->frequency(speed);
}

/**
 * On MIDI Speed Change
 */
void Psyc03::onMidiSpeedChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onSpeedChange(control, mapValue, 255);
}

/**
 * On Depth Change
 */
inline void Psyc03::onDepthChange(byte inputIndex, float value, int diffToPrevious){
  float depth = (float)map(
    (float)value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    1
  );
  
  getInstance()->lfo->amplitude(depth);
}

/**
 * On MIDI Depth Change
 */
void Psyc03::onMidiDepthChange(byte channel, byte control, byte value){
  unsigned int mapValue = map(
    value, 
    0,
    127,
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue()
  );
  
  getInstance()->onDepthChange(control, mapValue, 255);
}
#endif
