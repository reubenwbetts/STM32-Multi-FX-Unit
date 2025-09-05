/*
 * late_diffusion.hpp
 *
 *  Created on: Apr 19, 2025
 *      Author: admin
 */

#ifndef INC_LATE_DIFFUSION_HPP_
#define INC_LATE_DIFFUSION_HPP_

class late_diffusion{

public:

	float process_test(float input)
	{
		return input;
	}

	float process (float input_1)
	{

		// TANK 1 ===========================================

		//float tank_1_in = input_1;

		// APF1 -----------------------------------------

		int delay_1 = static_cast<int>(inv_apf1_delay);

		int read_idx_1 = inv_apf1_write_idx - delay_1;
		if (read_idx_1 < 0){
			read_idx_1 += inv_apf1_size;
		}

		float delayed_1 = inv_apf1[read_idx_1];

		float inv_apf1_out = decay_diffusion_1 * input_1 + delayed_1;

		inv_apf1[inv_apf1_write_idx] = -decay_diffusion_1 * inv_apf1_out + input_1;

		inv_apf1_write_idx = (inv_apf1_write_idx + 1) % inv_apf1_size;

		return input_1;

		// DELAY LINE 1 ----------------------------------

		int delay_2 = static_cast<int>(delay_line_1_delay);

		int read_idx_2 = delay_line_1_write_idx - delay_2;

		if (read_idx_2 < 0){
			read_idx_2 += delay_line_1_size;
		}

		float delayed_2 = delay_line_1[read_idx_2];

		float delay_line_1_out = delayed_2;

		delay_line_1[delay_line_1_write_idx] = inv_apf1_out;

		delay_line_1_write_idx = (delay_line_1_write_idx + 1) % delay_line_1_size;

		//return delay_line_1_out;

		// DAMPING FILTER ----------------------------

		float sum_in = damp_factor * damp_filt1_delay + delay_line_1_out; // prevout = out

		damp_filt1_delay = sum_in;

		// DECAY CONTROL 1 -------------------------------

		float damp_1_out = sum_in * decay;

		// APF NON INVERTING 1 -----------------------

		int delay_3 = static_cast<int>(apf1_delay);

		int read_idx_3 = apf1_write_idx - delay_3;
		if (read_idx_3 < 0){
			read_idx_3 += apf1_size;
		}

		float delayed_3 = apf1[read_idx_3];

		float apf1_out = -decay_diffusion_2 * damp_1_out + delayed_3;

		apf1[apf1_write_idx] = damp_1_out + decay_diffusion_2 * apf1_out;

		apf1_write_idx = (apf1_write_idx + 1) % apf1_size;

		//return apf1_out;

		// DELAY LINE 2 --------------------------------

		int delay_4 = static_cast<int>(delay_line_2_delay);

		int read_idx_4 = delay_line_2_write_idx - delay_4;

		if (read_idx_4 < 0){
			read_idx_4 += delay_line_2_size;
		}

		float delayed_4 = delay_line_2[read_idx_4];

		float delay_line_2_out = delayed_4;

		delay_line_2[delay_line_2_write_idx] = apf1_out;

		delay_line_2_write_idx = (delay_line_2_write_idx + 1) % delay_line_2_size;

		//return delay_line_2_out;

		// DECAY CONTROL 2 --------------------------------

		float tank_1_out = delay_line_2_out * decay;

	    //return tank_1_out;

		// TANK 2 ==========================================

		float tank_2_in = tank_1_out; // input sum


		//return tank_2_in;

		// INVERTING APF 2 ---------------------------------------

		int delay_5 = static_cast<int>(inv_apf2_delay);

		int read_idx_5 = inv_apf2_write_idx - delay_5;
		if (read_idx_5 < 0){
			read_idx_5 += inv_apf2_size;
		}

		float delayed_5 = inv_apf2[read_idx_5];

		float inv_apf2_out = decay_diffusion_1 * tank_2_in + delayed_5;

		inv_apf2[inv_apf2_write_idx] = -decay_diffusion_1 * inv_apf2_out + tank_2_in;

		inv_apf2_write_idx = (inv_apf2_write_idx + 1) % inv_apf2_size;

		//return inv_apf2_out;

		// DELAY LINE 3 -----------------------------------

		int delay_6 = static_cast<int>(delay_line_3_delay);

		int read_idx_6 = delay_line_3_write_idx - delay_6;

		if (read_idx_6 < 0){
			read_idx_6 += delay_line_3_size;
		}

		float delayed_6 = delay_line_3[read_idx_6];

		float delay_line_3_out = delayed_6;

		delay_line_3[delay_line_3_write_idx] = inv_apf2_out;

		delay_line_3_write_idx = (delay_line_3_write_idx + 1) % delay_line_3_size;

		//return delay_line_3_out;





	}

private:

	// TANK 1 VARIABLES

	float inv_apf1[673] = {0.0};
	uint16_t inv_apf1_size = 673;
	float inv_apf1_delay = 672;
	uint16_t inv_apf1_write_idx = 0;

	float delay_line_1[4454] = {0.0};
	uint16_t delay_line_1_size = 4454;
	float delay_line_1_delay = 4453;
	uint16_t delay_line_1_write_idx = 0;

	float apf1[1801] = {0.0};
	uint16_t apf1_size = 1801;
	float apf1_delay = 1800;
	uint16_t apf1_write_idx = 0;

	float delay_line_2[3721] = {0.0};
	uint16_t delay_line_2_size = 3721;
	float delay_line_2_delay = 3720;
	uint16_t delay_line_2_write_idx = 0;

	float decay_diffusion_1 = 0.70;
	float decay_diffusion_2 = 0.50;

	float damp_filt1_delay = 0.0;
	float damp_factor = 0.0005;

	// TANK 2 VARIABLES

	float inv_apf2[909] = {0.0};
	uint16_t inv_apf2_size = 909;
	float inv_apf2_delay = 908;
	uint16_t inv_apf2_write_idx = 0;

	float delay_line_3[4218] = {0.0};
	uint16_t delay_line_3_size = 4218;
	float delay_line_3_delay = 4217;
	uint16_t delay_line_3_write_idx = 0;

	float decay = 0.45;

};




#endif /* INC_LATE_DIFFUSION_HPP_ */
