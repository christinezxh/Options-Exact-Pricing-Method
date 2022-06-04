// This utilityFunctions namespace contain all the useful function that would be used when testing in the main
#ifndef Utilities_HPP
#define Utilities_HPP

#include <vector>
#include <iostream>

namespace Christine
{
	namespace UtilityFunctions {

		//A global function that produces a mesh array of any data type separated by a mesh size h.
		template<typename T>
		vector<T> meshArray(T start, T end, int j) {
			vector<T> array(j); // this is a vector with size of j
			array[0] = start; // assigning the start value
			array[array.size() - 1] = end; // assigning the end value
			double h = (end - start) / (double(j) - 1.0);  // h is the mesh size
			for (int i = 1; i < array.size() - 1; ++i) {
				array[i] = array[i - 1] + h; // calculate the current value by using the previous one
			}
			return array;
		}
		// a template function to print out the vector
		template <typename T>
		void print(const vector<T>& vec)
		{
			cout << endl;
			for (std::size_t i = 0; i < vec.size(); ++i)
			{
				cout << vec[i] << " ";
			}
			cout << endl;
		}

		// overload function that prints a matrix
		template <typename T>
		void print(const vector<vector<T>>& matrix)
		{
			for (int i = 0; i < matrix.size(); ++i)
			{
				print(matrix[i]); // print row i of matrix as a vector in each loop
			}
		}

	}
}
#endif
