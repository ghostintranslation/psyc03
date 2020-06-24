#ifndef Psyc03_h
#define Psyc03_h

#include <Audio.h>

#include "Motherboard9.h"

/*
// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=70,83
AudioSynthWaveformSine   sine1;          //xy=73,135
AudioSynthWaveformSine   lfo;          //xy=76,195
AudioAnalyzePeak         peak1;          //xy=161,254
AudioEffectEnvelope      envelope1;      //xy=196,87
AudioSynthWaveformDc     dc2;            //xy=197,427
AudioSynthWaveformModulated sine_fm;        //xy=205,363
AudioMixer4              mixer1;         //xy=257,197
AudioEffectEnvelope      envelope3;      //xy=347,423
AudioEffectEnvelope      envelope2;      //xy=349,366
AudioFilterStateVariable filter;        //xy=516,403
AudioOutputI2S           i2s1;           //xy=735,370
AudioOutputUSB           usb1;           //xy=740,426
AudioConnection          patchCord1(dc1, envelope1);
AudioConnection          patchCord2(sine1, 0, mixer1, 1);
AudioConnection          patchCord3(lfo, peak1);
AudioConnection          patchCord4(envelope1, 0, mixer1, 0);
AudioConnection          patchCord5(dc2, envelope3);
AudioConnection          patchCord6(sine_fm, envelope2);
AudioConnection          patchCord7(mixer1, 0, sine_fm, 0);
AudioConnection          patchCord8(envelope3, 0, filter, 1);
AudioConnection          patchCord9(envelope2, 0, filter, 0);
AudioConnection          patchCord10(filter, 0, i2s1, 0);
AudioConnection          patchCord11(filter, 0, i2s1, 1);
AudioConnection          patchCord12(filter, 0, usb1, 0);
AudioConnection          patchCord13(filter, 0, usb1, 1);
// GUItool: end automatically generated code
*/


/*
 * Synth
 */
class Psyc03{
  
  private:
    AudioSynthWaveformDc        *dc1;
    AudioSynthWaveformSine      *sine1;
    AudioSynthWaveformSine      *lfo;
    AudioAnalyzePeak            *peak1;
    AudioEffectEnvelope         *envelope1;
    AudioSynthWaveformDc        *dc2;
    AudioSynthWaveformModulated *sine_fm;
    AudioMixer4                 *mixer1;
    AudioEffectEnvelope         *envelope3;
    AudioEffectEnvelope         *envelope2;
    AudioFilterStateVariable    *filter;
    AudioConnection* patchCords[10];
  
    // Output
    AudioMixer4 *output;

    // Motherboard
    Motherboard9 *device;

    // Params
    unsigned int tune = 30;
    float depth = 0;
    float speed = 0;
    float lfoPeak = 0;
    int fm = 400;
    int decay = 80;
    int attack = 1;
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
    Psyc03(Motherboard9 *device);

    void noteOn(byte midiNote);
    void noteOff(byte midiNote);
    void stop();
    void update();
    AudioMixer4 * getOutput();
};

/**
 * Constructor
 */
inline Psyc03::Psyc03(Motherboard9 *device){
  this->peak1 = new AudioAnalyzePeak();

  this->lfo = new AudioSynthWaveformSine();
  this->lfo->amplitude(1);
  this->lfo->frequency(1);
  
  this->sine1 = new AudioSynthWaveformSine();
  this->sine1->amplitude(1);
  this->sine1->frequency(this->fm);
  
  this->sine_fm = new AudioSynthWaveformModulated();
  this->sine_fm->begin(0);
  this->sine_fm->amplitude(.2);
  this->sine_fm->frequency(this->tune);
  
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

  this->device = device;

  this->output = new AudioMixer4();
  this->output->gain(0, 1 );
 
  this->patchCords[0] = new AudioConnection(*this->dc1, *this->envelope1);
  this->patchCords[1] = new AudioConnection(*this->sine1, 0, *this->mixer1, 1);
  this->patchCords[2] = new AudioConnection(*this->lfo, *this->peak1);
  this->patchCords[3] = new AudioConnection(*this->envelope1, 0, *this->mixer1, 0);
  this->patchCords[4] = new AudioConnection(*this->dc2, *this->envelope3);
  this->patchCords[5] = new AudioConnection(*this->sine_fm, *this->envelope2);
  this->patchCords[6] = new AudioConnection(*this->mixer1, 0, *this->sine_fm, 1);
  this->patchCords[7] = new AudioConnection(*this->envelope3, 0, *this->filter, 1);
  this->patchCords[8] = new AudioConnection(*this->envelope2, 0, *this->filter, 0);
  this->patchCords[9] = new AudioConnection(*this->filter, 0, *this->output, 0);
}


