// The perpetual price is the time-homogeneous price and is the same as the normal price
// expiry price T tends to infinity, so in both put and call option price calculations, we don't focus on T
// An American option is a contract that can be exercised at any time prior to T
#ifndef PerpetualAmericanOption_hpp
#define PerpetualAmericanOption_hpp

#include "AllOptions.h"
#include "OptionData.h"
#include "PerpetualSolution.h"
using namespace Christine::Calculations;

namespace Christine
{
	namespace Options
	{
		class PerpetualAmericanOption: public AllOptions
		{
		private:
		// private member data will include our call and put price
		// since these calculations of put and call price are unique for perpetual american option
		// we would do the calculation inside the class and declare them as the member data
			
			void init();	// Initialize all default values
			PerpetualSolution* mySolution; // point to the exact solution formula, get the exact solution for this European Option
		
		public:

			// Constructors, Destructor, and Assignment Operator
			PerpetualAmericanOption();  // Default constructor
			virtual ~PerpetualAmericanOption();	// Destructor
			PerpetualAmericanOption(const OptionData& OD); // constructor with OptionData
			PerpetualAmericanOption(const OptionData& OD, const double& b); // overloaded constructor with OptionData
			PerpetualAmericanOption(const PerpetualAmericanOption& copy);  // Copy constructor
			PerpetualAmericanOption& operator = (const PerpetualAmericanOption& source);  // Assignment operator

			// This is specific vector of all the data member for European price, will be used to return the matrix
			vector<double> American_vector() const;

			// Functions that get the option price
			double Price() const;
			// overloaded price function that will print out the option price depends on the parameter we changed
			double Price(const double& val, const int& type, const bool& parity) const;

			// price function with underlying asset price vector as parameter 
			virtual vector<double> Price_S(const vector<double>& S_vec) const; 

			//  Overloaded European Price matrix that will change gets the vector of changing parameter (one at a time), return the matrix of all the parameters, and the option price
			virtual vector<vector<double>> Price_Matrix(const vector<double>& param, const int& type) const;

			// Overloaded European Price matrix that receive the parameter matrix as an input, and return the matrix of price (both put and call) as the output
			virtual vector<vector<double>> Price_Matrix(const vector<vector<double>>& param_matrix, const int& type) const;


			// function that calculate option price with passing in the different parameter
			double Price_S(const double& S) const;
			double Price_K(const double& K) const;
			double Price_r(const double& r) const;
			double Price_sig(const double& sig) const;
			double Price_b(const double& b) const;

			// The following functions will not be used here currently
			virtual double Delta() const;// Get Delta
			virtual double GetGamma() const;// Get Gamma
			virtual double GetVega() const; // Get Vega
			virtual double GetTheta() const; // Get Theta
		};
	}
}
#endif
