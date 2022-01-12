#ifndef __SPRING__
#define __SPRING__

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <random>
#include "./eom.hpp"


class Spring {
	public:
		Spring Spring(double dt, int num) : dt(dt_) {
			std::random_device seed_gen;
			std::mt19937 engine(seed_gen());
			std::uniform_real_distribution<> dist1(-1.0, 1.0);

			for(int i{}; i < num; ++i) {
				double x = dist1(engine);
				double v = dist1(engine);
				double k = dist1(engine);
				double b = dist1(engine);
				double m = dist1(engine);
				doms.enplace_back(move(DOM(x, v, k, b, m, dt, 10)));
			}
		}
		void showObject() {
			glBegin(GL_LINE_LOOP);
			for (int i{}; i < 4; ++i) { glVertex2d(axis[i][0], axis[i][1]);}
			glEnd();
		}
	private:
		double calculate() {
			std::vector<double>x{};
			for(const auto& d : doms) {
				x.enplace_back(d.calculate());
			}
			return x;
		}
		std::vector<DOM> doms();
};

#endif