/*
 * svf_lpf.hpp
 *
 *  Created on: Apr 16, 2025
 *      Author: admin
 */

#ifndef INC_SVF_LPF_HPP_
#define INC_SVF_LPF_HPP_

class svf_lpf
{

public:

	svf_lpf(float cutoff, float res, float sample_rate);

	void coeff_gen(float cutoff, float res, float sample_rate);

	float process_lpf(float input);

	float process_hpf(float input);

	float process_bpf(float input);


private:


	float fs = 0.0;
	float q = 0.0;
	float f = 0.0;
	float w = 0.0;
	float a = 0.0;
	float b = 0.0;
	float c1 = 0.0;
	float c2 = 0.0;
	float z1_lpf = 0.0;
	float z2_lpf = 0.0;
	float z1_hpf = 0.0;
	float z2_hpf = 0.0;
	float z1_bpf = 0.0;
	float z2_bpf = 0.0;

	float d0lpf = 0.0;
	float d0hpf = 0.0;
	float d0bpf = 0.0;
	float d1bpf = 0.0;
	float d1 = 0.0;
	float d2 = 0.0;
};



#endif /* INC_SVF_LPF_HPP_ */
