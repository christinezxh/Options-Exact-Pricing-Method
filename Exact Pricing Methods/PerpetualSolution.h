// This class will be the derived class of PriceFormula
// This class will do all the necessary calculations for the Perpetual American Option (exception of American Option)
// This class's calculation will return the exact solution

#ifndef PerpetualSolution_HPP
#define PerpetualSolution_HPP

#include "PriceFormula.h"
#include "OptionData.h"
#include <vector>

namespace Christine
{
	namespace Calculations
	{
		class PerpetualSolution : public PriceFormula
		{
		private:
			// currently no private data member
		public:
			// Constructors, destructor, and Assignment Operator
			PerpetualSolution();// Default constructor
			PerpetualSolution(const PerpetualSolution& copy);	// Copy constructor
			PerpetualSolution& operator = (const PerpetualSolution& source); // Assignment operator
			virtual ~PerpetualSolution();// Destructor

			// The following two functions calculate the Option Price for American Perpetual Option
			// override from the base class
			double CallPrice(const vector<double>& OP) const;  // calculate the PUT price, getting data from vector
			double PutPrice(const vector<double>& OP) const;  // calculate the CALL price, getting data from vector

			// The below functions are to calculate the Call price with passing into different parameters, should be also used
			// to make the matrix
			double CalculateCall_S(const double& S, const vector<double>& OP) const; // call price with passing the different S
			double CalculateCall_K(const double& K, const vector<double>& OP) const; // call price with passing the different K
			double CalculateCall_sig(const double& sig, const vector<double>& OP) const; // call price with passing the different sig
			double CalculateCall_r(const double& r, const vector<double>& OP) const; // call price with passing the different r
			double CalculateCall_b(const double& b, const vector<double>& OP) const; // call price with passing the different b

			// The below functions are to calculate the Put price with passing into different parameters, should be also used
			// to make the matrix
			double CalculatePut_S(const double& S, const vector<double>& OP) const; // put price with passing the different S
			double CalculatePut_K(const double& K, const vector<double>& OP) const; // put price with passing the different K
			double CalculatePut_sig(const double& sig, const vector<double>& OP) const; // put price with passing the different sig
			double CalculatePut_r(const double& r, const vector<double>& OP) const; // put price with passing the different r
			double CalculatePut_b(const double& b, const vector<double>& OP) const; // put price with passing the different b
		};
	}
}
#endif