#include "PerpetualSolution.h"

namespace Christine
{
	namespace Calculations
	{
		// Constructors, destructor, and Assignment Operator
		PerpetualSolution::PerpetualSolution(): PriceFormula(){}// Default constructor
		PerpetualSolution::~PerpetualSolution(){}	// Destructor
		PerpetualSolution::PerpetualSolution(const PerpetualSolution& copy): PriceFormula(copy){}	// Copy constructor
		PerpetualSolution& PerpetualSolution::operator = (const PerpetualSolution& source) // Assignment operator
		{
			// Call the base class assignment
			PriceFormula::operator = (source);

			// Preclude self-assignment
			if (this == &source) return *this;
			return *this;
		}

		// The following two functions calculate the Option Price for American Perpetual Option
		double PerpetualSolution::CallPrice(const vector<double>& OP) const  // calculate the PUT price, getting data from vector
		{
			/*vec[0] = m_S;
			vec[1] = m_K;
			vec[2] = m_r;
			vec[3] = m_T;
			vec[4] = m_sig;
			vec[5] = m_b;*/

			double sig_2 = OP[4] * OP[4];
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y1 = 0.5 - OP[5] / sig_2 + sqrt(fac + 2.0 * OP[2] / sig_2);

			if (y1 == 1.0)
			{
				return OP[0];
			}
			else {
				double fac2 = ((y1 - 1.0) * OP[0]) / (y1 * OP[1]);
				double c = OP[1] * pow(fac2, y1) / (y1 - 1.0);

				return c;
			}
		}
		double PerpetualSolution::PutPrice(const vector<double>& OP) const  // calculate the CALL price, getting data from vector
		{
			/*vec[0] = m_S;
			vec[1] = m_K;
			vec[2] = m_r;
			vec[3] = m_T;
			vec[4] = m_sig;
			vec[5] = m_b;*/

			double sig_2 = OP[4] * OP[4];
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y2 = 0.5 - OP[5] / sig_2 - sqrt(fac + 2.0 * OP[2] / sig_2);

			if (0.0 == y2)
				return OP[0];

			double fac2 = ((y2 - 1.0) * OP[0]) / (y2 * OP[1]);
			double p = OP[1] * pow(fac2, y2) / (1.0 - y2);

			return p;
		}

		// The below functions are to calculate the Call price with passing into different parameters, should be also used
		// to make the matrix
		double PerpetualSolution::CalculateCall_S(const double& S, const vector<double>& OP) const // call price with passing the different S
		{
			double sig_2 = OP[4] * OP[4];
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y1 = 0.5 - OP[5] / sig_2 + sqrt(fac + 2.0 * OP[2] / sig_2);

			if (y1 == 1.0)
			{
				return S;
			}
			else {
				double fac2 = ((y1 - 1.0) * S) / (y1 * OP[1]);
				double c = OP[1] * pow(fac2, y1) / (y1 - 1.0);

				return c;
			}
		}
		double PerpetualSolution::CalculateCall_K(const double& K, const vector<double>& OP) const // call price with passing the different K
		{
			double sig_2 = OP[4] * OP[4];
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y1 = 0.5 - OP[5] / sig_2 + sqrt(fac + 2.0 * OP[2] / sig_2);

			if (y1 == 1.0)
			{
				return OP[0];
			}
			else {
				double fac2 = ((y1 - 1.0) * OP[0]) / (y1 * K);
				double c = K * pow(fac2, y1) / (y1 - 1.0);

				return c;
			}
		}

