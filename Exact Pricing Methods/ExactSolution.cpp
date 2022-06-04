#include "ExactSolution.h"
#include "AllOptions.h"

namespace Christine
{
	namespace Calculations
	{
		void ExactSolution::init()	// Initialise all default values
		{
			myNormal = new NormalDistribution(0, 1);
		}

		// now we implement the constructors, destructor, and assignment operator
		// call the base class here too
		ExactSolution::ExactSolution() : PriceFormula() { init(); }// Default constructor, intialize value
		ExactSolution::ExactSolution(const ExactSolution& copy) : PriceFormula(copy)  // Copy constructor
		{ 
			myNormal = new NormalDistribution(); // create the pointer, store on the heap; will have to delete it 
			*myNormal = *copy.myNormal; // dereferencing the pointer
		}
		ExactSolution::~ExactSolution() { delete myNormal; }	// Destructor; delete the pointer on the heap
		ExactSolution& ExactSolution::operator = (const ExactSolution& source)// Assignment operator
		{
			// Call the base class assignment
			PriceFormula::operator = (source);

			// Preclude self-assignment
			if (this == &source) return *this;

			myNormal = new NormalDistribution();
			*myNormal = *source.myNormal;
		}

		// determine if it is call or put option
		bool ExactSolution::IsCall(const OptionData& OD) const // call option data
		{
			return OD.type == 1;
		}
		bool ExactSolution::IsCall(const int& option_type) const // directly input option_type, member from base class
		{
			return option_type == 1;
		}

		// calculate the d1 by passing into the parameters
		double ExactSolution::d1(const double& S, const double& K, const double& r, const double& T, const double& sig, const double& b) const
		{
			double temp = sig * sqrt(T);
			return (log(S / K) + (b + (sig * sig) * 0.5) * T) / temp;
		}

		// calculate the d2 by using the relationship between d1 and d2
		double ExactSolution::d2(const double& S, const double& K, const double& r, const double& T, const double& sig, const double& b) const
		{
			return d1(S, K, r, T, sig, b) - (sig * sqrt(T));
		}


		// the normal distribution function
		double ExactSolution::norm_cdf(const double& dx) const  // Standard cumulative normal(Gaussian) distribution function
		{
			return myNormal->Cumulative_Distribution(dx);
		}

		double ExactSolution::norm_pdf(const double& dx) const  // Probability distribution function
		{
			return myNormal->Probability_Density(dx);
		}


