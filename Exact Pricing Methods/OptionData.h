#ifndef OptionData_h
#define OptionData_h
#include <string>
#include <iostream>
using namespace std;

struct OptionData 
{
	double S;     // Asset Pirce
	double r;		// Interest rate
	double sig;		// Volatility
	double K;		// Strike price
	double T;		// Expiry date
	//double b;		// Cost of carry
	// I comment this out because I figure out there should be two logics deciding the value of b
	// 1. let the model figure out b
	// 2. let the user type in b by using the overloaded constructor
	double D;       // dividend
	int type;    // option type, 1 == call
	int model;   // determine the model; detailed description is given in AllOptions.h


	OptionData(double Asset, double Strike, double interest_rate, double Expiry_Date, double sig_1, double dividend, int option_type, int m_model)
		: S(Asset), K(Strike), r(interest_rate),T(Expiry_Date), sig(sig_1), D(dividend),type(option_type),model(m_model) {}
};
#endif