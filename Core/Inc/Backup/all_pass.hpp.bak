/*
 * all_pass.hpp
 *
 *  Created on: Apr 17, 2025
 *      Author: admin
 */
#include <cstdint>

#ifndef INC_ALL_PASS_HPP_

#define INC_ALL_PASS_HPP_


class all_pass
{

	public:

	all_pass(float delay_samples, float feedback_in);

	void set_fb(float feedback);

	float process(float input);

	private:

	//filter params
	float delay;
	float fb;

	//ring buffer variables
	uint16_t buff_write_idx;
	uint16_t buff_size = 2048;

	float buffer[2048] = {0.0};

};

#endif /* INC_ALL_PASS_HPP_ */
