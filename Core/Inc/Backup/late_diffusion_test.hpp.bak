
class late_diffuse_tank_1{

public:

	float process(float input, float decay)

	{
		// APF1 --------------------------------------------

		int delay_1 = static_cast<int>(apf1_delay);

		int read_idx_1 = apf1_write_idx - delay_1;
		if (read_idx_1 < 0){
			read_idx_1 += apf1_size;
		}

		float delayed_1 = apf1[read_idx_1];

		float apf1_out = -input_diffuse_fb_1 * input + delayed_1;

		apf1[apf1_write_idx] = input + input_diffuse_fb_1 * apf1_out;

		apf1_write_idx = (apf1_write_idx + 1) % apf1_size;

		//return apf1_out;

		// DELAY LINE 1 --------------------------------------------

		int delay_2 = static_cast<int>(delay_line_1_delay);

		int read_idx_2 = delay_line_1_write_idx - delay_2;
		if (read_idx_2 < 0){
			read_idx_2 += delay_line_1_size;
		}

		float delayed_2 = delay_line_1[read_idx_2];

		float delay_line_1_out = delayed_2;

		delay_line_1[delay_line_1_write_idx] =  apf1_out;

		delay_line_1_write_idx = (delay_line_1_write_idx + 1) % delay_line_1_size;

		//return apf2_out;

		// DAMPING FILTER ----------------------------

		float sum_in = damp_factor * damp_filt1_delay + delay_line_1_out; // prevout = out

		damp_filt1_delay = sum_in;

		// DECAY CONTROL 1 -------------------------------

		float damp_1_out = sum_in * decay;

		// APF3 ---------------------------------------------

		int delay_3 = static_cast<int>(apf2_delay);

		int read_idx_3 = apf2_write_idx - delay_3;
		if (read_idx_3 < 0){
			read_idx_3 += apf2_size;
		}

		float delayed_3 = apf2[read_idx_3];

		float apf3_out = -input_diffuse_fb_2 * damp_1_out + delayed_3;

		apf2[apf2_write_idx] = damp_1_out + input_diffuse_fb_2 * apf3_out;

		apf2_write_idx = (apf2_write_idx + 1) % apf2_size;

		//return apf3_out;

		// APF4 --------------------------------------------

		int delay_4 = static_cast<int>(delay_line_2_delay);

		int read_idx_4 = delay_line_2_write_idx - delay_4;
		if (read_idx_4 < 0){
			read_idx_4 += delay_line_2_size;
		}

		float delayed_4 = delay_line_2[read_idx_4];

		float delay_line_2_out = delayed_4;

		delay_line_2[delay_line_2_write_idx] = apf3_out;

		delay_line_2_write_idx = (delay_line_2_write_idx + 1) % delay_line_2_size;

		return delay_line_2_out * decay;

	}

private:

	// all-pass filter buffers (taken from datorros paper)

	float apf1[673] = {0.0};
	uint16_t apf1_size = 673;
	float apf1_delay = 672.0;
	uint16_t apf1_write_idx = 0;

	float delay_line_1[4454] = {0.0};
	uint16_t delay_line_1_size = 4454;
	float delay_line_1_delay = 4453;
	uint16_t delay_line_1_write_idx = 0;

	float apf2[1801] = {0.0};
	uint16_t apf2_size = 1801;
	float apf2_delay = 1800.0;
	uint16_t apf2_write_idx = 0;

	float delay_line_2[3721] = {0.0};
	uint16_t delay_line_2_size = 3721;
	float delay_line_2_delay = 3720.0;
	uint16_t delay_line_2_write_idx = 0;


	// fb coeffs (taken from datorros paper)

	float input_diffuse_fb_1 = 0.700;
	float input_diffuse_fb_2 = 0.625;

	float damp_filt1_delay = 0.0;
	float damp_factor = 0.0005;

};
