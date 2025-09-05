/*
 * AudiProcess.cpp
 *
 *  Created on: 11 Jul 2023
 *      Author: Steve
 */

#include "all_pass.hpp"
#include "AudioProcess.hpp" //This interface
#include "BasicTremolo.hpp" //Time based basic tremolo
#include "GainProcess.hpp"
#include "svf_lpf.hpp"
#include "3_band_eq.hpp" //need to declare as object then test!!!!!!
#include "early_diffusion.hpp"
#include "late_diffusion.hpp"
#include "late_diffusion_test.hpp"
#include "late_diffusion_test2.hpp"
#include "chorus.hpp"

#include <stdio.h>


TREMBlock tremolo_L; //
TREMBlock tremolo_R; //

basic_eq eq_L;
basic_eq eq_R;

// was having stack overflow issues so moved the reverb objects to the heap
early_diffusion* early_diffuse = new early_diffusion();
late_diffuse_tank_2* late_diffuse = new late_diffuse_tank_2();

const float INT16_TO_FLOAT = 1.0f / 32768.0f;

float sample_rate = 48000.0;
float timeStep = 1/48000.0;

float verb_wet = 0.3;
float verb_dry = 0.7;
float tank_2_out = 0.0;
float verb_gain = 1.0;
float trem_invert_bd = 1.0;
float trem_invert_bw = 0.0;
uint8_t trem_shape = 0;
uint16_t timep = 0;
uint16_t previousTimep = 0;

bool verb_flag = 0;
bool trem_flag = 0;

chorus chorus_L;

chorus chorus_R;






void UpdateObjects(uint8_t idx, uint16_t user_x, uint16_t user_y){
	/*
	 *  Reverb coefficient update function - idx value corresponds to slider position on screen:
	 *  idx == 1 - decay slider
	 *  idx == 2 - damping
	 *  idx == 3 - dry/wet
	 *  idx == 4 - pre-delay
	 *  idx != 1-4 - ends function
	*/


	 if(idx == 1){
		 late_diffuse->set_decay(coeffOne);
		 printf("Setting Decay");
		 printf("\n");
	 }
	 else if(idx == 2){
		 late_diffuse->set_damp(coeffOne);
		 early_diffuse->set_bandwidth(coeffOne);
		 printf("Setting damping");
		 printf("\n");
	 }

	 else if(idx == 3){
		verb_wet = coeffOne;
		verb_dry = -verb_wet + 1;
		 printf("Setting blend");
		 printf("\n");
	 }

	 else if(idx == 4){
		early_diffuse->set_pre_delay(coeffOne);
		 printf("Setting pre delay");
		 printf("\n");
	 }

	 else if(idx == 5){
		 eq_L.set_high_shelf_gain(coeffOne);
		 eq_R.set_high_shelf_gain(coeffOne);
		 printf("Setting high shelf");
		 printf("\n");
	 }

	 else if(idx == 6){
		 eq_L.set_high_mid_bell_gain(coeffOne);
		 eq_R.set_high_mid_bell_gain(coeffOne);
		 printf("Setting high mid bell");
		 printf("\n");
	 }

	 else if(idx == 7){
		 eq_L.set_low_mid_bell_gain(coeffOne);
		 eq_R.set_low_mid_bell_gain(coeffOne);
		 printf("Setting low mid bell");
		 printf("\n");
	 }

	 else if(idx == 8){
		 eq_L.set_low_shelf_gain(coeffOne);
		 eq_R.set_low_shelf_gain(coeffOne);
		 printf("Setting low shef");
		 printf("\n");
	 }

	 else if(idx == 9){
		 tremolo_L.setRate(coeffOne);
		 tremolo_R.setRate(coeffOne);
		 printf("Setting trem rate");
		 printf("\n");
	 }

	 else if(idx == 10){
		 tremolo_L.setDepth(coeffOne);
		 tremolo_R.setDepth(coeffOne);
		 printf("setting trem depth");
		 printf("\n");
	 }

	 else if(idx == 11){
		 trem_invert_bw = coeffOne;
		 trem_invert_bd = (coeffOne *-1)+1.0;
		 printf("setting trem stereo");
		 printf("\n");
	 }

	 else if(idx == 12){
		 if(user_y < 200 && user_y > 150) trem_shape = 0;
		 if(user_y < 275 && user_y > 225) trem_shape = 1;
		 if(user_y < 350 && user_y > 300) trem_shape = 2;
		 if(user_y < 425 && user_y > 375) trem_shape = 3;


		 printf("setting trem waveform");
		 printf("\n");
	 }




	 else{return;}

}