		// calculate the CALL price, passing into vector
		double ExactSolution::CallPrice(const vector<double>& OP) const
		{
			/*vec[0] = m_S;
			vec[1] = m_K;
			vec[2] = m_r;
			vec[3] = m_T;
			vec[4] = m_sig;
			vec[5] = m_b;*/

			return (OP[0] * exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5]))) - (OP[1] * exp(-OP[2] * OP[3]) * norm_cdf(d2(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5])));
		}

		// calculate the PUT price, getting data from vector
		double ExactSolution::PutPrice(const vector<double>& OP) const
		{
			return (-OP[0] * exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(-d1(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5]))) + (OP[1] * exp(-OP[2] * OP[3]) * norm_cdf(-d2(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5])));
		}

		// Calculate the CALL Delta by getting data from the vector
		double ExactSolution::CallDelta(const vector<double>& OP) const
		{
			/*double temp = OP[4] * sqrt(OP[3]);

			double m_d1 = (log(OP[0] / OP[1]) + (OP[5] + (OP[4] * OP[4]) * 0.5) * OP[3]) / temp;*/

			return exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5]));
		}

		// Calculate the PUT Delta by passing the vector
		double ExactSolution::PutDelta(const vector<double>& OP) const
		{
			/*double tmp = OP[4] * sqrt(OP[3]);

			double m_d1 = (log(OP[0] / OP[1]) + (OP[5] + (OP[4] * OP[4]) * 0.5) * OP[3]) / tmp;*/

			return exp((OP[5] - OP[2]) * OP[3]) * (norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5])) - 1.0);
		}

		// Calculate the Gamma by passing the vector
		double ExactSolution::Gamma(const vector<double>& OP) const
		{
			// This is how we calculate Gamma
			// pdf(d1) * exp(b-r)T/(S*sig*sqrt(T))
			return (norm_pdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5])) * exp((OP[5] - OP[2]) * OP[3])) / (OP[0] * OP[4] * sqrt(OP[3]));
		}
		// Calculate the Vega by passing the vector
		double ExactSolution::Vega(const vector<double>& OP) const
		{
			/*vec[0] = m_S;
			vec[1] = m_K;
			vec[2] = m_r;
			vec[3] = m_T;
			vec[4] = m_sig;
			vec[5] = m_b;*/

			// This is how we calculate Vega
			// pdf(d1) * S*sqrt(T) * exp(b-r)T

			return (norm_pdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5])) * (OP[0] * sqrt(OP[3])) * exp((OP[5] - OP[2]) * OP[3]));
		}
		// Calculate the Theta by passing the vector
		double ExactSolution::Theta(const vector<double>& OP) const
		{
			// This is how we calculate Theta
			// step 1 = - S*sig*exp(b-r)T*pdf(d1)  / (2*sqrt(T))
			double step1 = - (OP[0] * OP[4] * exp((OP[5] - OP[2]) * OP[3]) * norm_pdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5])) / (2 * sqrt(OP[3])));
			// step 2
			double step2 = (OP[5] - OP[2]) * OP[0] * exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5]));
			// step 3
			double step3 = OP[2] * OP[1] * exp(-OP[2] * OP[3]) * norm_cdf(d2(OP[0], OP[1], OP[2], OP[3], OP[4], OP[5]));
			double theta = step1 - step2 - step3;

			return theta;
		}

		//Put-call parity satisfaction
		//This is to make sure that a given set of put/call prices satisfy parity
		double ExactSolution::PutCallParity(const vector<double>& OP, const double& other_option_price, const int& option_type) const // This will use the call/put price to calculate the corresponding call/put price
		{
			// make the compiler know if this is a call or put option
			if (IsCall(option_type))  // This will be CALL Option
			{
				return other_option_price + OP[0] - (OP[1] * exp(-OP[2] * OP[3]));
			}
			else // This will be PUT Option
			{
				return other_option_price - OP[0] + (OP[1] * exp(-OP[2] * OP[3]));
			}
		}

		// The below functions are to calculate the Call price with passing into different parameters, should be also used
		// to make the matrix
		double ExactSolution::CallPrice_S(const double& S, const vector<double>& OP) const
		{
			return (S * exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(d1(S, OP[1], OP[2], OP[3], OP[4], OP[5]))) - (OP[1] * exp(-OP[2] * OP[3]) * norm_cdf(d2(S, OP[1], OP[2], OP[3], OP[4], OP[5])));
		}
		double ExactSolution::CallPrice_K(const double& K, const vector<double>& OP) const// call price with passing the different K
		{
			return (OP[0] * exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(d1(OP[0], K, OP[2], OP[3], OP[4], OP[5]))) - (K * exp(-OP[2] * OP[3]) * norm_cdf(d2(OP[0], K, OP[2], OP[3], OP[4], OP[5])));
		}
		double ExactSolution::CallPrice_T(const double& T, const vector<double>& OP) const // call price with passing the different T
		{
			return (OP[0] * exp((OP[5] - OP[2]) * T) * norm_cdf(d1(OP[0], OP[1], OP[2], T, OP[4], OP[5]))) - (OP[1] * exp(-OP[2] * T) * norm_cdf(d2(OP[0], OP[1], OP[2], T, OP[4], OP[5])));
		}
		double ExactSolution::CallPrice_sig(const double& sig, const vector<double>& OP) const // call price with passing the different sig
		{
			return (OP[0] * exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], sig, OP[5]))) - (OP[1] * exp(-OP[2] * OP[3]) * norm_cdf(d2(OP[0], OP[1], OP[2], OP[3], sig, OP[5])));
		}
		double ExactSolution::CallPrice_r(const double& r, const vector<double>& OP) const // call price with passing the different r
		{
			return (OP[0] * exp((OP[5] - r) * OP[3]) * norm_cdf(d1(OP[0], OP[1], r, OP[3], OP[4], OP[5]))) - (OP[1] * exp(-r * OP[3]) * norm_cdf(d2(OP[0], OP[1], r, OP[3], OP[4], OP[5])));
		}
		double ExactSolution::CallPrice_b(const double& b, const vector<double>& OP) const // call price with passing the different b
		{
			return (OP[0] * exp((b - OP[2]) * OP[3]) * norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], b))) - (OP[1] * exp(-OP[2] * OP[3]) * norm_cdf(d2(OP[0], OP[1], OP[2], OP[3], OP[4], b)));
		}


		// put price with passing the different S
		double ExactSolution::PutPrice_S(const double& S, const vector<double>& OP) const
		{
			return (-S * exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(-d1(S, OP[1], OP[2], OP[3], OP[4], OP[5]))) + (OP[1] * exp(-OP[2] * OP[3]) * norm_cdf(-d2(S, OP[1], OP[2], OP[3], OP[4], OP[5])));
		}

		double ExactSolution::PutPrice_K(const double& K, const vector<double>& OP) const // put price with passing the different K
		{
			return (-OP[0] * exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(-d1(OP[0], K, OP[2], OP[3], OP[4], OP[5]))) + (K * exp(-OP[2] * OP[3]) * norm_cdf(-d2(OP[0], K, OP[2], OP[3], OP[4], OP[5])));
		}
		double ExactSolution::PutPrice_T(const double& T, const vector<double>& OP) const // put price with passing the different T
		{
			return (-OP[0] * exp((OP[5] - OP[2]) * T) * norm_cdf(-d1(OP[0], OP[1], OP[2], T, OP[4], OP[5]))) + (OP[1] * exp(-OP[2] * T) * norm_cdf(-d2(OP[0], OP[1], OP[2], T, OP[4], OP[5])));
		}
		double ExactSolution::PutPrice_sig(const double& sig, const vector<double>& OP) const // put price with passing the different sig
		{
			return (-OP[0] * exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(-d1(OP[0], OP[1], OP[2], OP[3], sig, OP[5]))) + (OP[1] * exp(-OP[2] * OP[3]) * norm_cdf(-d2(OP[0], OP[1], OP[2], OP[3], sig, OP[5])));
		}
		double ExactSolution::PutPrice_r(const double& r, const vector<double>& OP) const // put price with passing the different r
		{
			return (-OP[0] * exp((OP[5] - r) * OP[3]) * norm_cdf(-d1(OP[0], OP[1], r, OP[3], OP[4], OP[5]))) + (OP[1] * exp(-r * OP[3]) * norm_cdf(-d2(OP[0], OP[1], r, OP[3], OP[4], OP[5])));
		}
		double ExactSolution::PutPrice_b(const double& b, const vector<double>& OP) const // put price with passing the different b
		{
			return (-OP[0] * exp((b - OP[2]) * OP[3]) * norm_cdf(-d1(OP[0], OP[1], OP[2], OP[3], OP[4], b))) + (OP[1] * exp(-OP[2] * OP[3]) * norm_cdf(-d2(OP[0], OP[1], OP[2], OP[3], OP[4], b)));
		}

		/*vec[0] = m_S;
			vec[1] = m_K;
			vec[2] = m_r;
			vec[3] = m_T;
			vec[4] = m_sig;
			vec[5] = m_b;*/

		// The below functions are to calculate the Call Delta with passing into different parameters, should be also used
		// to make the matrix
		double ExactSolution::CallDelta_S(const double& S, const vector<double>& OP) const // Call Delta with passing the different S
		{
			return exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(d1(S, OP[1], OP[2], OP[3], OP[4], OP[5]));
		}
		double ExactSolution::CallDelta_K(const double& K, const vector<double>& OP) const // Call Delta with passing the different S
		{
			return exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(d1(OP[0], K, OP[2], OP[3], OP[4], OP[5]));
		}
		double ExactSolution::CallDelta_T(const double& T, const vector<double>& OP) const // Call Delta with passing the different S
		{
			return exp((OP[5] - OP[2]) * T) * norm_cdf(d1(OP[0], OP[1], OP[2], T, OP[4], OP[5]));
		}
		double ExactSolution::CallDelta_sig(const double& sig, const vector<double>& OP) const // Call Delta with passing the different S
		{
			return exp((OP[5] - OP[2]) * OP[3]) * norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], sig, OP[5]));
		}
		double ExactSolution::CallDelta_r(const double& r, const vector<double>& OP) const // Call Delta with passing the different S
		{
			return exp((OP[5] - r) * OP[3]) * norm_cdf(d1(OP[0], OP[1], r, OP[3], OP[4], OP[5]));
		}
		double ExactSolution::CallDelta_b(const double& b, const vector<double>& OP) const // Call Delta with passing the different S
		{
			return exp((b - OP[2]) * OP[3]) * norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], b));
		}


		// The below functions are to calculate the Put Delta with passing into different parameters, should be also used
		// to make the matrix
		double ExactSolution::PutDelta_S(const double& S, const vector<double>& OP) const // put Delta with passing the different S
		{
			return exp((OP[5] - OP[2]) * OP[3]) * (norm_cdf(d1(S, OP[1], OP[2], OP[3], OP[4], OP[5])) - 1.0);
		}
		double ExactSolution::PutDelta_K(const double& K, const vector<double>& OP) const // put Delta with passing the different S
		{
			return exp((OP[5] - OP[2]) * OP[3]) * (norm_cdf(d1(OP[0], K, OP[2], OP[3], OP[4], OP[5])) - 1.0);
		}
		double ExactSolution::PutDelta_T(const double& T, const vector<double>& OP) const // put Delta with passing the different S
		{
			return exp((OP[5] - OP[2]) * T) * (norm_cdf(d1(OP[0], OP[1], OP[2], T, OP[4], OP[5])) - 1.0);
		}
		double ExactSolution::PutDelta_sig(const double& sig, const vector<double>& OP) const // put Delta with passing the different S
		{
			return exp((OP[5] - OP[2]) * OP[3]) * (norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], sig, OP[5])) - 1.0);
		}
		double ExactSolution::PutDelta_r(const double& r, const vector<double>& OP) const // put Delta with passing the different S
		{
			return exp((OP[5] - r) * OP[3]) * (norm_cdf(d1(OP[0], OP[1], r, OP[3], OP[4], OP[5])) - 1.0);
		}
		double ExactSolution::PutDelta_b(const double& b, const vector<double>& OP) const // put Delta with passing the different S
		{
			return exp((b - OP[2]) * OP[3]) * (norm_cdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], b)) - 1.0);
		}

		/*vec[0] = m_S;
			vec[1] = m_K;
			vec[2] = m_r;
			vec[3] = m_T;
			vec[4] = m_sig;
			vec[5] = m_b;*/

		// The below functions are to calculate the Gamma with passing into different parameters, should be also used
			// to make the matrix
		double ExactSolution::Gamma_S(const double& S, const vector<double>& OP) const // Gamma with passing the different S
		{
			return (norm_pdf(d1(S, OP[1], OP[2], OP[3], OP[4], OP[5])) * exp((OP[5] - OP[2]) * OP[3])) / (S * OP[4] * sqrt(OP[3]));
		}
		double ExactSolution::Gamma_K(const double& K, const vector<double>& OP) const // Gamma with passing the different K
		{
			return (norm_pdf(d1(OP[0], K, OP[2], OP[3], OP[4], OP[5])) * exp((OP[5] - OP[2]) * OP[3])) / (OP[0] * OP[4] * sqrt(OP[3]));
		}
		double ExactSolution::Gamma_T(const double& T, const vector<double>& OP) const // Gamma with passing the different T
		{
			return (norm_pdf(d1(OP[0], OP[1], OP[2], T, OP[4], OP[5])) * exp((OP[5] - OP[2]) * T)) / (OP[0] * OP[4] * sqrt(T));
		}
		double ExactSolution::Gamma_sig(const double& sig, const vector<double>& OP) const // Gamma with passing the different sig
		{
			return (norm_pdf(d1(OP[0], OP[1], OP[2], OP[3], sig, OP[5])) * exp((OP[5] - OP[2]) * OP[3])) / (OP[0] * sig * sqrt(OP[3]));
		}
		double ExactSolution::Gamma_r(const double& r, const vector<double>& OP) const // Gamma with passing the different r
		{
			return (norm_pdf(d1(OP[0], OP[1], r, OP[3], OP[4], OP[5])) * exp((OP[5] - r) * OP[3])) / (OP[0] * OP[4] * sqrt(OP[3]));
		}
		double ExactSolution::Gamma_b(const double& b, const vector<double>& OP) const // Gamma with passing the different b
		{
			return (norm_pdf(d1(OP[0], OP[1], OP[2], OP[3], OP[4], b)) * exp((b - OP[2]) * OP[3])) / (OP[0] * OP[4] * sqrt(OP[3]));
		}
	}
}