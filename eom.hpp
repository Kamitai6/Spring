#ifndef __EOM__
#define __EOM__

#include <stdio.h>
#include <math.h>

class EOM {
	public:
		EOM() : x(0.0), v(0.0), k(0.2), b(0.2), m(1.0), dt(0.01), n(0), count(0) {}
		EOM(double x_, double v_, double k_, double b_, double m_, double dt_, int s)
			: x(x_), v(v_), k(k_), b(b_), m(m_), dt(dt_), n(0), count(0) {
				n = static_cast<int>(s / dt);
			};
		double calculate() {
			if (count >= n) {
				return -1.0;
			}

			double k1_x = dt * V_(v);
			double k1_v = dt * F_(x, v);
			double k2_x = dt * V_(v + k1_v / 2);
			double k2_v = dt * F_(x + k1_x / 2, v + k1_v / 2);
			double k3_x = dt * V_(v + k2_v / 2);
			double k3_v = dt * F_(x + k2_x / 2, v + k2_v / 2);
			double k4_x = dt * V_(v + k3_v);
			double k4_v = dt * F_(x + k3_x, v + k3_v);
			x += (k1_x + 2 * k2_x + 2 * k3_x + k4_x) / 6;
			v += (k1_v + 2 * k2_v + 2 * k3_v + k4_v) / 6;

			count++;
			return x;
		}
		void setPoint(double x_, double v_) {
			x = x_;
			v = v_;
			return;
		}
		void setParam(double k_, double b_, double m_) {
			k = k_;
			b = b_;
			m = m_;
			return;
		}
		void reset() {
			count = n;
		}

	private:
		double x, v;
		double k, b, m;
		double dt;
		int n, count;

		//
		double F_(double x, double v)
		{
			double G = 9.8;
			return -k / m * x + G + -b / m * v;
		}
		//dx/dt = v;
		double V_(double v) {
			return v;
		}
};

#endif