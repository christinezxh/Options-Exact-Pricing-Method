#include "PerpetualAmericanOption.h"
#include <cmath>
namespace Christine
{
	namespace Options
	{

		void PerpetualAmericanOption::init()	// Initialise all default values
		{
			mySolution = new PerpetualSolution(); // pointer point to the PerpetualSolution, store in the heap
		}

		// Constructors, destructor, and assignment operator
		PerpetualAmericanOption::PerpetualAmericanOption(): AllOptions() { init(); }  // Default constructor, call the base class
		PerpetualAmericanOption::~PerpetualAmericanOption() { delete mySolution; }	// Destructor, delete the pointer
		PerpetualAmericanOption::PerpetualAmericanOption(const OptionData& OD): AllOptions(OD) { init(); } // constructor with OptionData
		PerpetualAmericanOption::PerpetualAmericanOption(const OptionData& OD, const double& b): AllOptions(OD,b) { init(); } // overloaded constructor with OptionData
		PerpetualAmericanOption::PerpetualAmericanOption(const PerpetualAmericanOption& copy): AllOptions(copy) // Copy constructor
		{ 
			mySolution = new PerpetualSolution();
			*mySolution = *copy.mySolution; // dereferencing the pointer
		}
		PerpetualAmericanOption& PerpetualAmericanOption::operator = (const PerpetualAmericanOption& source)  // Assignment operator
		{
			// Call the base class assignment operator
			// make sure correctly inherited from base class
			AllOptions::operator = (source);

			// preclude self-assignment
			if (this == &source) return *this;

			mySolution = new PerpetualSolution();
			*mySolution = *source.mySolution; // dereferencing the pointer
		}

