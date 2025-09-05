/*
 * 3_band_eq.hpp
 *
 *  Created on: Apr 22, 2025
 *      Author: admin
 */



#ifndef INC_3_BAND_EQ_HPP_
#define INC_3_BAND_EQ_HPP_
#include "svf_lpf.hpp"

class basic_eq
{

public:

	void set_low_shelf_gain(float gain);

	void set_low_mid_bell_gain(float gain);

	void set_high_mid_bell_gain(float gain);

	void set_high_shelf_gain(float gain);

	float process(float input);




private:


	// biquads would have made a much better choice as they're static but ah well

	svf_lpf filter_hs {5000.0, 0.707, 48000.0};
	svf_lpf filter_hs2 {1000.0, 0.303, 48000.0};


	svf_lpf filter_hmb {1300.0, 0.707, 48000.0};
	svf_lpf filter_hmb2 {1300.0, 0.303, 48000.0};

	svf_lpf filter_lmb {400.0, 0.707, 48000.0};
	svf_lpf filter_lmb2 {400.0, 0.303, 48000.0};


	svf_lpf filter_ls {150.0, 0.707, 48000.0};
	svf_lpf filter_ls2 {300.0, 0.303, 48000.0};



	float g_ls = 0.0;
	float g_hs = 0.0;
	float g_lmb = 0.0;
	float g_hmb = 0.0;







};



#endif /* INC_3_BAND_EQ_HPP_ */
