#ifndef __SPRING__
#define __SPRING__

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <random>
#include <iostream>
#include "./eom.hpp"


template<typename T>
static inline T Restrain(T x, T limit) {
	return ((x) < (-limit) ? (-limit) : ((x) > (limit) ? (limit) : (x)));
}


class Spring {
	public:
		Spring(double dt, int num) : eoms{}, axis{}, g{}, xaxis{}, size{} {
			std::random_device seed_gen;
			std::mt19937 engine(seed_gen());
			std::uniform_real_distribution<> dist1(-1.0, 1.0);

			for (int i{}; i < num; ++i) {
				double x = dist1(engine);
				double v = dist1(engine);
				double k = dist1(engine) / 2.0;
				double b = dist1(engine) / 3.0;
				double m = std::abs(dist1(engine) * 5.0);
				eoms.emplace_back(std::move(EOM(x, v, k, b, m, dt, 1000)));
				xaxis.emplace_back(dist1(engine));
				size.emplace_back(dist1(engine));

			}
		}
		void showObject() {
		    auto yaxis = calculate();
			
			auto x_b = xaxis.begin();
			auto y_b = yaxis.begin();
			auto s_b = size.begin();
			auto x_e = xaxis.end();
			auto y_e = yaxis.end();
			auto s_e = size.end();
			while (x_b != x_e || y_b != y_e || s_b != s_e)
			{
				gtoAxis(*x_b, *y_b, *s_b);
				glBegin(GL_LINE_LOOP);
				for (int i{}; i < 4; ++i) { glVertex2d(axis[i][0], axis[i][1]); std::cout << axis[i][0] << " " << axis[i][1] << std::endl;
				}
				glEnd();
				if (x_b != x_e) { ++x_b; }
				if (y_b != y_e) { ++y_b; }
				if (s_b != s_e) { ++s_b; }
			}
		}
	private:
		void gtoAxis(GLfloat x, GLfloat y, GLfloat size) {
			axis[0][0] = x - (size / 2);
			axis[0][1] = y - (size / 2);
			axis[1][0] = x + (size / 2);
			axis[1][1] = y - (size / 2);
			axis[2][0] = x + (size / 2);
			axis[2][1] = y + (size / 2);
			axis[3][0] = x - (size / 2);
			axis[3][1] = y + (size / 2);

			for (int i{}; i < 4; ++i) {
				for (int j{}; j < 2; ++j) {
					Restrain<double>(axis[i][j], 0.99);
				}
			}
			return;
		}
		std::vector<double> calculate() {
			double max = 0.0;
			std::vector<double>x{};
			for (auto& d : eoms) {
				auto a = d.calculate();
				x.emplace_back(a);
				if (a > max) max = a;
			}
			for (auto& d : x) {
				d /= max;
			}
			return x;
		}
		std::vector<EOM> eoms;
		GLfloat axis[4][2];
		GLfloat g[3] = {};
		std::vector<double>xaxis;
		std::vector<double>size;

};

#endif