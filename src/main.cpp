#include "daisy_versio.h"
#include "daisysp.h"
#include <string>

daisy::DaisyVersio hw;

// bitcrush effect
daisysp::Decimator decimator_l;
daisysp::Decimator decimator_r;

static float kval;

// This runs at a fixed rate, to prepare audio samples
void callback(daisy::AudioHandle::InterleavingInputBuffer in,
              daisy::AudioHandle::InterleavingOutputBuffer out,
              size_t size) {
  // Audio is interleaved stereo by default
  for (size_t i = 0; i < size; i += 2) {
    out[i] = decimator_l.Process(in[i]); // left
    out[i + 1] = decimator_r.Process(in[i + 1]); // right
  }
}

int main() {
  // Initialize Versio hardware and start audio, ADC
  hw.Init();

  decimator_l.Init();
  decimator_r.Init();

  kval = 0.f;

  hw.StartAudio(callback);
  hw.StartAdc();

  while (true) {
    hw.ProcessAnalogControls(); // Normalize CV inputs
    hw.UpdateExample(); // Control the LED colors using the knobs and gate inputs
    hw.UpdateLeds();

    decimator_l.SetBitcrushFactor(hw.GetKnobValue(daisy::DaisyVersio::KNOB_0));
    decimator_l.SetDownsampleFactor(hw.GetKnobValue(daisy::DaisyVersio::KNOB_1));

    decimator_r.SetBitcrushFactor(hw.GetKnobValue(daisy::DaisyVersio::KNOB_2));
    decimator_r.SetDownsampleFactor(hw.GetKnobValue(daisy::DaisyVersio::KNOB_3));

    kval = hw.GetKnobValue(daisy::DaisyVersio::KNOB_6);
  }
}