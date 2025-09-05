/*
 * all_pass.cpp
 *
 *  Created on: Apr 17, 2025
 *      Author: admin
 */

#include <all_pass.hpp>



// 8 bit buffer for smaller values -------------------------------------
// utilising fixed size buffers to avoid using modulo or manual fold back

all_pass::all_pass(float delay_samples, float feedback_in)
{
	// ensure silence on initialisation

	// set all parameters on initialisation

	fb = feedback_in;
	delay = delay_samples;
	buff_write_idx = 0;


}



float all_pass::process(float x)
{


	int delay_samples = static_cast<int>(delay);
	int read_idx = buff_write_idx - delay_samples;
	if (read_idx < 0){
		read_idx += buff_size;
	}
	// Get delayed sample
	float delayed = buffer[read_idx];

	// Calculate current output
	 float y = -fb * x + delayed;

	// Write to buffer for future feedback
	buffer[buff_write_idx] = x + fb * y;

	// Advance write index and wrap
	buff_write_idx = (buff_write_idx + 1) % buff_size;

	return y;

}


