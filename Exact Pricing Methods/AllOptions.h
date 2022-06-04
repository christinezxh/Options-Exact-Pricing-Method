// This is the abstract base class of options
// This class currently have two derived classes: European Option and American Option
// In the future, this class might contain more option derived class
// All the data that this class used will be passed by OptionData class later in the main program
#include <string>
#include <iostream>
#include <vector>
#include "OptionData.h"
#include "NormalDistribution.h"

#ifndef AllOptions_hpp
#define AllOptions_hpp

using namespace std;

namespace Christine
{
	namespace Options
	{
		class AllOptions
		{
		private:
			OptionData* m_option_data;  // Pointer to the OptionData class
			void Init(const OptionData& OD);	// This will initialize the values
			void Init(const OptionData& OD, const double& b);	// This will be used to assign the b by user

		protected:
			double m_S;     // Underlying Asset Pirce
			double m_r;		// Risk free Interest rate
			double m_sig;	// Volatility
			double m_K;		// Strike price
			double m_T;		// Expiry date
			double m_b;		// Cost of carry
			double m_D;     // Dividend
			int m_type;     // 0 for put,1 for call
			int m_model;    // 1 for Black-Scholes stock option; 2 for Morton model; 3 for Black-Scholes future option; 4 for currency option 

		public:
			AllOptions(); // constructor
			virtual ~AllOptions(); // destructor
			AllOptions(const OptionData& o);  // constructor with OptionData class 
			AllOptions(const OptionData& o, const double& b); // overloaded constructor with user assigning the b;
			// This overloaded constructor could be really useful with American Option
			AllOptions(const AllOptions& copy); // copy constructor

			AllOptions& operator = (const AllOptions& source); // Assignment operator

			// Core functions that must be implemented in all derived classes
			// both European and American option would use them, so delcare as pure virtual in the base class
			// the usage of these functions will be described in the derived class
			virtual double Price() const = 0; // Get price
			virtual double Delta() const = 0; // Get Delta
			virtual double GetGamma() const = 0; // Get Gamma
			virtual double GetVega() const = 0; // Get Vega
			virtual double GetTheta() const = 0; // Get Vega

			// below are the functions that will change one parameter as to calculate the price
			virtual double Price(const double& val, const int& type, const bool& parity) const = 0;
			virtual double Price_S(const double& S) const = 0;
			virtual double Price_K(const double& K) const = 0;
			virtual double Price_r(const double& r) const = 0;
			virtual double Price_sig(const double& sig) const = 0;
			virtual double Price_b(const double& b) const = 0;
			// below are the vector and matrix functions
			virtual vector<double> Price_S(const vector<double>& S_vec) const = 0;
			virtual vector<vector<double>> Price_Matrix(const vector<double>& param, const int& type) const = 0;
			virtual vector<vector<double>> Price_Matrix(const vector<vector<double>>& param_matrix, const int& type) const = 0;

			virtual bool IsCall() const;  // will return 1 if it is call option

			// Below are the getter for all the member data
			// Underlying asset price
			// Getter for m_S
			virtual double S() const;

			// Strike price
			// Getter for m_K
			virtual double K() const;

			// Expiry date
			// Getter for m_T
			virtual double T() const;

			// Risk free Interest rate
			// Getter for m_r
			virtual double r() const;

			// Volatility
			// Getter for m_sig
			virtual double sig() const;

			// Dividend
			// Getter for m_sig
			virtual double D() const;

			// Model Type
			// Getter for m_model
			virtual int model() const;

			// Option type
			// Getter for m_type
			virtual int type() const;

			// Getter for m_b
			virtual double b() const;

			// Getter for cost of carry (m_b)
			// This is to determine which model we will be using
			virtual double b_model() const;

			// Getter for m_option_data
			// it will return m_option_data from OptionData class
			// later we could use this to store the data
			virtual OptionData& option_data() const;

			// Getter that will return m_option_data in the form of a vector
			virtual vector<double> option_vector() const;

			// Below are the setters for all the member data

			// Underlying stock price
			// Setter for m_S
			virtual void S(const double& _S);

			// Strike price
			// Setter for m_K
			virtual void K(const double& _K);

			// Expiry Date
			// Setter for m_T
			virtual void T(const double& _T);

			// Risk free Interest rate
			// Setter for m_r
			virtual void r(const double& _r);

			// Volatility
			// Setter for m_sig
			virtual void sig(const double& _sig);

			// Dividend
			// Setter for m_D
			virtual void D(const double& _D);

			// Option type
			// Setter for m_type
			virtual void type(const int& t1);

		};
	}
}
#endif

