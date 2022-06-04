#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP
#include "AllOptions.h"
#include "OptionData.h"
#include "ExactSolution.h"
#include "NormalDistribution.h"
using namespace Christine::Calculations;
using namespace std;
namespace Christine
{
	namespace Options
	{
		class EuropeanOption: public AllOptions
		{
		private:
			void init();	// Initialize all default values
			ExactSolution* mySolution; // point to the exact solution formula, get the exact solution for this European Option

			// The following are to approximate first and second-order derivatives in S
			// by 3-point second order approximations
			// later will be accessed by using a function in public
			virtual double CallDeltaApproximate(const double& h) const; // calculate call delta approximate
			virtual double PutDeltaApproximate(const double& h) const; // calculate call delta approximate
			virtual double CallGammaApproximate(const double& h) const; // calculate call gamma approximate
			virtual double PutGammaApproximate(const double& h) const; // calculate put gamma approximate

		public:
			// Constructors
			EuropeanOption();  // Default constructor
			virtual ~EuropeanOption();	// Destructor
			EuropeanOption(const OptionData& OD);  // constructor with OptionData
			EuropeanOption(const OptionData& OD, const double& b);  // overloaded constructor with OptionData
			EuropeanOption(const EuropeanOption& copy);  // Copy constructor
			EuropeanOption& operator = (const EuropeanOption& source);  // Assignment operator

			// Functions that get the option price
			double Price() const;
			// overloaded price function that will print out the option price depends on the parameter we changed
			double Price(const double& val, const int& type, const bool& parity) const;
			// function that calculate option price with passing in the different parameter
			double Price_S(const double& S) const;
			double Price_K(const double& K) const;
			double Price_T(const double& T) const;
			double Price_r(const double& r) const;
			double Price_sig(const double& sig) const;
			double Price_b(const double& b) const;

			// This is specific vector of all the data member for European price, will be used to return the matrix
			vector<double> European_vector() const;

			// price function with underlying asset price vector as parameter 
			virtual vector<double> Price_S(const vector<double>& S_vec) const;
	
			//  Overloaded European Price matrix that will change gets the vector of changing parameter (one at a time), return the matrix of all the parameters, and the option price
			virtual vector<vector<double>> Price_Matrix(const vector<double>& param, const int& type) const;

			// Overloaded European Price matrix that receive the parameter matrix as an input, and return the matrix of price (both put and call) as the output
			virtual vector<vector<double>> Price_Matrix(const vector<vector<double>>& param_matrix, const int& type) const;

			// Functions to get the sensitivities
			double Delta() const; // return the Delta by using a pointer to the ExactSolution
			// overloaded delta function that will print out the option price depends on the parameter we changed
			double Delta(const double& val, const int& type, const bool& parity) const;
			// function that calculate Delta with passing in the different parameter
			double Delta_S(const double& S) const;
			double Delta_K(const double& K) const;
			double Delta_T(const double& T) const;
			double Delta_r(const double& r) const;
			double Delta_sig(const double& sig) const;
			double Delta_b(const double& b) const;

			virtual vector<double> Delta_S(const vector<double>& S_vec) const; //Delta function with underlying asset price vector as parameter 
			
			// Overloaded European Delta matrix that will change gets the vector of changing parameter (one at a time), return the matrix of all the parameters, and the Delta
			virtual vector<vector<double>> European_Delta_Matrix(const vector<double>& param, const int& type) const;

			// Overloaded European Delta matrix that receive the parameter matrix as an input, and return the matrix of Delta (both put and call) as the output
			virtual vector<vector<double>> European_Delta_Matrix(const vector<vector<double>>& param_matrix, const int& type) const;


			double GetGamma() const; // return the Gamma by using a pointer to the ExactSolution
			// function that calculate Gamma with passing in the different parameter
			double GetGamma_S(const double& S) const;
			double GetGamma_K(const double& K) const;
			double GetGamma_T(const double& T) const;
			double GetGamma_r(const double& r) const;
			double GetGamma_sig(const double& sig) const;
			double GetGamma_b(const double& b) const;
			// Overloaded European Gamma matrix that will change gets the vector of changing parameter (one at a time), return the matrix of all the parameters, and the Gamma
			virtual vector<vector<double>> European_Gamma_Matrix(const vector<double>& param, const int& type) const;

			// Overloaded European Delta matrix that receive the parameter matrix as an input, and return the matrix of Gamma as the output
			virtual vector<vector<double>> European_Gamma_Matrix(const vector<vector<double>>& param_matrix, const int& type) const;

			double GetVega() const;
			double GetTheta() const;
			double DeltaApproximate(const double& x) const; // this function will take a parameter from the user and return the Approximate value of Delta
			double GammaApproximate(const double& x) const; // this function will take a parameter from the user and return the Approximate value of Gamma

			//These are two ways to meet the Put-call parity Satisfication
			double EuropeanPutCallParity(const EuropeanOption& otherOP) const;   // This will use the call/put price to calculate the corresponding call/put price
			bool IsEuropeanPutCallParity(const EuropeanOption& otherOP, const double& error_boundary) const;  // bool func to check if a given set of put/call prices prices satisfy parity

			// Modifier functions
			void toggle();		// Change option type (C/P, P/C)

		};
	}
}
#endif