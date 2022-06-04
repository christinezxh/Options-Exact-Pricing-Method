#include "EuropeanOption.h"
#include <cmath>
#include <iostream>
#include <boost/math/distributions/normal.hpp>  // Normal distribution header file
using namespace boost::math; // Don't forget to tell compiler which namespace
using namespace Christine::Statistics;

namespace Christine
{
	namespace Options
	{
		void EuropeanOption::init()	// Initialize all default values
		{
			mySolution = new ExactSolution(); // pointer point to the ExactSolution, store in the heap
		}

		// The following are to approximate first and second-order derivatives in S
		// by 3-point second order approximations
		double EuropeanOption::CallDeltaApproximate(const double& h) const
		{
			// We declare these as vectors in order to return tese objects' option parameters as a vector
			vector<double> Parameter_Plus = this->option_vector();
			Parameter_Plus[0] += h;  // S+h

			vector<double> Parameter_Minus = this->option_vector(); 
			Parameter_Minus[0] -= h;  // S-h

				// now we calculate the approximate for Call Delta
			double Result_Plus = mySolution->CallPrice(Parameter_Plus);  // This would be like V(S+h) or Option_Price(S+h)
			double Result_Minus = mySolution->CallPrice(Parameter_Minus);  // This would be like V(S-h) or Option_Price(S-h)

			return (Result_Plus - Result_Minus) / (2 * h);  // now we have (V(S+h) - V(S-h)) / (2h)
		}

		double EuropeanOption::PutDeltaApproximate(const double& h) const
		{
			// We declare these as vectors in order to return tese objects' option parameters as a vector
			vector<double> Parameter_Plus = this->option_vector();
			Parameter_Plus[0] += h;  // S+h

			vector<double> Parameter_Minus = this->option_vector();
			Parameter_Minus[0] -= h;  // S-h

			// now we calculate the approximate for Put Delta
			double Result_Plus = mySolution->PutPrice(Parameter_Plus);  // This would be like V(S+h) or Option_Price(S+h)
			double Result_Minus = mySolution->PutPrice(Parameter_Minus);  // This would be like V(S-h) or Option_Price(S-h)

			return (Result_Plus - Result_Minus) / (2 * h);  // now we have (V(S+h) - V(S-h)) / (2h)
		}

		double EuropeanOption::CallGammaApproximate(const double& h) const // Get call gamma approximate
		{
			// We declare these as vectors in order to return tese objects' option parameters as a vector
			vector<double> Parameter_Plus = this->option_vector(); 
			Parameter_Plus[0] += h;   // S+h

			vector<double> Parameter_Minus = this->option_vector();
			Parameter_Minus[0] -= h;  // S-h


				// now we calculate the approximate for Call Gamma
			double Result_Plus = mySolution->CallPrice(Parameter_Plus);  // This would be like V(S+h) or Option_Price(S+h)
			double Result_Minus = mySolution->CallPrice(Parameter_Minus);  // This would be like V(S-h) or Option_Price(S-h)
			double Result_2vs = mySolution->CallPrice(this->option_vector()) * 2;  // This would be like 2*V(S)

			return (Result_Plus + Result_Minus - Result_2vs) / (h * h);  //Calculate the apprxoiamte gamma call option price
		}

		double EuropeanOption::PutGammaApproximate(const double& h) const // Get put gamma approximate
		{
			// We declare these as vectors in order to return tese objects' option parameters as a vector
			vector<double> Parameter_Plus = this->option_vector();
			Parameter_Plus[0] += h;   // S+h

			vector<double> Parameter_Minus = this->option_vector();
			Parameter_Minus[0] -= h;  // S-h


				// now we calculate the approximate for PUT Gamma
			double Result_Plus = mySolution->PutPrice(Parameter_Plus);  // This would be like V(S+h) or Option_Price(S+h)
			double Result_Minus = mySolution->PutPrice(Parameter_Minus);  // This would be like V(S-h) or Option_Price(S-h)
			double Result_2vs = mySolution->PutPrice(this->option_vector()) * 2;  // This would be like 2*V(S)

			return (Result_Plus + Result_Minus - Result_2vs) / (h * h);  //Calculate the apprxoiamte gamma put option price

		}
	