		double PerpetualSolution::CalculateCall_sig(const double& sig, const vector<double>& OP) const // call price with passing the different sig
		{
			double sig_2 = sig * sig;
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y1 = 0.5 - OP[5] / sig_2 + sqrt(fac + 2.0 * OP[2] / sig_2);

			if (y1 == 1.0)
			{
				return OP[0];
			}
			else {
				double fac2 = ((y1 - 1.0) * OP[0]) / (y1 * OP[1]);
				double c = OP[1] * pow(fac2, y1) / (y1 - 1.0);

				return c;
			}
		}
		double PerpetualSolution::CalculateCall_r(const double& r, const vector<double>& OP) const // call price with passing the different r
		{
			double sig_2 = OP[4] * OP[4];
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y1 = 0.5 - OP[5] / sig_2 + sqrt(fac + 2.0 * r / sig_2);

			if (y1 == 1.0)
			{
				return OP[0];
			}
			else {
				double fac2 = ((y1 - 1.0) * OP[0]) / (y1 * OP[1]);
				double c = OP[1] * pow(fac2, y1) / (y1 - 1.0);

				return c;
			}
		}
		double PerpetualSolution::CalculateCall_b(const double& b, const vector<double>& OP) const // call price with passing the different b
		{
			double sig_2 = OP[4] * OP[4];
			double fac = b / sig_2 - 0.5; fac *= fac;
			double y1 = 0.5 - b / sig_2 + sqrt(fac + 2.0 * OP[2] / sig_2);

			if (y1 == 1.0)
			{
				return OP[0];
			}
			else {
				double fac2 = ((y1 - 1.0) * OP[0]) / (y1 * OP[1]);
				double c = OP[1] * pow(fac2, y1) / (y1 - 1.0);

				return c;
			}
		}

		// The below functions are to calculate the Put price with passing into different parameters, should be also used
		// to make the matrix
		double PerpetualSolution::CalculatePut_S(const double& S, const vector<double>& OP) const // put price with passing the different S
		{
			double sig_2 = OP[4] * OP[4];
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y2 = 0.5 - OP[5] / sig_2 - sqrt(fac + 2.0 * OP[2] / sig_2);

			if (0.0 == y2)
				return S;

			double fac2 = ((y2 - 1.0) * S) / (y2 * OP[1]);
			double p = OP[1] * pow(fac2, y2) / (1.0 - y2);

			return p;
		}
		double PerpetualSolution::CalculatePut_K(const double& K, const vector<double>& OP) const // put price with passing the different K
		{
			double sig_2 = OP[4] * OP[4];
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y2 = 0.5 - OP[5] / sig_2 - sqrt(fac + 2.0 * OP[2] / sig_2);

			if (0.0 == y2)
				return OP[0];

			double fac2 = ((y2 - 1.0) * OP[0]) / (y2 * K);
			double p = K * pow(fac2, y2) / (1.0 - y2);

			return p;
		}
		double PerpetualSolution::CalculatePut_sig(const double& sig, const vector<double>& OP) const // put price with passing the different sig
		{
			double sig_2 = sig * sig;
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y2 = 0.5 - OP[5] / sig_2 - sqrt(fac + 2.0 * OP[2] / sig_2);

			if (0.0 == y2)
				return OP[0];

			double fac2 = ((y2 - 1.0) * OP[0]) / (y2 * OP[1]);
			double p = OP[1] * pow(fac2, y2) / (1.0 - y2);

			return p;
		}
		double PerpetualSolution::CalculatePut_r(const double& r, const vector<double>& OP) const // put price with passing the different r
		{
			double sig_2 = OP[4] * OP[4];
			double fac = OP[5] / sig_2 - 0.5; fac *= fac;
			double y2 = 0.5 - OP[5] / sig_2 - sqrt(fac + 2.0 * r / sig_2);

			if (0.0 == y2)
				return OP[0];

			double fac2 = ((y2 - 1.0) * OP[0]) / (y2 * OP[1]);
			double p = OP[1] * pow(fac2, y2) / (1.0 - y2);

			return p;
		}
		double PerpetualSolution::CalculatePut_b(const double& b, const vector<double>& OP) const // put price with passing the different b
		{
			double sig_2 = OP[4] * OP[4];
			double fac = b / sig_2 - 0.5; fac *= fac;
			double y2 = 0.5 - OP[5] / sig_2 - sqrt(fac + 2.0 * OP[2] / sig_2);

			if (0.0 == y2)
				return OP[0];

			double fac2 = ((y2 - 1.0) * OP[0]) / (y2 * OP[1]);
			double p = OP[1] * pow(fac2, y2) / (1.0 - y2);

			return p;
		}
	}
}