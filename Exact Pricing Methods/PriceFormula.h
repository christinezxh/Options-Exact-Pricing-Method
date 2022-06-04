// This class is the abstract base class for all the pricing formula (2 pure virtual functions)
// This class will not have much operations in this project, but for future reusability, we expect to have more pricing formula
// since this is a small base class, I decide to put both declaration and implementation in the header file for simplicity
#ifndef PriceFormula_HPP
#define PriceFormula_HPP

#include <iostream>
#include <vector>
using namespace::std;

namespace Christine
{
	namespace Calculations
	{
		class PriceFormula
		{
		public:
			// Constructors, destructor, and Assignment Operator
			PriceFormula(){} // Default constructor
			PriceFormula(const PriceFormula& copy){}	// Copy constructor
			PriceFormula& operator = (const PriceFormula& source) // Assignment operator
			{
				// make sure preclude self-assignment
				if (this == &source) return *this;

				return *this;
			}
			virtual ~PriceFormula(){}	// Destructor

			// these two virtual functions will be later override in the derived class
			// get call and put option price
			virtual double CallPrice(const vector<double>& OP) const = 0;
			virtual double PutPrice(const vector<double>& OP) const = 0;

		};

	}
}

#endif