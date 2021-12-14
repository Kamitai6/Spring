#ifndef __EOM__
#define __EOM__

#include <stdio.h>
#include <math.h>

class EOM {
	public:
		EOM(double x_, double v_, double k_, double m_, double dt_, int n_)
			: x(x_), v(v_), k(k_), m(m_), dt(dt_), n(n_), count(0) {};
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
		void setParam(double k_, double m_) {
			k = k_;
			m = m_;
			return;
		}
		void reset() {
			count = n;
		}

	private:
		double x, v;
		double k, m;
		double dt;
		int n, count;

		//Ž¿“_‚É‰Á‚í‚é—Í
		double F_(double x, double v) {
			return -k / m * x;
		}
		//dx/dt = v;
		double V_(double v) {
			return v;
		}
};

#endif