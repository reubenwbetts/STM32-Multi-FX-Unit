/*
 * GainProces.hpp
 *
 *  Created on: Apr 16, 2025
 *      Author: admin
 */

#ifndef INC_GAINPROCESS_HPP_
#define INC_GAINPROCESS_HPP_

#include <cmath>

class GainProcess

{

public:

GainProcess()
{
	gain = 1.0f;
}

void update_value(float val)
{
	gain = val;

}

float Process(float input)
{

	float output = (input*gain);
	return output;

}

private:

float gain;

};

#endif /* INC_GAINPROCESS_HPP_ */