/**
 * Note on
 */
inline void Psyc03::noteOn(byte note){
  float freq = 440.0 * powf(2.0, (float)(note - 69) * 0.08333333);

  this->sine_fm->frequency(this->tune + freq); //lfoPeak*1000
  this->envelope1->noteOn();
  this->envelope2->noteOn();
  this->envelope3->noteOn();
}

/**
 * Note off
 */
inline void Psyc03::noteOff(byte note){
 
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
  if(this->clockUpdate > this->updateMillis){
   
    // Shape
    byte shape = map(
      this->device->getInput(
      this->shapeInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      2
    );
    
    if(this->shape != shape){
      this->shape = shape;
      this->sine_fm->begin(shape);
    } 

    // Tune
    unsigned int tune = (float)map(
      (float)this->device->getInput(
      this->tuneInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      500
    );
    
    if(this->tune != tune){
      this->tune = tune;
    } 

    // Sweep
    float sweep = (float)map(
      (float)this->device->getInput(
      this->sweepInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      1
    );
    
    if(this->sweep != sweep){
      this->sweep = sweep;
      this->mixer1->gain(0, sweep);
    } 
  
    // FM
    int fm = this->device->getInput(this->fmInputIndex);
    if(this->fm != fm){
      this->fm = fm;
      float fmLevel = map((float)fm, 0, 1023, 0, .6);
      this->sine1->frequency(fm);
      this->mixer1->gain(1, fmLevel);
    }
    
    // Attack
    int attack = map(
      this->device->getInput(this->attackInputIndex),
      this->device->getAnalogMinValue(),
      this->device->getAnalogMaxValue(),
      0,
      500
    );
    
    if(this->attack != attack){
      this->attack = attack;
      this->envelope2->attack(attack);
      this->envelope3->attack(attack);
    }
  
    // Decay
    int decay = map(
      this->device->getInput(this->decayInputIndex),
      this->device->getAnalogMinValue(),
      this->device->getAnalogMaxValue(),
      0,
      500
    );
  
    if(this->decay != decay){
      this->decay = decay;
      this->envelope1->decay(decay);
      this->envelope2->decay(decay);
      this->envelope3->decay(decay);
    }

    // Cutoff
    int cutoff = map(
      this->device->getInput(
      this->cutoffInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      2000
    );
    
    if(this->cutoff != cutoff){
      this->cutoff = cutoff;
    } 

    // Speed
    float speed = (float)map(
      (float)this->device->getInput(
      this->speedInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      10
    );
    
    if(this->speed != speed){
      this->speed = speed;
      this->lfo->frequency(speed);
    } 

    // Depth
    float depth = (float)map(
      (float)this->device->getInput(
      this->depthInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      1
    );
    
    if(this->depth != depth){
      this->depth = depth;
      this->lfo->amplitude(depth);
    } 

    // Filter folowwing the envelope
    if (this->peak1->available()) {
      this->lfoPeak = this->peak1->read();
      this->filter->frequency((float)this->cutoff + this->lfoPeak*2000);
    }
    
    this->clockUpdate = 0;
  }
}
#endif
