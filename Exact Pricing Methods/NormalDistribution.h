#ifndef NORMALDISTRIBUTION_HPP
#define NORMALDISTRIBUTION_HPP

#include <boost/math/distributions/normal.hpp>  // Normal distribution header file
using namespace boost::math; // Don't forget to tell compiler which namespace

namespace Christine
{
	namespace Statistics
	{
		class NormalDistribution
		{
		private:
			double m_mean;  // Mean  
			double m_stdev;  // Standard deviation  
			boost::math::normal_distribution<>* m_normal; // Pointer to the boost library

		public:
			double Mean() const; // getter for the Mean
			double StandardDeviation() const; // getter for the standard deviation
			void Mean(const double& m1); // setter for the mean
			void StandardDeviation(const double& s1); // setter for the standard deviation

			// Constructors
			NormalDistribution();  // Default constructor
			NormalDistribution(const double& mean, const double& stdev);  // Override constructor passes into the initial mean/std deviation that boost library normal_distribution requires.  If omitted will default to (0,1)
			NormalDistribution(const NormalDistribution& copy);  // Copy constructor
			NormalDistribution& operator = (const NormalDistribution& source);  // Assignment operator
			virtual ~NormalDistribution();	// Destructor

			// the normal (Gaussian) probability density function
			// will return the pdf
			double Probability_Density(const double& x) const;

			// the normal (Gaussian) distribution function
			// will return the cdf
			double Cumulative_Distribution(const double& x) const;

		};
	}
}
#endif