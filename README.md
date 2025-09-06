# MULTI-FX-UNIT

This is a project for the STM32f769i-Disco development board completed for my Digital Audio Systems and Processing Module. The code is messy, and contains alot of junk, but I've decided to share it as it a fully functioning system that still sounds very cool, especially the Tremolo and Reverb. A much better developed and greatly improved version of the Reverb alogirithim (and better example of my programming skills!) can be found in this repo: https://github.com/reubenwbetts/BYC-VERB-JUCE

It tuns a Reverb, EQ and Tremolo, with the FX selectable with the GPIO buttons. Each FX's parameters is controlled via the LCD/Touchscreen, with the parameter list (and it's effects) shown below.

**Tremolo**

Controls for the Tremolo are as follows:
- LFO Shape (selectable waveforms: sine, triangle, square and saw)
- Pan (phase shifts the left and right channels waveforms to create an Autopan effect)
- Depth (intensity of the effect)
- Freq (speed of effect)

**Reverb**

Controls for the Reverb are as follows:
- Blend (simple wet/dry mix)
- Decay (length of the Reverb tail)
- Damping (reduces high-frequency decay)
- Pre-Delay (delays the wet signal by a certain amount)

**EQ**

- LF (low shelf gain)
- LMF (low mid bell gain)
- HMF (high mid bell gain)
- HF (high shelf gain)
  