		// Constructors, Destructor, and Assignment Operator

		EuropeanOption::EuropeanOption() : AllOptions() { init(); }  // Default constructor, call the base class
		EuropeanOption::~EuropeanOption() { delete mySolution; }	// Destructor, delete the pointer
		EuropeanOption::EuropeanOption(const OptionData& OD) : AllOptions(OD) { init(); }   // Overload constructor with OptionData
		EuropeanOption::EuropeanOption(const OptionData& OD, const double& b): AllOptions(OD,b) { init(); }  // overloaded constructor with OptionData
		EuropeanOption::EuropeanOption(const EuropeanOption& copy) : AllOptions(copy) // Copy constructor
		{ 
			mySolution = new ExactSolution();
			*mySolution = *copy.mySolution; // dereferencing the pointer
		}  
		EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source)  // Assignment operator
		{
			// Call the base class assignment operator
			// make sure correctly inherited from base class
			AllOptions::operator = (source);

			// Check to preclude self-assignment
			if (this == &source) return *this;

			mySolution = new ExactSolution();
			*mySolution = *source.mySolution; // dereferencing the pointer
		}

		// Functions that get the option price and sensitivities
		// Return the price of option
		double EuropeanOption::Price() const //Get the Option price
		{
			// determine if it is a call or put option
			// This is the function in ExactSolution
			if (IsCall()) // CALL Option
				return mySolution->CallPrice(this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutPrice(this->option_vector()); // these are vectors called from base class
		}
		// This is the overloaded Price function that will print out the option price depends on the parameter we changed
		double EuropeanOption::Price(const double& val, const int& type, const bool& parity) const
		{
			// parity will be used later in the matrix in order to print out the corresponding put/call price
			// logic: Call price: IsCall() is true and parity is false, or IsCall() is false and parity is true
			// Put price: IsCall() is false and parity is false, or IsCall() is true and parity is true
			switch (type) 
			{
			case 0: // S
				if (IsCall() != parity) // CALL Option
					return mySolution->CallPrice_S(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutPrice_S(val, this->option_vector()); // these are vectors called from base class
			case 1: // K
				if (IsCall() != parity) // CALL Option
					return mySolution->CallPrice_K(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutPrice_K(val, this->option_vector()); // these are vectors called from base class
			case 2: // r
				if (IsCall() != parity) // CALL Option
					return mySolution->CallPrice_r(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutPrice_r(val, this->option_vector()); // these are vectors called from base class
			case 3: // T
				if (IsCall() != parity) // CALL Option
					return mySolution->CallPrice_T(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutPrice_T(val, this->option_vector()); // these are vectors called from base class
			case 4: // sig
				if (IsCall() != parity) // CALL Option
					return mySolution->CallPrice_sig(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutPrice_sig(val, this->option_vector()); // these are vectors called from base class
			case 5: // b
				if (IsCall() != parity) // CALL Option
					return mySolution->CallPrice_b(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutPrice_b(val, this->option_vector()); // these are vectors called from base class
			}
		}

		// function that get option price with S as parameter
		double EuropeanOption::Price_S(const double& S) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallPrice_S(S, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutPrice_S(S, this->option_vector()); // these are vectors called from base class
		}

		vector<double> EuropeanOption::Price_S(const vector<double>& S_vec) const // overload price function with underlying asset price vector as parameter 
		{
			vector<double> OptionPrice_vec; // create a vector to store the option prices
			for (int i = 0; i < S_vec.size(); ++i)
			{
				OptionPrice_vec.push_back(Price_S(S_vec[i])); // calculate the option price for the given underlying stock price, and push it into the option price vector
			}
			return OptionPrice_vec;
		}

		// This is specific vector of all the data member for European Option, will be used to return the matrix
		// we will reassign the value to each position in the vector in the matrix, this is just to initialize the values
		// make sure we can rewrite it
		vector<double> EuropeanOption::European_vector() const
		{
			vector<double> vec(8);
			// Assign each option parameter to vector
			vec[0] = m_S;
			vec[1] = m_K;
			vec[2] = m_r;
			vec[3] = m_T;
			vec[4] = m_sig;
			vec[5] = m_b;
			vec[6] = Price();
			vec[7] = 0;

			return vec;
		}

		// This Matrix function receives the vector as an input, the vector changes each parameter at a time
		// and depend on the type of the input parameter(S,K,r,T...), print out each batch as a matrix
		vector<vector<double>> EuropeanOption::Price_Matrix(const vector<double>& param, const int& type) const
		{
			size_t row_size = param.size(); // this will be the number of rows of this matrix depend on the size of the input vector
			vector<vector<double>> all_parameter_matrix(row_size, European_vector()); // European vector will be used here
			for (int n = 0; n < param.size(); ++n)
			{
				switch (type)
				{
				case 0: // S
					all_parameter_matrix[n][0] = param[n]; // n is the row number, increases up to the size of the input vector
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Price(param[n],0,false); // store one of the price in the 7th column
					all_parameter_matrix[n][7] = Price(param[n],0,true); // store the other price in the 8th column
					break;
				case 1: // K
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = param[n];
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Price(param[n], 1, false);
					all_parameter_matrix[n][7] = Price(param[n], 1, true);
					break;
				case 2: //r
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = param[n];
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Price(param[n], 2, false);
					all_parameter_matrix[n][7] = Price(param[n], 2, true);
					break;
				case 3: // T
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = param[n];
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Price(param[n], 3, false);
					all_parameter_matrix[n][7] = Price(param[n], 3, true);
					break;
				case 4: //sig
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = param[n];
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Price(param[n], 4, false);
					all_parameter_matrix[n][7] = Price(param[n], 4, true);
					break;
				case 5://b
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = param[n];
					all_parameter_matrix[n][6] = Price(param[n], 5, false);
					all_parameter_matrix[n][7] = Price(param[n], 5, true);
					break;
				}
			}
			return all_parameter_matrix;
		}
		// Overloaded European matrix that receive the parameter matrix as an input, and return the matrix of price (both put and call) as the output
		vector<vector<double>> EuropeanOption::Price_Matrix(const vector<vector<double>>& param_matrix, const int& type) const // type will be specify by user
		{
			vector<vector<double>> OptionPrice_matrix(param_matrix.size()); // create an option price matrix corresponding to the input parameter matrix 
			for (int n = 0; n < param_matrix.size(); ++n)
			{
					switch (type) // depends on the type being tested, we switch the output matrix
					{
					case 0: // S
						OptionPrice_matrix[n].push_back(param_matrix[n][0]); // I utilize push_back here because the original matrix does not have any values
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][0], 0, false));
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][0], 0, true));
						break;
					case 1: // K
						OptionPrice_matrix[n].push_back(param_matrix[n][1]);
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][1],1,false));
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][1],1,true));
						break;
					case 2: // r
						OptionPrice_matrix[n].push_back(param_matrix[n][2]);
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][2], 2, false));
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][2], 2, true));
						break;
					case 3: // T
						OptionPrice_matrix[n].push_back(param_matrix[n][3]);
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][3], 3, false));
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][3], 3, true));
						break;
					case 4: // sig
						OptionPrice_matrix[n].push_back(param_matrix[n][4]);
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][4], 4, false));
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][4], 4, true));
						break;
					case 5: // b
						OptionPrice_matrix[n].push_back(param_matrix[n][5]);
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][5], 5, false));
						OptionPrice_matrix[n].push_back(Price(param_matrix[n][5], 5, true));
						break;
					}
			}
			return OptionPrice_matrix;
		}

		// function that get option price with K as parameter
		double EuropeanOption::Price_K(const double& K) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallPrice_K(K, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutPrice_K(K, this->option_vector()); // these are vectors called from base class
		}
		// function that get option price with T as parameter
		double EuropeanOption::Price_T(const double& T) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallPrice_T(T, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutPrice_T(T, this->option_vector()); // these are vectors called from base class
		}

		// function that get option price with r as parameter
		double EuropeanOption::Price_r(const double& r) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallPrice_r(r, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutPrice_r(r, this->option_vector()); // these are vectors called from base class
		}

		// function that get option price with T as parameter
		double EuropeanOption::Price_sig(const double& sig) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallPrice_sig(sig, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutPrice_sig(sig, this->option_vector()); // these are vectors called from base class
		}

		// function that get option price with T as parameter
		double EuropeanOption::Price_b(const double& b) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallPrice_b(b, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutPrice_b(b, this->option_vector()); // these are vectors called from base class
		}

		// return the Delta (sensitivity) of the option
		double EuropeanOption::Delta() const // get the Delta
		{
			// determine if it is a call or put option
			// This is the function in ExactSolution
			if (IsCall()) // CALL Option
				return mySolution->CallDelta(this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutDelta(this->option_vector()); // these are vectors called from base class
		}

		// This is the overloaded Delta function that will print out the option price depends on the parameter we changed
		double EuropeanOption::Delta(const double& val, const int& type, const bool& parity) const
		{
			// parity will be used later in the matrix in order to print out the corresponding put/call price
			// logic: Call: IsCall() is true and parity is false, or IsCall() is false and parity is true
			// Put: IsCall() is false and parity is false, or IsCall() is true and parity is true
			switch (type)
			{
			case 0: // S
				if (IsCall() != parity) // CALL Option
					return mySolution->CallDelta_S(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutDelta_S(val, this->option_vector()); // these are vectors called from base class
			case 1: // K
				if (IsCall() != parity) // CALL Option
					return mySolution->CallDelta_K(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutDelta_K(val, this->option_vector()); // these are vectors called from base class
			case 2: // r
				if (IsCall() != parity) // CALL Option
					return mySolution->CallDelta_r(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutDelta_r(val, this->option_vector()); // these are vectors called from base class
			case 3: // T
				if (IsCall() != parity) // CALL Option
					return mySolution->CallDelta_T(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutDelta_T(val, this->option_vector()); // these are vectors called from base class
			case 4: // sig
				if (IsCall() != parity) // CALL Option
					return mySolution->CallDelta_sig(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutDelta_sig(val, this->option_vector()); // these are vectors called from base class
			case 5: // b
				if (IsCall() != parity) // CALL Option
					return mySolution->CallDelta_b(val, this->option_vector()); // these are vectors called from base class
				else // PUT Option
					return mySolution->PutDelta_b(val, this->option_vector()); // these are vectors called from base class
			}
		}

		// This Matrix function receives the vector as an input, the vector changes each parameter at a time
			// and depend on the type of the input parameter(S,K,r,T...), print out each batch as a matrix
		vector<vector<double>> EuropeanOption::European_Delta_Matrix(const vector<double>& param, const int& type) const
		{
			size_t row_size = param.size(); // this will be the number of rows of this matrix depend on the size of the input vector
			vector<vector<double>> all_parameter_matrix(row_size, European_vector()); // European vector will be used here
			for (int n = 0; n < param.size(); ++n)
			{
				switch (type)
				{
				case 0: // S
					all_parameter_matrix[n][0] = param[n]; // n is the row number, increases up to the size of the input vector
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Delta(param[n], 0, false); // store one of the Delta in the 7th column
					all_parameter_matrix[n][7] = Delta(param[n], 0, true); // store the other Delta in the 8th column
					break;
				case 1: // K
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = param[n];
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Delta(param[n], 1, false);
					all_parameter_matrix[n][7] = Delta(param[n], 1, true);
					break;
				case 2: //r
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = param[n];
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Delta(param[n], 2, false);
					all_parameter_matrix[n][7] = Delta(param[n], 2, true);
					break;
				case 3: // T
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = param[n];
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Delta(param[n], 3, false);
					all_parameter_matrix[n][7] = Delta(param[n], 3, true);
					break;
				case 4: //sig
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = param[n];
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = Delta(param[n], 4, false);
					all_parameter_matrix[n][7] = Delta(param[n], 4, true);
					break;
				case 5://b
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = param[n];
					all_parameter_matrix[n][6] = Delta(param[n], 5, false);
					all_parameter_matrix[n][7] = Delta(param[n], 5, true);
					break;
				}
			}
			return all_parameter_matrix;
		}
		// Overloaded European Delta matrix that receive the parameter matrix as an input, and return the matrix of Delta (both put and call) as the output
		vector<vector<double>> EuropeanOption::European_Delta_Matrix(const vector<vector<double>>& param_matrix, const int& type) const // type will be specify by user
		{
			vector<vector<double>> OptionDelta_matrix(param_matrix.size()); // create an option Delta matrix corresponding to the input parameter matrix 
			for (int n = 0; n < param_matrix.size(); ++n)
			{
				switch (type) // depends on the type being tested, we switch the output matrix
				{
				case 0: // S
					OptionDelta_matrix[n].push_back(param_matrix[n][0]); // we utilize push_back here because the original matrix does not have any values
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][0], 0, false));
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][0], 0, true));
					break;
				case 1: // K
					OptionDelta_matrix[n].push_back(param_matrix[n][1]);
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][1], 1, false));
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][1], 1, true));
					break;
				case 2: // r
					OptionDelta_matrix[n].push_back(param_matrix[n][2]);
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][2], 2, false));
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][2], 2, true));
					break;
				case 3: // T
					OptionDelta_matrix[n].push_back(param_matrix[n][3]);
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][3], 3, false));
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][3], 3, true));
					break;
				case 4: // sig
					OptionDelta_matrix[n].push_back(param_matrix[n][4]);
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][4], 4, false));
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][4], 4, true));
					break;
				case 5: // b
					OptionDelta_matrix[n].push_back(param_matrix[n][5]);
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][5], 5, false));
					OptionDelta_matrix[n].push_back(Delta(param_matrix[n][5], 5, true));
					break;
				}
			}
			return OptionDelta_matrix;
		}


		// function that get option price with S as parameter
		double EuropeanOption::Delta_S(const double& S) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallDelta_S(S, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutDelta_S(S, this->option_vector()); // these are vectors called from base class
		}
		// overloaded vector function of Delta with the underlying asset price as the parameter

		vector<double> EuropeanOption::Delta_S(const vector<double>& S_vec) const
		{
			vector<double> Delta_vec1; // create a vector to store the Delta corresponding to each element in underlying asset price vector
			for (int i = 0; i < S_vec.size(); ++i) // store in the vector
			{
				Delta_vec1.push_back(Delta_S(S_vec[i])); // calculate the Delta for the given underlying asset
				// push it back into the Delta vector
			}
			return Delta_vec1;
		}

		// function that get option price with T as parameter
		double EuropeanOption::Delta_T(const double& T) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallDelta_T(T, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutDelta_T(T, this->option_vector()); // these are vectors called from base class
		}
		// function that get option price with K as parameter
		double EuropeanOption::Delta_K(const double& K) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallDelta_K(K, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutDelta_K(K, this->option_vector()); // these are vectors called from base class
		}
		// function that get option price with r as parameter
		double EuropeanOption::Delta_r(const double& r) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallDelta_r(r, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutDelta_r(r, this->option_vector()); // these are vectors called from base class
		}
		// function that get option price with S as parameter
		double EuropeanOption::Delta_sig(const double& sig) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallDelta_sig(sig, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutDelta_sig(sig, this->option_vector()); // these are vectors called from base class
		}
		// function that get option price with S as parameter
		double EuropeanOption::Delta_b(const double& b) const
		{
			if (IsCall()) // CALL Option
				return mySolution->CallDelta_b(b, this->option_vector()); // these are vectors called from base class
			else // PUT Option
				return mySolution->PutDelta_b(b, this->option_vector()); // these are vectors called from base class
		}


		// return the Gamma: the partial derivative of Greek (Gamma is also a derivative of Delta)
		// help to show how sensitive the value of derivatives is to changes in the value of underlying asset
		double EuropeanOption::GetGamma() const // Get the Gamma
		{
			return mySolution->Gamma(this->option_vector());
		}

		// This Matrix function receives the vector as an input, the vector changes each parameter at a time
			// and depend on the type of the input parameter(S,K,r,T...), print out each batch as a matrix
		vector<vector<double>> EuropeanOption::European_Gamma_Matrix(const vector<double>& param, const int& type) const
		{
			size_t row_size = param.size(); // this will be the number of rows of this matrix depend on the size of the input vector
			vector<vector<double>> all_parameter_matrix(row_size,European_vector()); // European vector will be used here
			for (int n = 0; n < param.size(); ++n)
			{
				switch (type)
				{
				case 0: // S
					all_parameter_matrix[n][0] = param[n]; // n is the row number, increases up to the size of the input vector
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = GetGamma_S(param[n]); // store one of the Gamma in the 7th column
					break;
				case 1: // K
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = param[n];
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = GetGamma_K(param[n]);
					break;
				case 2: //r
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = param[n];
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = GetGamma_r(param[n]);
					break;
				case 3: // T
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = param[n];
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = GetGamma_T(param[n]);
					break;
				case 4: //sig
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = param[n];
					all_parameter_matrix[n][5] = m_b;
					all_parameter_matrix[n][6] = GetGamma_sig(param[n]);
					break;
				case 5://b
					all_parameter_matrix[n][0] = m_S;
					all_parameter_matrix[n][1] = m_K;
					all_parameter_matrix[n][2] = m_r;
					all_parameter_matrix[n][3] = m_T;
					all_parameter_matrix[n][4] = m_sig;
					all_parameter_matrix[n][5] = param[n];
					all_parameter_matrix[n][6] = GetGamma_b(param[n]);
					break;
				}
			}
			return all_parameter_matrix;
		}
		// Overloaded European Gamma matrix that receive the parameter matrix as an input, and return the matrix of Gamma as the output
		vector<vector<double>> EuropeanOption::European_Gamma_Matrix(const vector<vector<double>>& param_matrix, const int& type) const // type will be specify by user
		{
			vector<vector<double>> OptionGamma_matrix(param_matrix.size()); // create an option Gamma matrix corresponding to the input parameter matrix 
			for (int n = 0; n < param_matrix.size(); ++n)
			{
				switch (type) // depends on the type being tested, we switch the output matrix
				{
				case 0: // S
					OptionGamma_matrix[n].push_back(param_matrix[n][0]); // we utilize push_back here because the original matrix does not have any values
					OptionGamma_matrix[n].push_back(GetGamma_S(param_matrix[n][0]));
					break;
				case 1: // K
					OptionGamma_matrix[n].push_back(param_matrix[n][1]);
					OptionGamma_matrix[n].push_back(GetGamma_K(param_matrix[n][1]));
					break;
				case 2: // r
					OptionGamma_matrix[n].push_back(param_matrix[n][2]);
					OptionGamma_matrix[n].push_back(GetGamma_r(param_matrix[n][2]));
					break;
				case 3: // T
					OptionGamma_matrix[n].push_back(param_matrix[n][3]);
					OptionGamma_matrix[n].push_back(GetGamma_T(param_matrix[n][3]));
					break;
				case 4: // sig
					OptionGamma_matrix[n].push_back(param_matrix[n][4]);
					OptionGamma_matrix[n].push_back(GetGamma_sig(param_matrix[n][4]));
					break;
				case 5: // b
					OptionGamma_matrix[n].push_back(param_matrix[n][5]);
					OptionGamma_matrix[n].push_back(GetGamma_b(param_matrix[n][5]));
					break;
				}
			}
			return OptionGamma_matrix;
		}
		// function that calculate Gamma with passing in the different parameter
		double EuropeanOption::GetGamma_S(const double& S) const
		{
			return mySolution->Gamma_S(S, this->option_vector()); // these are vectors called from base class
		}
		double EuropeanOption::GetGamma_K(const double& K) const
		{
			return mySolution->Gamma_K(K, this->option_vector()); // these are vectors called from base class
		}
		double EuropeanOption::GetGamma_T(const double& T) const
		{
			return mySolution->Gamma_T(T, this->option_vector()); // these are vectors called from base class
		}
		double EuropeanOption::GetGamma_r(const double& r) const
		{
			return mySolution->Gamma_r(r, this->option_vector()); // these are vectors called from base class
		}
		double EuropeanOption::GetGamma_sig(const double& sig) const
		{
			return mySolution->Gamma_sig(sig, this->option_vector()); // these are vectors called from base class
		}
		double EuropeanOption::GetGamma_b(const double& b) const
		{
			return mySolution->Gamma_b(b, this->option_vector()); // these are vectors called from base class
		}

		// return the Vega: the sensitivity of the option price to a change in volatility
		// vega is the same for both put and call option
		double EuropeanOption::GetVega() const // Get the Vega
		{
			return mySolution->Vega(this->option_vector());
		}
		
		// return the Theta: measures the sesitivity of the value of the derivative to the passage of time
		// "time decay"
		// Theta is always negative
		double EuropeanOption::GetTheta() const
		{
			return mySolution->Theta(this->option_vector());
		}

		// Return the Delta Approximate
		// In general, we can approximate first and second-order derivatives in S by 3-point second order approximates
		double EuropeanOption::DeltaApproximate(const double& x) const
		{
			// determine if it is a call or put option
			if (IsCall()) // CALL Option
				return CallDeltaApproximate(x); // this approximate calculation is the private member of European Class
			else // PUT Option
				return PutDeltaApproximate(x); // this approximate calculation is the private member of European Class
		}
		// Return the Gamma Approximate
		// In general, we can approximate first and second-order derivatives in S by 3-point second order approximates
		double EuropeanOption::GammaApproximate(const double& x) const
		{
			// determine if it is a call or put option
			if (IsCall()) // CALL Option
				return CallGammaApproximate(x);// this approximate calculation is the private member of European Class
			else // PUT Option
				return PutGammaApproximate(x); // this approximate calculation is the private member of European Class
		}

		//Put-call parity Satisfication
		double EuropeanOption::EuropeanPutCallParity(const EuropeanOption& otherOP) const   // This will use the call/put price to calculate the corresponding call/put price
		{
			return mySolution->PutCallParity(this->option_vector(), otherOP.Price(), this->type());
		}

		bool EuropeanOption::IsEuropeanPutCallParity(const EuropeanOption& otherOP, const double& error_boundary) const  // Check if a given set of put/call prices prices satisfy parity
		{
			double this_price = this->Price();  // Obtain price of the option that I calculate in the EuropeanOption class
			double op_price = EuropeanPutCallParity(otherOP);   // Obtain price of the other object
			return ((abs(this_price - op_price)) < error_boundary);  // Determine if parity is achieved, error_boundary is used to determine the margin accuracy, and this will be assigned by user
			// usually the error_boundary will be 0.01 to obtain a good accuracy
		}

		// Modifier functions
		void EuropeanOption::toggle()
		{ // Change option type (C/P, P/C)

			if (IsCall()) // CALL Option
				m_type = 0;
			else // PUT Option
				m_type = 1;
		}
	}
}