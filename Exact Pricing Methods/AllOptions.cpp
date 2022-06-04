#include "AllOptions.h"
#include <sstream> // to create ToString()

namespace Christine
{
	namespace Options
	{
		// I decided to initialize the base class in two ways
		// One is to let the model decides what the cost of carry is, detailed description is given in the b_model()
		// The other one lets the user to type in the b if not using those models
		// This is useful especially when we calculate the Perpetual American Option
		void AllOptions::Init(const OptionData& OD)   // Initialize the base class
		{
			m_S = OD.S;
			m_K = OD.K;
			m_T = OD.T;
			m_r = OD.r;
			m_sig = OD.sig;
			m_type = OD.type;
			m_model = OD.model;
			m_b = b_model(); // b_model () is a function defined and implemented in AllOptions class, help to determine the m_b
			m_D = OD.D;

			m_option_data = new OptionData(OD);  // Init pointer to OptionData class
		}

		void AllOptions::Init(const OptionData& OD, const double& b) // overloaded Initializing base class
		// This will be used to assign the b by user
		{
			m_S = OD.S;
			m_K = OD.K;
			m_T = OD.T;
			m_r = OD.r;
			m_sig = OD.sig;
			m_type = OD.type;
			m_model = OD.model;
			m_D = OD.D;
			m_b = b; // make sure that user could directly assign the cost of carry

			m_option_data = new OptionData(OD);  // Init pointer to OptionData class
		}
		// Constructors, destructor, and assignment operator
		AllOptions::AllOptions() :m_S(0), m_K(0), m_T(0), m_r(0), m_sig(0), m_b(0),m_type(0), m_model(0), m_D(0) {} // constructor
		AllOptions::~AllOptions() { delete m_option_data; } // destructor
		// copy constructor
		AllOptions::AllOptions(const AllOptions& copy): m_S(copy.m_S), m_K(copy.m_K), m_T(copy.m_T), m_r(copy.m_r), m_sig(copy.m_sig), m_model(copy.m_model), m_b(copy.m_b), m_D(copy.m_D),m_type(copy.m_type)
		{ 
			m_option_data = new OptionData(copy.option_data());  // copy the pointer to optiondata struct
			*m_option_data = *copy.m_option_data;  // Copy data from existing pointer to new pointer
		}
		AllOptions::AllOptions(const OptionData& o) {Init(o);} //Overload constructor to intialize all the value
		AllOptions::AllOptions(const OptionData& o, const double& b){ Init(o,b); } // overloaded constructor, assign the b by user

		AllOptions& AllOptions::operator = (const AllOptions& source) // Assignment operator
		{
			// preclude self-assignment
			if (this == &source) return *this;

			m_S = source.m_S;
			m_K = source.m_K;
			m_T = source.m_T;
			m_r = source.m_r;
			m_sig = source.m_sig;
			m_model = source.m_model;
			m_b = source.m_b;
			m_D = source.m_D;
			m_type = source.m_type;

			m_option_data = new OptionData(source.option_data());  // copy the pointer to optiondata struct
			*m_option_data = *source.m_option_data;  // Copy data from existing pointer to new pointer
		} 

		// will return 1 if it is call option
		bool AllOptions::IsCall() const
		{
			return m_type == 1;
		}

		// Underlying asset price
		// Getter member-function for m_S
		double AllOptions::S() const { return m_S; }

		// Strike price
		// Getter member-function for m_K
		double AllOptions::K() const { return m_K; }

		// Expiry date
		// Getter member-function for m_T
		double AllOptions::T() const { return m_T; }

		// Risk free Interest rate
		// Getter member-function for m_r
		double AllOptions::r() const { return m_r; }

		// Volatility
		// Getter member-function for m_sig
		double AllOptions::sig() const { return m_sig; }

		// Dividend
		// Getter member-function for m_D
		double AllOptions::D() const { return m_D; }

		int AllOptions::model() const { return m_model; }

		// Getter for m_b
		double AllOptions::b() const { return m_b; }

		// model to determine the cost of carry
		double AllOptions::b_model() const
		{

			double tmp;
			if (m_model == 1) // black-scholes option model
			{
				tmp = m_r;
			}else if (m_model == 2)  // morton model with continuous dividend yield D
			{
				tmp = m_r - m_D;
			}
			else if (m_model == 3) // balck-scholes futures option model
			{
				tmp = 0;
			}
			return tmp;
		}

		// Getter for type
		int AllOptions::type() const { return m_type; }

		// Getter member-function for m_option_data
		// Returns m_option_data from OptionData class
		// later we could use this to store the data
		OptionData& AllOptions::option_data() const 
		{
			return *m_option_data;
		}

		// Returns data member m_option_data in the form of a vector
		vector<double> AllOptions::option_vector() const
		{
			vector<double> vec(6);
			// Assign each option parameter to vector
			vec[0] = m_S;
			vec[1] = m_K;
			vec[2] = m_r;
			vec[3] = m_T;
			vec[4] = m_sig;
			vec[5] = m_b;

			return vec;
		}

		// Underlying asset price
		// Setter for m_S
		void AllOptions::S(const double& _S) { m_S = _S; }

		// Strike price
		// Setter  for m_K
		void AllOptions::K(const double& _K) { m_K = _K; }

		// Expiry Date
		// Setter for m_T
		void AllOptions::T(const double& _T) { m_T = _T; }

		// Risk free Interest rate
		// Setter for m_r
		void AllOptions::r(const double& _r) { m_r = _r; }

		// Volatility
		// Setter for m_sig
		void AllOptions::sig(const double& _sig) { m_sig = _sig; }

		// Dividend
		// Setter for m_D
		void AllOptions::D(const double& _D) { m_D = _D; }

		// Setter for type
		void AllOptions::type(const int& t1) { m_type = t1; }

		
	}
}