		// Functions that get the option price
		double PerpetualAmericanOption::Price() const
		{
			// determine if it is a call or put option
			// The CalculateCall function is the function in ExactSolution
			if (IsCall())  // CALL Option
				return mySolution->CallPrice(this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutPrice(this->option_vector()); // these are vectors called from base class
		}

		// This is the overloaded Price function that will print out the option price depends on the parameter we changed
		double PerpetualAmericanOption::Price(const double& val, const int& type, const bool& parity) const
		{
			// parity will be used later in the matrix in order to print out the corresponding put/call price
			// logic: Call price: IsCall() is true and parity is false, or IsCall() is false and parity is true
			// Put price: IsCall() is false and parity is false, or IsCall() is true and parity is true
			switch (type)
			{
			case 0: // S
				if (IsCall() != parity) // CALL Option
					return mySolution->CalculateCall_S(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->CalculatePut_S(val, this->option_vector()); // these are vectors called from base class
			case 1: // K
				if (IsCall() != parity) // CALL Option
					return mySolution->CalculateCall_K(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->CalculatePut_K(val, this->option_vector()); // these are vectors called from base class
			case 2: // r
				if (IsCall() != parity) // CALL Option
					return mySolution->CalculateCall_r(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->CalculatePut_r(val, this->option_vector()); // these are vectors called from base class
			case 3: // sig
				if (IsCall() != parity) // CALL Option
					return mySolution->CalculateCall_sig(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->CalculatePut_sig(val, this->option_vector()); // these are vectors called from base class
			case 4: // b
				if (IsCall() != parity) // CALL Option
					return mySolution->CalculateCall_b(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->CalculatePut_b(val, this->option_vector()); // these are vectors called from base class
			}
		}

		// This is specific vector of all the data member for American Option, will be used to return the matrix
		vector<double> PerpetualAmericanOption::American_vector() const
		{
			vector<double> vec(7);
			// Assign each option parameter to vector
			vec[0] = m_S;
			vec[1] = m_K;
			vec[2] = m_r;
			vec[3] = m_sig;
			vec[4] = m_b;
			vec[5] = Price();
			vec[6] = Price();

			return vec;
		}

		vector<double> PerpetualAmericanOption::Price_S(const vector<double>& S_vec) const // price function with underlying asset price vector as parameter 
		{
			vector<double> OptionPrice_vec; // create a vector to store the option prices corresponding to each element in underlying asset price vector
			for (int i = 0; i < S_vec.size(); ++i)
			{
				OptionPrice_vec.push_back(Price_S(S_vec[i])); // calculate the option price for the given underlying stock price, and push it into the option price vector
			}
			return OptionPrice_vec;
		}

		// This Matrix function receives the vector as an input, the vector changes each parameter at a time
				// and depend on the type of the input parameter(S,K,r,T...), print out each batch as a matrix
		vector<vector<double>> PerpetualAmericanOption::Price_Matrix(const vector<double>& param, const int& type) const
		{
			size_t row_size = param.size(); // this will be the number of rows of this matrix depend on the size of the input vector
			vector<vector<double>> all_parameter_matrix(row_size, American_vector()); // European vector will be used here
			for (int n = 0; n < param.size(); ++n)
			{
				switch (type)
				{
				case 0: // S
					all_parameter_matrix[n][0] = param[n]; // n is the row number, increases up to the size of the input vector
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_sig;
					all_parameter_matrix[n][4] = m_b;
					all_parameter_matrix[n][5] = Price(param[n], 0, false); // store one of the price in the 7th column
					all_parameter_matrix[n][6] = Price(param[n], 0, true); // store the other price in the 8th column
					break;
				case 1: // K
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = param[n];
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_sig;
					all_parameter_matrix[n][4] = m_b;
					all_parameter_matrix[n][5] = Price(param[n], 1, false);
					all_parameter_matrix[n][6] = Price(param[n], 1, true);
					break;
				case 2: //r
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = param[n];
					all_parameter_matrix[n][3] = m_sig;
					all_parameter_matrix[n][4] = m_b;
					all_parameter_matrix[n][5] = Price(param[n], 2, false);
					all_parameter_matrix[n][6] = Price(param[n], 2, true);
					break;
				case 3: //sig
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = param[n];
					all_parameter_matrix[n][4] = m_b;
					all_parameter_matrix[n][5] = Price(param[n], 3, false);
					all_parameter_matrix[n][6] = Price(param[n], 3, true);
					break;
				case 4://b
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_sig;
					all_parameter_matrix[n][4] = param[n];
					all_parameter_matrix[n][5] = Price(param[n], 4, false);
					all_parameter_matrix[n][6] = Price(param[n], 4, true);
					break;
				}
			}
			return all_parameter_matrix;
		}
		// Overloaded European matrix that receive the parameter matrix as an input, and return the matrix of price (both put and call) as the output
		vector<vector<double>> PerpetualAmericanOption::Price_Matrix(const vector<vector<double>>& param_matrix, const int& type) const // type will be specify by user
		{
			vector<vector<double>> OptionPrice_matrix(param_matrix.size()); // create an option price matrix corresponding to the input parameter matrix 
			for (int n = 0; n < param_matrix.size(); ++n)
			{
				switch (type) // depends on the type being tested, we switch the output matrix
				{
				case 0: // S
					OptionPrice_matrix[n].push_back(param_matrix[n][0]); // we utilize push_back here because the original matrix does not have any values
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][0], 0, false));
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][0], 0, true));
					break;
				case 1: // K
					OptionPrice_matrix[n].push_back(param_matrix[n][1]);
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][1], 1, false));
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][1], 1, true));
					break;
				case 2: // r
					OptionPrice_matrix[n].push_back(param_matrix[n][2]);
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][2], 2, false));
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][2], 2, true));
					break;
				case 3: // sig
					OptionPrice_matrix[n].push_back(param_matrix[n][3]);
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][3], 3, false));
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][3], 3, true));
					break;
				case 4: // b
					OptionPrice_matrix[n].push_back(param_matrix[n][4]);
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][4], 4, false));
					OptionPrice_matrix[n].push_back(Price(param_matrix[n][4], 4, true));
					break;
				}
			}
			return OptionPrice_matrix;
		}
																							
		// below are the functions that calculate option price with passing in the different parameter
		double PerpetualAmericanOption::Price_S(const double& S) const
		{
			if (IsCall())  // CALL Option
				return mySolution->CalculateCall_S(S, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->CalculatePut_S(S, this->option_vector()); // these are vectors called from base class
		}
		double PerpetualAmericanOption::Price_K(const double& K) const
		{
			if (IsCall())  // CALL Option
				return mySolution->CalculateCall_K(K, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->CalculatePut_K(K, this->option_vector()); // these are vectors called from base class
		}
		double PerpetualAmericanOption::Price_r(const double& r) const
		{
			if (IsCall())  // CALL Option
				return mySolution->CalculateCall_r(r, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->CalculatePut_r(r, this->option_vector()); // these are vectors called from base class
		}
		double PerpetualAmericanOption::Price_sig(const double& sig) const
		{
			if (IsCall())  // CALL Option
				return mySolution->CalculateCall_sig(sig, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->CalculatePut_sig(sig, this->option_vector()); // these are vectors called from base class
		}
		double PerpetualAmericanOption::Price_b(const double& b) const
		{
			if (IsCall())  // CALL Option
				return mySolution->CalculateCall_b(b, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->CalculatePut_b(b, this->option_vector()); // these are vectors called from base class
		}

		// these functions currently do not have any use inside American Option
		double PerpetualAmericanOption::Delta() const { return -1; }  // Get Delta
		double PerpetualAmericanOption::GetGamma() const { return -1; }  // Get Gamma
		double PerpetualAmericanOption::GetVega() const { return -1; }  // Get Gamma
		double PerpetualAmericanOption::GetTheta() const { return -1; }  // Get Theta
	}
}