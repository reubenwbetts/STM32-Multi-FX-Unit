/*
 * BasicTremolo.cpp
 *
 *  Created on: 11 Jul 2023
 *      Author: Steve
 */

#include "BasicTremolo.hpp"

#include <cmath>

TREMBlock::TREMBlock()
  {
    depth = 0.5; //50% depth
    rate = 1.0;   //1Hz
}

//inside class definition
void TREMBlock::process(float val){
    // y(n) = x(n) * ( (1-d) + d*mod) )
	//LFOdepth = depth; //so if depth is 0..100, then will go from 0..0.5 depending on UI,

	//this could be removed, either way need to limit depth to 0..1
    levOffset = 1.0-depth;

    if (levOffset>=1)
      levOffset = 1.0;

    if (levOffset<=0) //just in case
	  levOffset=0.0;

    //rate needs to be in integers of 2*M_PI to ensure
    //one complete f cycle.

    if (rate<=1) rate=1; //just trap as we don't want mute


    // Sine Wave LFO -------------------------------------

    LFOval = depth*sin(2*M_PI*(int)rate*LFOstep)+levOffset; 					// Same in each ears
    LFOvalShifted1 = depth*sin(2*M_PI*(int)rate*LFOstepShifted1)+levOffset; 	// Stereo offset from the other line
    LFOvalShifted2 = depth*sin(2*M_PI*(int)rate*LFOstepShifted2)+levOffset; 	// Stereo offset from the other line

    sin_out = LFOval * val;
    sin_shift_invert = LFOvalShifted2*val;
    sin_shift_non_invert = LFOvalShifted1*val;

    LFOstep=(LFOstep+Tau);
    LFOstepShifted1=(LFOstepShifted1+Tau);
    LFOstepShifted2=(LFOstepShifted2+Tau);

    if(LFOstep>=1)LFOstep=0;
    if(LFOstepShifted1>=1)LFOstepShifted1=0;
    if(LFOstepShifted2>=1)LFOstepShifted2=0;

    // Saw Wave LFO ----------------------------------

    lfo_step += Tau * rate;
    lfo_step_shifted = lfo_step + 0.25;
    lfo_step_shifted_2 = lfo_step + 0.75;

    if(lfo_step >= 1) lfo_step -= 1.0;
    if(lfo_step_shifted >= 1) lfo_step_shifted -= 1.0;
    if(lfo_step_shifted_2 >= 1) lfo_step_shifted_2 -= 1.0;

    saw_val = depth * lfo_step + levOffset;
    saw_val_shifted = depth * lfo_step_shifted + levOffset;
    saw_val_shifted_2 = depth * lfo_step_shifted_2 + levOffset;

    // Single pole IIR low pass for smoothing LFO outs

    saw_val_smoothed = (1-0.1) * saw_val_smoothed + 0.1 * saw_val;
    saw_val_shift1_smoothed = (1-0.1) * saw_val_shift1_smoothed + 0.1 * saw_val_shifted;
    saw_val_shift2_smoothed = (1-0.1) * saw_val_shift2_smoothed + 0.1 * saw_val_shifted_2;

    saw_out = saw_val_smoothed * val;
    saw_shift_1 = saw_val_shift1_smoothed * val;
    saw_shift_2 = saw_val_shift2_smoothed * val;

    // Square Wave LFO -------------------------------

    if(lfo_step > 0.5)square_val = 1.0 ;
    	else if (lfo_step <= 0.5) square_val = 0.0 ;
    if(lfo_step_shifted > 0.5) square_val_shifted = 1.0 ;
    	else if (lfo_step_shifted <= 0.5) square_val_shifted = 0.0 ;
    if(lfo_step_shifted_2 > 0.5)square_val_shifted_2 = 1.0 ;
    	else if (lfo_step_shifted_2 <= 0.5)square_val_shifted_2 = 0.0 ;

    square_val = depth * square_val + levOffset;
    square_val_shifted = depth * square_val_shifted + levOffset;
    square_val_shifted_2 = depth * square_val_shifted_2 + levOffset;

    square_val_smoothed = (1-0.2) * square_val_smoothed + 0.2 * square_val;
    square_val_shift1_smoothed = (1-0.2) * square_val_shift1_smoothed + 0.2 * square_val_shifted;
    square_val_shift2_smoothed = (1-0.2) * square_val_shift2_smoothed + 0.2 * square_val_shifted_2;

    square_out = square_val_smoothed * val;
    square_shift_1 = square_val_shift1_smoothed * val;
    square_shift_2 = square_val_shift2_smoothed * val;

    // Triangle Wave LFO -------------------------------

    tri_val = 2.0 * (1.0 - fabsf(2.0 * lfo_step - 1.0)) - 1.0;
    if (lfo_step == 0.5) tri_val = 0.0;

    tri_val_shifted = 2.0 * (1.0 - fabsf(2.0 * lfo_step_shifted - 1.0)) - 1.0;
    if (lfo_step_shifted == 0.5) tri_val_shifted = 0.0;

    tri_val_shifted_2 = 2.0 * (1.0 - fabsf(2.0 * lfo_step_shifted_2 - 1.0)) - 1.0;
    if (lfo_step_shifted_2 == 0.5) tri_val_shifted_2 = 0.0;

    // avoids clicks from triangle start and end not aligning


    tri_val = tri_val*depth+levOffset;
    tri_val_shifted = tri_val_shifted*depth+levOffset;
    tri_val_shifted_2 = tri_val_shifted_2*depth+levOffset;

    tri_out = tri_val * val;
    tri_shift_1 = tri_val_shifted * val;
    tri_shift_2 = tri_val_shifted_2 * val;

    //return processedSample;
}


float TREMBlock::saw_lfo_out(){
	return saw_out;
}

float TREMBlock::saw_lfo_shift_out(){
	return saw_shift_1;
}

float TREMBlock::saw_lfo_shift2_out(){
	return saw_shift_2;
}

float TREMBlock::tri_lfo_out(){
	return tri_out;
}

float TREMBlock::tri_lfo_shift_out(){
	return tri_shift_1;
}

float TREMBlock::tri_lfo_shift2_out(){
	return tri_shift_2;
}

float TREMBlock::square_lfo_out(){
	return square_out;
}

float TREMBlock::square_lfo_shift_out(){
	return square_shift_1;
}

float TREMBlock::square_lfo_shift2_out(){
	return square_shift_2;
}

float TREMBlock::sine_lfo_out(){
	return sin_out;
}

float TREMBlock::sine_lfo_shift_out(){
	return sin_shift_invert;
}

float TREMBlock::sine_lfo_shift2_out(){
	return sin_shift_non_invert;
}

void TREMBlock::setRate(float TargetRate){
	rate = TargetRate * 5.0;
}

void TREMBlock::setDepth(float TargetDepth){
	 depth = TargetDepth;
 }





