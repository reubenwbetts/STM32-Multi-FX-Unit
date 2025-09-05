/*
 * svf_lpf.cpp
 *
 *  Created on: Apr 16, 2025
 *      Author: admin
 */

#include "svf_lpf.hpp"
#include <cmath>
const float pi = 3.14159715;

/* state variable lowpass
 *
 * use this for sweepable lpf's (quaicker coeff gen than biqaud's)
 *
*/

svf_lpf::svf_lpf(float cutoff,float res, float sample_rate)
{
	fs = sample_rate;
		f = cutoff/fs;
		q = res;
		w = 2.0 * fs * tan(pi * f / fs);

		a = w / res;
		b = w * w;

		c1 = (a + b) / (1.0 + a / 2.0 + b / 4.0);
		c2 = b / (a + b);

		d0lpf = c1 * c2 / 4.0;
		d0hpf = 1.0 -d0lpf;
		d0bpf = (1.0-c2) * c1/2.0;
		d1bpf = 1 -c2;
};

/*void svf_lpf::coeff_gen(float cutoff, float res, float sample_rate)
{
	fs = sample_rate;
	f = cutoff/fs;
	q = res;
	w = 2.0 * fs * tan(pi * f / fs);

	a = w / res;
	b = w * w;

	c1 = (a + b) / (1.0 + a / 2.0 + b / 4.0);
	c2 = b / (a + b);

	d0lpf = c1 * c2 / 4.0;
	d0hpf = 1.0 -d0lpf;
	d0bpf = (1.0-c2) * c1/2.0;
	d1bpf = 1 -c2;

}
/*
 *
 */
float svf_lpf::process_lpf(float input)
{
	float x = input - z1_lpf - z2_lpf;
    z2_lpf += c2 * z1_lpf;
    float y = d0lpf * x + z2_lpf;
    z1_lpf += c1 * x;
    return y + 1e-20f - 1e-20f;
}

float svf_lpf::process_hpf(float input)
{
	float x = input - z1_hpf - z2_hpf;
	float y = d0hpf * x;
    z2_hpf += c2 * z1_hpf;
    z1_hpf += c1 * x;
    return y + 1e-20f - 1e-20f;
}

 float svf_lpf::process_bpf(float input)
{
	float x = input - z1_bpf - z2_bpf;
	float y = d0bpf * x + d1 * z1_bpf;
    z2_bpf += c2 * z1_bpf;
    z1_bpf += c1 * x;
    return y + 1e-20f - 1e-20f;
}


