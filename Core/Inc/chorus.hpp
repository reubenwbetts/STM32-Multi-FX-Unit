/*
 * chorus.hpp
 *
 *  Created on: Apr 22, 2025
 *      Author: admin
 */



class chorus{
public:

	chorus(){
		depth = 20.0;
		rate_1 = 1.0;
		rate_2 = 0.5;
		rate_3 = 0.4;

	}
	void set_depth(float depth_val){
		depth = depth_val;
	}

	void set_rate(float rate_val_1, float rate_val_2, float rate_val_3){
		rate_1 = rate_val_1;
		rate_2 = rate_val_2;
		rate_3 = rate_val_3;
	}

	void set_feedback(float feedback_val){
		fb = feedback_val;

	}

	float process(float input){

		//LFO's ---------------------------------------
		float levOffset = 1.0-depth;

		if (levOffset>=1)
		    levOffset = 1.0;

		if (levOffset<=0)
			levOffset=0.0;

		LFO_1_step=(LFO_1_step+tau);

		if(LFO_1_step>=1){
			LFO_1_step=0;
			 target_1 = rand()%100;
			 target_2 = rand()%100;
			 target_3 = rand()%100;


		}

		if (LFO_1_val < target_1) LFO_1_val++;

		else if(LFO_1_val > target_1) LFO_1_val--;
		else if(LFO_1_val == target_1){;}

		if (LFO_2_val < target_2) LFO_2_val++;
		else if(LFO_2_val > target_2) LFO_2_val--;
		else if(LFO_2_val == target_2){;}

		if (LFO_3_val < target_3) LFO_3_val++;
		else if(LFO_3_val > target_3) LFO_3_val--;
		else if(LFO_3_val == target_3){;}

		// Chorus -------------------------------------

		int read_idx_1 = buffer_write_idx - tap_1_delay + LFO_1_val;
		int read_idx_2 = buffer_write_idx - tap_2_delay + LFO_2_val;
		int read_idx_3 = buffer_write_idx - tap_3_delay + LFO_3_val;

		if (read_idx_1 < 0){
			read_idx_1 += buffer_size;
		}
		if (read_idx_2 < 0){
			read_idx_2 += buffer_size;
		}
		if (read_idx_3 < 0){
			read_idx_3 += buffer_size;
		}

		float tap_1 = buffer[read_idx_1] * 0.33;
		float tap_2 = buffer[read_idx_2] * 0.33;
		float tap_3 = buffer[read_idx_3] * 0.33;

		float output = input + (tap_1 + tap_2 + tap_3);

		buffer[buffer_write_idx] = input;

	    buffer_write_idx = (buffer_write_idx + 1) % buffer_size;

	    // Output -------------------------------------

	    return output;

	}
private:

float depth;
float rate_1;
float rate_2;
float rate_3;
float fb;

uint8_t tap_1_delay = 100;
uint8_t tap_2_delay = 73;
uint8_t tap_3_delay = 86;
uint8_t buffer_write_idx = 0;
float buffer[2100];
uint8_t buffer_size = 2100;
float LFO_1_val = 1.0;
float LFO_2_val = 1.0;
float LFO_3_val = 1.0;

float LFO_1_val_filt = 1.0;

float LF0_2_val_filt = 1.0;
float LF0_3_val_filt = 1.0;
float LFO_1_step = 0.0;

int target_1 = 0.0;
int target_2 = 0.0;
int target_3 = 0.0;

float LFO_2_step = 0.0;

float LFO_3_step = 0.0;

float tau = 1/48000.0;



};




