// This class will be the derived class of PriceFormula
// This class will do all the necessary calculations for Option by giving exact solution

#ifndef ExactSolution_HPP
#define ExactSolution_HPP

#include "PriceFormula.h"
#include "OptionData.h"
#include "NormalDistribution.h"
#include "Utilities.h"

using namespace Christine::Statistics; // enable the use for NormalDistribution
using namespace Christine::UtilityFunctions; // enable the use of mesh array
using namespace std;


namespace Christine
{
	namespace Calculations
	{
		class ExactSolution: public PriceFormula
		{
		private:
			void init();	// Initialise all default values
			NormalDistribution* myNormal; // composition member class points to the NormalDistribution, will need this for cdf and pdf

			// determine if it is call or put option
			bool IsCall(const OptionData& OD) const;
			bool IsCall(const int& option_type1) const;

			// the two d inputs into the normal distribution function by letting user pass in each parameter
			double d1(const double& S, const double& K, const double& r, const double& T, const double& sig, const double& b) const;
			double d2(const double& S, const double& K, const double& r, const double& T, const double& sig, const double& b) const;

			// the normal distribution function
			double norm_cdf(const double& dx) const;  // Standard cumulative normal(Gaussian) distribution function
			double norm_pdf(const double& dx) const;  // Probability distribution function

			// all of these private data members will be used when calculate the put/call option price
			// I don't intend to let the user type in any of these, so I keep them private

		public:
			// Constructors & Destructor
			ExactSolution(); // Default constructor
			ExactSolution(const ExactSolution& copy);	// Copy constructor
			ExactSolution& operator = (const ExactSolution& source); // Assignment operator
			virtual ~ExactSolution();	// Destructor

			// Now we will have all the functions to calculate the price and delta

			// Call price calculation, passing the vector
			// override from the base class
			double CallPrice(const vector<double>& OP) const;

			// Put price calculation, passing the vector
			// override from the base class
			double PutPrice(const vector<double>& OP) const;

			// Calculate the CALL Delta by passing the vector
			double CallDelta(const vector<double>& OP) const;

			// Calculate the PUT Delta by passing the vector
			double PutDelta(const vector<double>& OP) const;

			// Calculate the GAMMA by passing the vector
			double Gamma(const vector<double>& OP) const;

			// Calculate the Vega by passing the vector
			double Vega(const vector<double>& OP) const;

			// Calculate the Theta by passing the vector
			double Theta(const vector<double>& OP) const;

			//Check the Put-call parity satisfaction
			//This is to make sure that a given set of put/call prices satisfy parity
			// This will use the call/put price to calculate the corresponding call/put price
			// The first parameter will pass in all the needed data to calculate the option price, the second pass in the other option's price(call/put)
			// The final parameter helps us to determine the type: CALL or PUT
			double PutCallParity(const vector<double>& OP, const double& other_option_price, const int& option_type) const;  

			// The below functions are to calculate the Call price with passing into different parameters, should be also used
			// to make the matrix
			double CallPrice_S(const double& S, const vector<double>& OP) const; // call price with passing the different S
			double CallPrice_K(const double& K, const vector<double>& OP) const; // call price with passing the different K
			double CallPrice_T(const double& T, const vector<double>& OP) const; // call price with passing the different T
			double CallPrice_sig(const double& sig, const vector<double>& OP) const; // call price with passing the different sig
			double CallPrice_r(const double& r, const vector<double>& OP) const; // call price with passing the different r
			double CallPrice_b(const double& b, const vector<double>& OP) const; // call price with passing the different b

			// The below functions are to calculate the Put price with passing into different parameters, should be also used
			// to make the matrix
			double PutPrice_S(const double& S, const vector<double>& OP) const; // put price with passing the different S
			double PutPrice_K(const double& K, const vector<double>& OP) const; // put price with passing the different K
			double PutPrice_T(const double& T, const vector<double>& OP) const; // put price with passing the different T
			double PutPrice_sig(const double& sig, const vector<double>& OP) const; // put price with passing the different sig
			double PutPrice_r(const double& r, const vector<double>& OP) const; // put price with passing the different r
			double PutPrice_b(const double& b, const vector<double>& OP) const; // put price with passing the different b

			// The below functions are to calculate the Call Delta with passing into different parameters, should be also used
			// to make the matrix
			double CallDelta_S(const double& S, const vector<double>& OP) const; // Call Delta with passing the different S
			double CallDelta_K(const double& K, const vector<double>& OP) const; // Call Delta with passing the different S
			double CallDelta_T(const double& T, const vector<double>& OP) const; // Call Delta with passing the different S
			double CallDelta_sig(const double& sig, const vector<double>& OP) const; // Call Delta with passing the different S
			double CallDelta_r(const double& r, const vector<double>& OP) const; // Call Delta with passing the different S
			double CallDelta_b(const double& b, const vector<double>& OP) const; // Call Delta with passing the different S

			// The below functions are to calculate the Put Delta with passing into different parameters, should be also used
			// to make the matrix
			double PutDelta_S(const double& S, const vector<double>& OP) const; // put Delta with passing the different S
			double PutDelta_K(const double& K, const vector<double>& OP) const; // put Delta with passing the different S
			double PutDelta_T(const double& T, const vector<double>& OP) const; // put Delta with passing the different S
			double PutDelta_sig(const double& sig, const vector<double>& OP) const; // put Delta with passing the different S
			double PutDelta_r(const double& r, const vector<double>& OP) const; // put Delta with passing the different S
			double PutDelta_b(const double& b, const vector<double>& OP) const; // put Delta with passing the different S

			// The below functions are to calculate the Gamma with passing into different parameters, should be also used
			// to make the matrix
			double Gamma_S(const double& S, const vector<double>& OP) const; // Gamma with passing the different S
			double Gamma_K(const double& K, const vector<double>& OP) const; // Gamma with passing the different K
			double Gamma_T(const double& T, const vector<double>& OP) const; // Gamma with passing the different T
			double Gamma_sig(const double& sig, const vector<double>& OP) const; // Gamma with passing the different sig
			double Gamma_r(const double& r, const vector<double>& OP) const; // Gamma with passing the different r
			double Gamma_b(const double& b, const vector<double>& OP) const; // Gamma with passing the different b
		};

	}
}

#endif