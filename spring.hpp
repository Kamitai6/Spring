#ifndef __SPRING__
#define __SPRING__

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <random>
#include "./eom.hpp"


class Spring {
	public:
		Spring(double dt, int num) : eoms{}, axis{} {
			std::random_device seed_gen;
			std::mt19937 engine(seed_gen());
			std::uniform_real_distribution<> dist1(-1.0, 1.0);

			for (int i{}; i < num; ++i) {
				double x = dist1(engine);
				double v = dist1(engine);
				double k = dist1(engine);
				double b = dist1(engine);
				double m = dist1(engine);
				eoms.emplace_back(std::move(EOM(x, v, k, b, m, dt, 10)));
			}
		}
		void showObject() {
			glBegin(GL_LINE_LOOP);
			for (int i{}; i < 4; ++i) { glVertex2d(axis[i][0], axis[i][1]); }
			glEnd();
		}
		auto calculate() {
			std::vector<double>x{};
			for (auto& d : eoms) {
				x.emplace_back(d.calculate());
			}
			return x;
		}
	private:
		std::vector<EOM> eoms;
		GLfloat axis[4][2];
};

#endif