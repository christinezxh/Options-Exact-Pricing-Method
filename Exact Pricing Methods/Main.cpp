#include <vector>
#include "EuropeanOption.h"
#include "PerpetualAmericanOption.h"
#include "Utilities.h"

using namespace Christine::Calculations;
using namespace Christine::Options;
using namespace Christine::Statistics;
using namespace Christine::UtilityFunctions;


int main()
{
	// Now we will test all of our four batches
	// Here are the sequence of data plugging in:
	// Asset, Strike,interest rate, ExpiryDate, Volatility, dividend(0 for Black Scholes model)
	// Option type (1 Call, 0 Put), Model (1 for Black Scholes model))

	// before officially start the test for each braket, I would like to randomly check some set and get function
	/*EuropeanOption test_1;
	test_1.T(1.5);
	cout << test_1.T() << endl;
	test_1.ToString();
	cout << endl << endl;*/
	// All work, comment out after checking

	// give call and put a int value, will be used to call them
	int type_call = 1;
	int type_put = 0;
	cout << "**************************Part A Exact Solution********************************" << endl;

	cout << "This section we will test the put and call option price for 4 batches" << endl;
	cout << "The data members are: Asset price, Strike Price, Interest Rate, Exercise Date, Volatility, and Cost of Carry" << endl;

	cout << "-----------------------------Now we test BATCH 1-----------------------------" << endl;
	// The data of Batch1
	double S1 = 108.0;
	double K1 = 120.0;
	double r1 = 0.045;
	double T1 = 1.45;
	double sig1 = 0.51;
	double d1 = 0;
	int model1 = 4;
	OptionData myCall_option1(S1, K1, r1, T1, sig1,d1,type_call, model1); // create the batch for call option
	OptionData myPut_option1(S1, K1, r1, T1, sig1, d1, type_put, model1); // create the batch for put option

	EuropeanOption batchCall_option1 = EuropeanOption(myCall_option1,0); // make the EuropeanOption for Call by passing in the Option data value
	EuropeanOption batchPut_option1 = EuropeanOption(myPut_option1,0); // make the EuropeanOption for Call by passing in the Option data value

	cout << "Call Price: " << batchCall_option1.Price() << endl;
	cout << "Put Price: " << batchPut_option1.Price() << endl;
	cout << "-----------------------------Now we test BATCH 2-----------------------------" << endl;
	// The data of Batch2
	double S2 = 100.0;
	double K2 = 100.0;
	double r2 = 0.0;
	double T2 = 1.0;
	double sig2 = 0.20;
	double d2 = 0;
	int model2 = 1;
	OptionData myCall_option2(S2, K2, r2, T2, sig2, d2, type_call, model2); // create the batch for call option
	OptionData myPut_option2(S2, K2, r2, T2, sig2, d2, type_put, model2); // create the batch for put option

	EuropeanOption batchCall_option2 = EuropeanOption(myCall_option2); // make the EuropeanOption for Call by passing in the Option data value
	EuropeanOption batchPut_option2 = EuropeanOption(myPut_option2); // make the EuropeanOption for Call by passing in the Option data value

	cout << "Call Price: " << batchCall_option2.Price() << endl;
	cout << "Put Price: " << batchPut_option2.Price() << endl;

	cout << "-----------------------------Now we test BATCH 3-----------------------------" << endl;
	// The data of Batch3
	double S3 = 5.0;
	double K3 = 10.0;
	double r3 = 0.12;
	double T3 = 1.0;
	double sig3 = 0.50;
	double d3 = 0;
	int model3 = 1;

	OptionData myCall_option3(S3, K3, r3, T3, sig3, d3, type_call, model3); // create the batch for call option
	OptionData myPut_option3(S3, K3, r3, T3, sig3, d3, type_put, model3); // create the batch for put option

	EuropeanOption batchCall_option3 = EuropeanOption(myCall_option3); // make the EuropeanOption for Call by passing in the Option data value
	EuropeanOption batchPut_option3 = EuropeanOption(myPut_option3); // make the EuropeanOption for Call by passing in the Option data value

	cout << "Call Price: " << batchCall_option3.Price() << endl;
	cout << "Put Price: " << batchPut_option3.Price() << endl;

	cout << "-----------------------------Now we test BATCH 4-----------------------------" << endl;
	// The data of Batch4
	double S4 = 100.0;
	double K4 = 100.0;
	double r4 = 0.08;
	double T4 = 30.0;
	double sig4 = 0.30;
	double d4 = 0;
	int model4 = 1;
	OptionData myCall_option4(S4, K4, r4, T4, sig4, d4, type_call, model4); // create the batch for call option
	OptionData myPut_option4(S4, K4, r4, T4, sig4, d4, type_put, model4);  // create the batch for put option

	EuropeanOption batchCall_option4 = EuropeanOption(myCall_option4); // make the EuropeanOption for Call by passing in the Option data value
	EuropeanOption batchPut_option4 = EuropeanOption(myPut_option4); // make the EuropeanOption for Call by passing in the Option data value

	cout << "Call Price: " << batchCall_option4.Price() << endl;
	cout << "Put Price: " << batchPut_option4.Price() << endl;

	cout << "-----------------------------Now we come to test (b)-----------------------------" << endl;
	// Test if the above batches satisfy the Put-Call Parity
	// A mechanism to calculate the call/ put for a corresponding price, and check if parity satisfaction is met
	// Batch1
	cout << "***Test the Put-Call Parity for Batch 1***" << endl;
	// This will calculate the call price by input the put price
	cout << "Test the Put-Call Parity for Call Price: " << batchCall_option1.EuropeanPutCallParity(batchPut_option1) << endl;
	// This will calculate the put price by input the call price
	cout << "Test the Put-Call Parity for Put Price: " << batchPut_option1.EuropeanPutCallParity(batchCall_option1) << endl;
	cout << "Check if the prices satisfy parity: " << ((batchCall_option1.IsEuropeanPutCallParity(batchPut_option1, 0.01)) ? "Satisfied" : "NOT satisfied") << endl;
	// note that we 0.01 is to test the accuracy, usually < 0.01 is a good estimation
	cout << endl;

	//Batch2
	cout << "***Test the Put-Call Parity for Batch 2***" << endl;
	cout << "Test the Put-Call Parity for Call Price: " << batchCall_option2.EuropeanPutCallParity(batchPut_option2) << endl;
	cout << "Test the Put-Call Parity for Put Price: " << batchPut_option2.EuropeanPutCallParity(batchCall_option2) << endl;
	cout << "Check if the prices satisfy parity: " << ((batchCall_option2.IsEuropeanPutCallParity(batchPut_option2, 0.01)) ? "Satisfied" : "NOT satisfied") << endl;
	cout << endl;

	//Batch3
	cout << "***Test the Put-Call Parity for Batch 3***" << endl;
	cout << "Test the Put-Call Parity for Call Price: " << batchCall_option3.EuropeanPutCallParity(batchPut_option3) << endl;
	cout << "Test the Put-Call Parity for Put Price: " << batchPut_option3.EuropeanPutCallParity(batchCall_option3) << endl;
	cout << "Check if the prices satisfy parity: " << ((batchCall_option3.IsEuropeanPutCallParity(batchPut_option3, 0.01)) ? "Satisfied" : "NOT satisfied") << endl;
	cout << endl;

	//Batch4
	cout << "***Test the Put-Call Parity for Batch 4***" << endl;
	cout << "Test the Put-Call Parity for Call Price: " << batchCall_option4.EuropeanPutCallParity(batchPut_option4) << endl;
	cout << "Test the Put-Call Parity for Put Price: " << batchPut_option4.EuropeanPutCallParity(batchCall_option4) << endl;
	cout << "Check if the prices satisfy parity: " << ((batchCall_option4.IsEuropeanPutCallParity(batchPut_option4, 0.01)) ? "Satisfied" : "NOT satisfied") << endl;
	cout << endl;

	cout << "-----------------------------Now we come to test (c)-----------------------------" << endl;

	double start_S = batchCall_option1.S();  // set the start value as stock price of Batch 1 data
	double end_S = start_S * 2.0; // set the end value as 2.0 times of initial value
	int num_S = 8;               // set the number of underlying asset prices (S) we need to 15

	// create a vector of of monotonically increasing stock prices
	vector<double> B1_vec = meshArray(start_S, end_S, num_S);
	cout << "The Underlying Asset price are: " << endl;
	print(B1_vec); // use the global template function to print out the different S stored in the vector
	cout << endl;

	// Price_S will calculate the corresponding option price result 
	// now we create the vector to store the corresponding Call Option Price
	vector<double> C1_vec = batchCall_option1.Price_S(B1_vec);
	// now I would like to try to use toggle() to change the type instead of directly calling the Put option, just for fun
	batchCall_option1.toggle();

	//now we create the vector to store the corresponding Put Option Price
	vector<double> P1_vec = batchCall_option1.Price_S(B1_vec);

	cout << "The Call Option data are: " << endl;
	print(C1_vec);  // print the call price vector
	cout << endl;
	cout << "The Put Option data are: " << endl;
	print(P1_vec);  // print the call price vector

	batchCall_option1.toggle();// now we change it back to call option
	cout << endl;

	cout << "-----------------------------Now we come to test (d)-----------------------------" << endl;
	// this part we will test the matrix
	// the purpose here is to be able to input a matrix (vectors of vectors) of option parameters
	// and receive a matrix of option prices as the result
	int num_data = 5; // set the size of each paramater vector as 5

	// now we create the vectors of S (underlying asset price)
	vector<double> vec_S1 = meshArray(start_S, end_S, num_data); // we already set the start_S, end_S in part(c)

	// now we create the vectors of K (strike price)
	double start_K = batchCall_option1.K();
	double end_K = start_K * 2.0; // set the end value as 2.0 times of initial value
	vector<double> vec_K1 = meshArray(start_K, end_K, num_data);

	// now we create the vectors of r (interest rate)
	double start_r = batchCall_option1.r();
	double end_r = start_r * 2.0; // set the end value as 2.0 times of initial value
	vector<double> vec_r1 = meshArray(start_r, end_r, num_data);

	// now we create the vectors of T (expiry date)
	double start_T = batchCall_option1.T();
	double end_T = start_T * 2.0; // set the end value as 2.0 times of initial value
	vector<double> vec_T1 = meshArray(start_T, end_T, num_data);

	// now we create the vectors of sig (volatility)
	double start_sig = batchCall_option1.sig();
	double end_sig = start_sig * 2.0; // set the end value as 2.0 times of initial value
	vector<double> vec_sig1 = meshArray(start_sig, end_sig, num_data);

	// now we create the vectors of b (cost of carry)
	double start_b = batchCall_option1.b();
	double end_b = start_b * 2.0; // set the end value as 2.0 times of initial value
	vector<double> vec_b1 = meshArray(start_b, end_b, num_data);

	// now we test the matrix function by changing S
	// int type is follow: S:0, K:1, r:2, T:3, sig:4, b:5
	// choose the parameter that will be changed
	cout << "Print out the Matrix of Batch1 that changes S" << endl;
	cout << "S   K   r   T   sig   b   Call   Put" << endl;
	vector<vector<double>> Price_Matrix_S = batchCall_option1.Price_Matrix(vec_S1, 0);
	print(Price_Matrix_S);
	cout << endl << endl;
	cout << "Just print out the S and the result Call, Put Price" << endl;
	cout << "S  Call    Put" << endl;
	vector<vector<double>> Price_Matrix_S1 = batchCall_option1.Price_Matrix(Price_Matrix_S, 0);
	print(Price_Matrix_S1);
	cout << endl << endl;
	// now we test the matrix function by changing r
	cout << "Print out the Matrix of Batch1 that changes r" << endl;
	cout << "S   K   r   T   sig   b   Call   Put" << endl;
	vector<vector<double>> Price_Matrix_r = batchCall_option1.Price_Matrix(vec_r1, 2);
	print(Price_Matrix_r);
	cout << endl << endl;
	cout << "Just print out the r and the result Call, Put Price" << endl;
	cout << "r    Call    Put" << endl;
	vector<vector<double>> Price_Matrix_r1 = batchCall_option1.Price_Matrix(Price_Matrix_r, 2);
	print(Price_Matrix_r1);
	cout << endl << endl;
	cout << "************************Part A II Option Sensitivities******************************" << endl;
	cout << endl;
	cout << "-----------------------------(a)Now we test the given Batch-----------------------------" << endl;
	// Here are the sequence of data plugging in:
	// Asset, Strike,interest rate, ExpiryDate, Volatility, dividend(0 for Black Scholes model)
	// Option type (1 Call, 0 Put), Model (3 for Black Scholes future Option pricing))
	// Note that this is a future pricing model! so we use 3 for model
	// The data of Greek batch
	double S5 = 108.0;
	double K5 = 120.0;
	double r5 = 0.045;
	double T5 = 1.45;
	double sig5 = 0.51;
	double d5 = 0;
	int model5 = 4;

	OptionData myCall_option1_sensitivity(S5, K5, r5, T5, sig5, d5, type_call, model5); // create the batch for call option
	OptionData myPut_option1_sensitivity(S5, K5, r5, T5, sig5, d5, type_put, model5); // create the batch for put option

	EuropeanOption batchCall_sensitivity = EuropeanOption(myCall_option1_sensitivity,0); // make the EuropeanOption for Call by passing in the Option data value
	EuropeanOption batchPut_sensitivity = EuropeanOption(myPut_option1_sensitivity,0); // make the EuropeanOption for Call by passing in the Option data value

	cout << "Exact Delta Call: " << batchCall_sensitivity.Delta() << endl;
	cout << "Exact Delta Put: " << batchPut_sensitivity.Delta() << endl;
	cout << "Exact put price: " << batchPut_sensitivity.Price() << endl;

	// since gamma and vega are the same for both put and call option, we will just test the call
	cout << "Gamma: " << batchCall_sensitivity.GetGamma() << endl;
	cout << "Vega: " << batchCall_sensitivity.GetVega() << endl;
	cout << "Theta: " << batchCall_sensitivity.GetTheta() << endl;

	cout << "-----------------------------Now we come to test (b)-----------------------------" << endl;
	// we will use the batch from II (a)
	double start_DeltaS1 = batchCall_sensitivity.S(); // now we set the start value to be the value of the asset from the given batch
	double end_DeltaS1 = start_DeltaS1 * 1.5; 
	// set the end value to be 1.5 times the start, because in the previous section I set it to 2
	// and I do think 1.5 could be more appropriate
	int num_DeltaS1 = 15; // set the number of underlying stock prices (S) we need to 10

	// now we create the vector for a monotonically increasing range of underlying value of S
	vector<double> vec_Delta_testS1 = meshArray(start_DeltaS1, end_DeltaS1, num_DeltaS1);
	cout << "The Underlying Asset price are: " << endl;
	print(vec_Delta_testS1);
	cout << endl;

	// now we create the vector to store the corresponding Call Option delta
	vector<double> vec_Delta_Call1 = batchCall_sensitivity.Delta_S(vec_Delta_testS1);
	// now we create the vector to store the corresponding Put Option delta
	vector<double> vec_Delta_Put1 = batchPut_sensitivity.Delta_S(vec_Delta_testS1);

	cout << "The Call Option Delta are: " << endl;
	print(vec_Delta_Call1);  // print the call delta vector
	cout << endl;
	cout << "The Put Option Delta are: " << endl;
	print(vec_Delta_Put1);  // print the call delta vector

	cout << endl << endl;

	cout << "-----------------------------Now we come to test (c)-----------------------------" << endl;
	// First we test the matrix of Delta
	int num_Delta_test = 5; // set the size of each paramater vector as 5
	// now we create the vectors of S (underlying asset price)
	vector<double> vec_DeltaS1 = meshArray(start_DeltaS1, end_DeltaS1, num_Delta_test);

	// now we create the vectors of K (underlying asset price)
	double start_DeltaK1 = batchCall_sensitivity.K(); // now we set the start value from the given batch
	double end_DeltaK1 = start_DeltaK1 * 1.5; // set the end value to be 1.5 times the start
	vector<double> vec_DeltaK1 = meshArray(start_DeltaK1, end_DeltaK1, num_Delta_test); // create the vector of Strike price

	// now we create the vectors of r (underlying asset price)
	double start_Delta_r1 = batchCall_sensitivity.r(); // now we set the start value from the given batch
	double end_Delta_r1 = start_Delta_r1 * 1.5; // set the end value to be 1.5 times the start
	vector<double> vec_Delta_r1 = meshArray(start_Delta_r1, end_Delta_r1, num_Delta_test); // create the vector of interest rate

	// now we create the vectors of T (underlying asset price)
	double start_DeltaT1 = batchCall_sensitivity.T(); // now we set the start value from the given batch
	double end_DeltaT1 = start_DeltaT1 * 1.5; // set the end value to be 1.5 times the start
	vector<double> vec_DeltaT1 = meshArray(start_DeltaT1, end_DeltaT1, num_Delta_test); // create the vector of Expiry Date

	// now we create the vectors of sig (underlying asset price)
	double start_Delta_sig1 = batchCall_sensitivity.sig(); // now we set the start value from the given batch
	double end_Delta_sig1 = start_Delta_sig1 * 1.5; // set the end value to be 1.5 times the start
	vector<double> vec_Delta_sig1 = meshArray(start_Delta_sig1, end_Delta_sig1, num_Delta_test); // create the vector of volatility

	// now we create the vectors of b (underlying asset price)
	double start_Delta_b1= batchCall_sensitivity.b(); // now we set the start value from the given batch
	double end_Delta_b1 = 0.2; // set the end value to be 1.5 times the start
	vector<double> vec_Delta_b1 = meshArray(start_Delta_b1, end_Delta_b1, num_Delta_test); // create the vector of volatility

	// now we test the matrix function of Delta by changing T
	// int type is follow: S:0, K:1, r:2, T:3, sig:4, b:5
	cout << "Print out the Matrix of given batch that changes T" << endl;
	cout << "S   K   r   T   sig   b   Call   Put" << endl;
	vector<vector<double>> Delta_Matrix_T = batchCall_sensitivity.European_Delta_Matrix(vec_DeltaT1, 3);
	print(Delta_Matrix_T);
	cout << endl << endl;
	cout << "Just print out the T and the result Call, Put Delta" << endl;
	cout << "T   Call_D   Put_D" << endl;
	vector<vector<double>> Delta_Matrix_T1 = batchCall_sensitivity.European_Delta_Matrix(Delta_Matrix_T, 3);
	print(Delta_Matrix_T1);
	cout << endl << endl;
	// now we test the matrix function by changing sig
	cout << "Print out the Matrix of given batch that changes sig" << endl;
	cout << "S   K   r   T   sig   b   Call   Put" << endl;
	vector<vector<double>> Delta_Matrix_sig = batchCall_sensitivity.European_Delta_Matrix(vec_Delta_sig1, 4);
	print(Delta_Matrix_sig);
	cout << endl << endl;
	cout << "Just print out the sig and the result Call, Put Delta" << endl;
	cout << "sig   Call_D   Put_D" << endl;
	vector<vector<double>> Delta_Matrix_sig1 = batchCall_sensitivity.European_Delta_Matrix(Delta_Matrix_sig, 4);
	print(Delta_Matrix_sig1);
	cout << endl << endl;

	// now we test the matrix function of Gamma by changing S
	// int type is follow: S:0, K:1, r:2, T:3, sig:4, b:5
	vector<vector<double>> Gamma_Matrix_S = batchCall_sensitivity.European_Gamma_Matrix(vec_DeltaS1, 0);

	cout << "Just print out the S and the result Gamma" << endl;
	cout << "S  Gamma" << endl;
	vector<vector<double>> Gamma_Matrix_S1 = batchCall_sensitivity.European_Gamma_Matrix(Gamma_Matrix_S, 0);
	print(Gamma_Matrix_S1);

	cout << endl << endl;


	cout << "-----------------------------Now we come to test (d)-----------------------------" << endl;
	// now let's check out the approximate option sensitivities
	double h; // the parameter h will be input into the approximate function to see the accuracy

	// in order to see how the result of this approximation could be really closed to our exact solution
	// I will use a for loop to get relatively small h
	// Here, we are still using the given batch for Sensitivity batch
	// the batch is: S = 105, K = 100, r = 0.1, T = 0.5, sig = 0.36, b = 0;

	// let's store the delta and gamma in a variable for simplicity
	double call_delta_1 = batchCall_sensitivity.Delta();
	double put_delta_1 = batchPut_sensitivity.Delta();
	double gamma_1 = batchCall_sensitivity.GetGamma();

	// First of all, we test the Delta for Call Option
	// I would print out both the absolute error and the relative error
	// absolute error doesn't account for order of magnitude
	cout.precision(20); // make sure we can print out the needed places after decimal

	cout << "***Call Delta Approximation***" << endl;
	for (int i = 0; i < 6; ++i)
	{
		h = pow(100, -i); // this will give us an h really close to 0, so relatively larger accuracy!
		// here we first print out the h with approximate Call Delta
		cout << "h = " << h << ", Approximate Call Delta = " << batchCall_sensitivity.DeltaApproximate(h) << endl;
		// print out the exact Call Delta of the given batch
		cout << "The Exact Call Delta is: " << call_delta_1 << endl;
		// print out the difference between the exact delta and the approximation
		cout << "The Absolute Error is: " << abs(batchCall_sensitivity.DeltaApproximate(h) - call_delta_1) << "  The Relative Error is: " << 100 * abs(batchCall_sensitivity.DeltaApproximate(h) - call_delta_1) / call_delta_1 << " %" << endl;
		cout << endl;
	}
	cout << endl << endl;
	cout << "***Put Delta Approximation***" << endl;
	// Then, we test the Delta for Put Option
	for (int i = 0; i < 6; ++i)
	{
		h = pow(100, -i); // this will give us an h really close to 0, so relatively larger accuracy!
		// here we first print out the h with approximate Call Delta
		cout << "h = " << h << ", Approximate Put Delta = " << batchPut_sensitivity.DeltaApproximate(h) << endl;
		// print out the exact Put Delta of the given batch
		cout << "The Exact Put Delta is: " << put_delta_1 << endl;
		// print out the difference between the exact delta and the approximation
		cout << "The Absolute Error is: " << abs(batchPut_sensitivity.DeltaApproximate(h) - put_delta_1) << "  The Relative Error is: " << 100 * abs(batchPut_sensitivity.DeltaApproximate(h) - put_delta_1) / - put_delta_1 << " %" << endl;
		cout << endl;
	}
	cout << endl << endl;
	cout << "***Call Gamma Approximation***" << endl;
	// Finally, we test the Call Gamma
	for (int i = 0; i < 6; ++i)
	{
		h = pow(100, -i); // this will give us an h really close to 0, so relatively larger accuracy!
		// here we first print out the h with approximate Call Delta
		cout << "h = " << h << ", Approximate Call Gamma = " << batchCall_sensitivity.GammaApproximate(h) << endl;
		// print out the exact Gamma of the given batch
		cout << "The Exact Gamma is: " << gamma_1 << endl;
		// print out the difference between the exact delta and the approximation
		cout << "The Absolute Error is: " << abs(batchCall_sensitivity.GammaApproximate(h) - gamma_1) << "  The Relative Error is: " << 100 * abs(batchCall_sensitivity.GammaApproximate(h) - gamma_1) / gamma_1 << " %" << endl;
		cout << endl;
	}
	cout << endl;

	cout << "**********************Part B Perpetual American Options****************************" << endl;
	// Now we start to test the Perpetual American Options
	// Here are the sequence of data plugging in:
	// Asset, Strike,interest rate, ExpiryDate, Volatility, dividend(0 for Black Scholes model)
	// Option type (1 Call, 0 Put), Model
	// Our test data is: S = 110, K = 100, r = 0.1, T = 0, sig = 0.1, b = 0.02;
	cout << "-----------------------------Now we come to test (b)-----------------------------" << endl;
	cout.precision(6); // we don't need that many places after decimal, so change back
	// The data of Perpetual American Options, b will be specified using the overloaded constructor
	double S6 = 110.0;
	double K6 = 100.0;
	double r6 = 0.1;
	double T6 = 0.0;
	double sig6 = 0.1;
	double d6 = 0;
	int model6 = 4;
	OptionData myCall_AmericanOption1(S6, K6, r6, T6, sig6, d6, type_call, model6); // create the batch for call option
	OptionData myPut_AmericanOption1(S6, K6, r6, T6, sig6, d6, type_put, model6); // create the batch for put option

	// This is not a Black Scholes Model, so we let the user type in cost of carry directly by using overloaded constructor
	PerpetualAmericanOption Perpetual_Call_1 = PerpetualAmericanOption(myCall_AmericanOption1,0.02); // b= 0.02
	PerpetualAmericanOption Perpetual_Put_1 = PerpetualAmericanOption(myPut_AmericanOption1,0.02);

	cout << "The Call Price of this American Option is: " << Perpetual_Call_1.Price() << endl;
	cout << "The Put Price of this American Option is: " << Perpetual_Put_1.Price() << endl;
	cout << endl;

	cout << "-----------------------------Now we come to test (c)-----------------------------" << endl;

	double American_start_S = Perpetual_Call_1.S();  // set the start value as stock price of Batch 1 data
	double American_end_S = American_start_S * 2.0; // set the end value as 2.0 times of initial value
	int American_num_S = 8;               // set the number of underlying stock prices (S) we need to 15

	// create a vector of of monotonically increasing stock prices
	vector<double> American_S_vec = meshArray(American_start_S, American_end_S, American_num_S);
	cout << "The American Underlying Asset price are: " << endl;
	print(American_S_vec); // print the underlying asset vector 
	cout << endl << endl;

	// now we create the vector to store the corresponding Call Option Price
	vector<double> American_C1_vec = Perpetual_Call_1.Price_S(American_S_vec);
	// now we create the vector to store the corresponding Put Option Price
	vector<double> American_P1_vec = Perpetual_Put_1.Price_S(American_S_vec);

	cout << "The American Call Option data are: " << endl;
	print(American_C1_vec);  // print the call price vector
	cout << endl << endl;
	cout << "The American Put Option data are: " << endl;
	print(American_P1_vec);  // print the call price vector
	cout << endl;

	cout << "-----------------------------Now we come to test (d)-----------------------------" << endl;
	// this part we will test the matrix
	// the purpose here is to be able to input a matrix (vectors of vectors) of option parameters
	// and receive a matrix of option prices as the result
	int num_American_test = 5; // set the size of each paramater vector as 5

	// now we create the vectors of S (underlying asset price)
	vector<double> American_S1_vec = meshArray(American_start_S, American_end_S, num_American_test); // we already set the start, end in part(c)

	// now we create the vectors of K (strike price)
	double American_start_K = Perpetual_Call_1.K();
	double American_end_K = start_K * 1.5; // set the end value as 1.5 times of initial value
	vector<double> American_K_vec = meshArray(American_start_K, American_end_K, num_American_test);

	// now we create the vectors of r (interest rate)
	double American_start_r = Perpetual_Call_1.r();
	double American_end_r = American_start_r * 1.5; // set the end value as 1.5 times of initial value
	vector<double> American_r_vec = meshArray(American_start_r, American_end_r, num_American_test);

	// now we create the vectors of sig (volatility)
	double American_start_sig = Perpetual_Call_1.sig();
	double American_end_sig = American_start_sig * 1.5; // set the end value as 1.5 times of initial value
	vector<double> American_sig_vec = meshArray(American_start_sig, American_end_sig, num_American_test);

	// now we create the vectors of b (cost of carry)
	double American_start_b = Perpetual_Call_1.b();
	double American_end_b = American_start_b * 1.5; // set the end value as 1.5 times of initial value
	vector<double> American_b_vec = meshArray(American_start_b, American_end_b, num_American_test);

	// now we test the matrix function by changing S
	// int type is follow: S:0, K:1, r:2, sig:3, b:4
	cout << "Print out the Matrix of American Option Batch that changes S" << endl;
	cout << "S   K   r   sig   b   Call   Put" << endl;
	vector<vector<double>> APrice_Matrix_S = Perpetual_Call_1.Price_Matrix(American_S1_vec, 0);
	print(APrice_Matrix_S);
	cout << endl << endl;
	cout << "Just print out the S and the result Call, Put Price" << endl;
	cout << "S  Call    Put" << endl;
	vector<vector<double>> APrice_Matrix_S1 = Perpetual_Call_1.Price_Matrix(APrice_Matrix_S, 0);
	print(APrice_Matrix_S1);
	cout << endl << endl;

	// now we test the matrix function by changing b
	cout << "Print out the Matrix of American Option Batch that changes b" << endl;
	cout << "S   K   r   sig   b   Call   Put" << endl;
	vector<vector<double>> APrice_Matrix_b = Perpetual_Call_1.Price_Matrix(American_b_vec, 4);
	print(APrice_Matrix_b);
	cout << endl << endl;
	cout << "Just print out the b and the result Call, Put Price" << endl;
	cout << "b    Call    Put" << endl;
	vector<vector<double>> APrice_Matrix_b1 = Perpetual_Call_1.Price_Matrix(APrice_Matrix_b, 4);
	print(APrice_Matrix_b1);
	cout << endl << endl;

	cout << endl << endl;


	return 0;
}