#include "NormalDistribution.h"
#include <boost/math/distributions/normal.hpp> 
using namespace boost::math;

namespace Christine
{
	namespace Statistics
	{
		void NormalDistribution::Mean(const double& m1) // setter for the mean
		{
			m_mean = m1;
		}
		void NormalDistribution::StandardDeviation(const double& s1) // setter for the standard deviation
		{
			m_stdev = s1;
		}

		double NormalDistribution::Mean() const { return m_mean; } // getter for the Mean
		double NormalDistribution::StandardDeviation() const { return m_stdev; } // getter for the standard deviation

		// Constructors, destructor, and assignment Operator
		NormalDistribution::NormalDistribution(): m_mean(0.0),m_stdev(0.0), m_normal(new normal_distribution<>()){} // Default constructor
		NormalDistribution::NormalDistribution(const NormalDistribution& copy):m_mean(copy.m_mean), m_stdev(copy.m_stdev) // Copy constructor
		{
			m_normal = new normal_distribution<>(this->m_mean, this->m_stdev);  //this will point to normal_distribution boost library
			*m_normal = *copy.m_normal; // copy the poitner
		} 
		NormalDistribution::NormalDistribution(const double& mean, const double& stdev): m_mean(mean), m_stdev(stdev), m_normal(new normal_distribution<>(mean, stdev)){} // parameterised constructor
		NormalDistribution::~NormalDistribution() { delete m_normal; } 	// Destructor, delete the pointer to save space (this is on the heap)
		NormalDistribution& NormalDistribution::operator = (const NormalDistribution& source)  // Assignment operator
		{
			// preclude self-assignment
			if (this == &source) return *this;

			m_mean = source.m_mean;
			m_stdev = source.m_stdev;
			m_normal = new normal_distribution<>(this->m_mean, this->m_stdev);  //Create new pointer to normal_distribution boost library
			*m_normal = *source.m_normal;  // Assign existing pointer to new pointer of normal_distribution boost library
		}

		// the normal (Gaussian) probability density function
		// will return the pdf
		double NormalDistribution::Probability_Density(const double& x) const
		{
			return pdf(*m_normal, x);
		}

		// the normal (Gaussian) distribution function
		// will return the cdf
		double NormalDistribution::Cumulative_Distribution(const double& x) const
		{
			return cdf(*m_normal, x);
		}
	}
}