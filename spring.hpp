#ifndef __SPRING__
#define __SPRING__

#include <stdio.h>
#include <math.h>
#include "./eom.hpp"


class Spring {
	public:
		Spring Spring(double dt_) : dt(dt_){
		
		}
		double 
	private:
		EOM eom(1.0, 2.0, 0.7, 5.0, 1.0 / delta_t, 10000);
};

#endif