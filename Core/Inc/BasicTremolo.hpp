#ifndef __BASICTREMOLO_HPP__
#define __BASICTREMOLO_HPP__


#include <cmath>

//Define the enums for setting maybe?


class TREMBlock {


  float depth; //0..100
  float rate;
  float levOffset = 0; //init level
  float LFOstep = 0;
  float LFOstepShifted1 = 0.25;
  float LFOstepShifted2 = 0.75;//init timestep

  float Tau = 1/48000.0;
  float LFOdepth;

  float LFOval;
  float LFOvalShifted1;
  float LFOvalShifted2;


  float saw_val;
  float saw_val_shifted;
  float saw_val_shifted_2;

  float saw_val_smoothed;
  float saw_val_shift1_smoothed;
  float saw_val_shift2_smoothed;

  float lfo_step = 0;
  float lfo_step_shifted;
  float lfo_step_shifted_2;

  float square_val;
  float square_val_shifted;
  float square_val_shifted_2;

  float square_val_smoothed;
  float square_val_shift1_smoothed;
  float square_val_shift2_smoothed;

  float tri_val = 0;
  float tri_val_shifted;
  float tri_val_shifted_2;

  float square_out;
  float square_shift_1;
  float square_shift_2;

  float sin_out;
  float sin_shift_invert;
  float sin_shift_non_invert;

  float saw_out;
  float saw_shift_1;
  float saw_shift_2;

  float tri_out;
  float tri_shift_1;
  float tri_shift_2;






//access specifier
public:
  // constructor built by compiler
  TREMBlock();

  void process(float val);

  void setRate(float TargetRate);

  void setDepth(float TargetDepth);

  float sine_lfo_out();

  float sine_lfo_shift_out();

  float sine_lfo_shift2_out();

  float saw_lfo_out();

  float saw_lfo_shift_out();

  float saw_lfo_shift2_out();

  float tri_lfo_out();

  float tri_lfo_shift_out();

  float tri_lfo_shift2_out();

  float square_lfo_out();

  float square_lfo_shift_out();

  float square_lfo_shift2_out();



 };

#endif
