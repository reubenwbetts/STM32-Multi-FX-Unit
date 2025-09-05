/*
 * simp_lfo.hpp
 *
 *  Created on: Apr 22, 2025
 *      Author: admin
 */

#ifndef INC_SIMP_LFO_HPP_
#define INC_SIMP_LFO_HPP_

//returns integers - not floats
#include <cmath>

class simple_lfo
{
public:

	simple_lfo(float rate, float depth)
	{r = rate/48000.0;
	d = depth;};

	uint8_t process(){
		p += r;
		if(p > 1) p -= 2;
		uint8_t out = floorf(4*p*(1-fabs(p))*d);
		return floorf(out);
	}


private:
	float r;
	float d;

	float p = 0.0;

};

#endif /* INC_SIMP_LFO_HPP_ */
