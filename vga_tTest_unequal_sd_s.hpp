/* Albino Bacolla
   MDACC
   Molecular & Cellular Oncology
   6767 Bertner Avenue
   Houston TX 77033
   abacolla@mdanderson.org
   April 2019
   vga_tTest_unequal_sd_l.hpp -- get p-value from t-test
*/

#ifdef _MSC_VER
#  pragma warning(disable: 4512) // assignment operator could not be generated.
#  pragma warning(disable: 4510) // default constructor could not be generated.
#  pragma warning(disable: 4610) // can never be instantiated - user defined constructor required.
#endif

#pragma once

#include <boost/math/distributions/students_t.hpp>
#include <boost/math/distributions/fisher_f.hpp>

namespace vga {
	double two_samples_t_test_unequal_sd(double Sm1,   // Sm1 = Sample Mean 1.
	  double Sd1,   // Sd1 = Sample Standard Deviation 1.
	  size_t Sn1,   // Sn1 = Sample Size 1.
	  double Sm2,   // Sm2 = Sample Mean 2.
	  double Sd2,   // Sd2 = Sample Standard Deviation 2.
	  size_t Sn2,   // Sn2 = Sample Size 2.
	  double alpha)   // alpha = Significance Level.
	{
		using boost::math::students_t;
		// Degrees of freedom:
		double v = Sd1 * Sd1 / Sn1 + Sd2 * Sd2 / Sn2;
		v *= v;
		double t1 = Sd1 * Sd1 / Sn1;
		t1 *= t1;
		t1 /=  (Sn1 - 1);
		double t2 = Sd2 * Sd2 / Sn2;
		t2 *= t2;
		t2 /= (Sn2 - 1);
		v /= (t1 + t2);
		// t-statistic:
		double t_stat = (Sm1 - Sm2) / sqrt(Sd1 * Sd1 / Sn1 + Sd2 * Sd2 / Sn2);
		students_t dist(v);
		// p-value:
		double q = cdf(complement(dist, fabs(t_stat)));
		return 2 * q;
	}

    double p_valueR(double const& fValue, int const& totalN) {
      using namespace boost::math;
      double p{};
      fisher_f dist(1, totalN - 2);
      p = cdf(complement(dist, fValue));
      return p;
    }
}