//Main CPP based audio processing loop

void AudioProcess(int16_t *pbuffer1, int16_t *pbuffer2, uint16_t BlockSize, uint8_t page_idx){

	// L R L R ..Recall
	/*
	 *  * Int16  Int16 Int16  Iint16
 	  * This allows transferral of varying sizes of data
 	  * In our case
 	  * L - 1st Int16
 	  * -
 	  * R   3rd Int16
 	  * -
 	  * L - 4th Int16
	  * Results in a L float block of 256, Hence blockSize/4
	 */

    // Tremolo


	for (uint16_t i = 0; i < BlockSize; i+=4){ //hop over right bytes because we will process in twos

		// Input for processing loop

    	float audio_in_L = (INT16_TO_FLOAT * pbuffer2[i]);
    	float audio_in_R = (INT16_TO_FLOAT * pbuffer2[i+2]);
    	float audio_out_L;
       	float audio_out_R;

    	// Tremolo processes and outputs ---------------------------------

    	if (page_idx == 0){

    	// Reverb processes ----------------------------------------------
    	float reverb_in_mono = (audio_in_L + audio_in_R)*0.5;

    	float reverb_sig = early_diffuse->process(reverb_in_mono);
	   	late_diffuse->process(reverb_sig);

      	// Reverb outputs ------------------------------------------------
   	   	float reverb_out_L = late_diffuse->out_L();
      	float reverb_out_R = late_diffuse->out_R();

      	//Reverb wet/dry blend
   	   	audio_out_L = (reverb_out_L * verb_wet + audio_in_L * verb_dry); // wet/dry
       	audio_out_R = (reverb_out_R * verb_wet + audio_in_R * verb_dry); // wet/dry
    	}
    	else if (page_idx == 4)
    	{// EQ process and outputs ----------------------------------------
    	audio_out_L = eq_L.process(audio_in_L);
    	audio_out_R = eq_R.process(audio_in_R);
    	}
    	else if(page_idx == 8){

    		tremolo_L.process(audio_in_L);
    		tremolo_R.process(audio_in_R);

    		switch(trem_shape){

    		case 0:
        		audio_out_L = (tremolo_L.tri_lfo_shift_out()*trem_invert_bw) + (tremolo_L.tri_lfo_out()* trem_invert_bd);
        		audio_out_R = (tremolo_R.tri_lfo_shift2_out()*trem_invert_bw) + (tremolo_R.tri_lfo_out()* trem_invert_bd);
        		break;
       		case 1:
       			audio_out_L = (tremolo_L.saw_lfo_shift_out()*trem_invert_bw) + (tremolo_L.saw_lfo_out()* trem_invert_bd);
       			audio_out_R = (tremolo_R.saw_lfo_shift2_out()*trem_invert_bw) + (tremolo_R.saw_lfo_out()* trem_invert_bd);
       			break;
       		case 2:
       			audio_out_L = (tremolo_L.square_lfo_shift_out()*trem_invert_bw) + (tremolo_L.square_lfo_out()* trem_invert_bd);
       			audio_out_R = (tremolo_R.square_lfo_shift2_out()*trem_invert_bw) + (tremolo_R.square_lfo_out()* trem_invert_bd);
       			break;
       		case 3:
        		audio_out_L = (tremolo_L.sine_lfo_shift_out()*trem_invert_bw) + (tremolo_L.sine_lfo_out()* trem_invert_bd);
       			audio_out_R = (tremolo_R.sine_lfo_shift2_out()*trem_invert_bw) + (tremolo_R.sine_lfo_out()* trem_invert_bd);
       			break;
    		}
        }

    	pbuffer1[i] = (int16_t)(audio_out_L*32768.0f); //convert back
    	pbuffer1[i+2] = (int16_t)(audio_out_R*32768.0f); //convert back

}


}






