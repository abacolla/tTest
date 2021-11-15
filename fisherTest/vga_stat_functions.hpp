/* Albino Bacolla
   MDACC
   Molecular & Cellular Oncology
   6767 Bertner Avenue
   Houston TX 77033
   abacolla@mdanderson.org
   February 2019 - July 2019
   vga_statFunctions.hpp -- general stat functions
*/

#ifndef VGA_FUNCTIONS_L_HPP
#define VGA_FUNCTIONS_L_HPP

#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <cstdlib>

namespace vga {

// General stats

// compute mean

    template<typename InputIterator>
    double meanS(InputIterator first, InputIterator last) {
        double m{0};
        size_t adv{0};
        while (first != last) {
            m += *first;
            ++first;
            ++adv;
        }
        return (m / adv);
    }

// compute standard deviation

    template<typename InputIterator>
    double sdS(InputIterator first, InputIterator last) {
        double total{0};
        double sum2{0};
        size_t adv{0};
        while (first != last) {
            total += *first;
            sum2 += (*first) * (*first);
            ++first;
            ++adv;
        }
        return sqrt( (sum2 - (total*total/adv)) / (adv - 1) );
    }

///////////////////////////////////////////////////////////

// p-values from t-test

	template<typename T>
	class pValFromTtest {
		private:
		std::vector<T> inData;
		public:
		void read(std::string const&);
		size_t getSize() const;
		double getMean() const;
		double getSD() const;
	};

	template<typename T>
	void pValFromTtest<T>::read(std::string const& fileName) {
		if (!inData.empty()) { 
			inData.clear(); 
		}
		std::ifstream file1(fileName);
		if (file1.is_open()) {
			std::copy(std::istream_iterator<T>(file1), std::istream_iterator<T>(), back_inserter(inData));
		} else {
			std::cerr << "could not open " << fileName << '\n';
		}
		file1.close();
	}

	template<typename T>
	size_t pValFromTtest<T>::getSize() const {
		return inData.size();
	}

	template<typename T>
	double pValFromTtest<T>::getMean() const {
		return meanS(inData.begin(), inData.end());
	}

	template<typename T>
	double pValFromTtest<T>::getSD() const {
		return sdS(inData.begin(), inData.end());
	}

///////////////////////////////////////////////////////////

// factorial

    long double factorial(size_t const& i) {
        if (i > 1) {
            return i * factorial(i - 1);
        }
        else {
            return 1;
        }
    }

///////////////////////////////////////////////////////////

// log factorial

double logFac(int n) { 
    double ret;
    for(ret = 0.; n > 0; --n) {
        ret += log((double)n);
    }
    return ret;
}

///////////////////////////////////////////////////////////

long double logHypergeometricProb(long double* logFac, int a, int b, int c, int d) { 
    return logFac[a+b] + logFac[c+d] + logFac[a+c] + logFac[b+d]
    - logFac[a] - logFac[b] - logFac[c] - logFac[d] - logFac[a+b+c+d]; 
}

void initLogFac(long double* logFac, int n) {
   logFac[0] = 0;
   for (int i = 1; i < n+1; ++i) {
       logFac[i] = logFac[i-1] + log((double)i);
   }
}

///////////////////////////////////////////////////////////

// Fisher exact test

    class getFisher {
    private: 
    size_t A{}, B{}, C{}, D{};

    public:
    void getP(std::string const&) const;        
    };

    void getFisher::getP(std::string const& in1) const {
        std::ifstream file1(in1);
        if (file1.is_open()) {
            int a{}, b{}, c{}, d{}, n{}; 
            int set = 1;
            while (file1 >> a >> c >> b >> d) {
                n = a + b + c + d;
                long double* logFac = new long double[n+1];
                initLogFac(logFac, n);
                long double logPCutoff = logHypergeometricProb(logFac, a, b, c, d); // logFacs added
                long double pFraction = 0.;
                for (int x = 0; x <= n; ++x) {
                    if ( a+b-x >= 0 && a+c-x >= 0 && d-a+x >=0 ) {
                        long double l = logHypergeometricProb(logFac, x, a+b-x, a+c-x, d-a+x); 
                        if ( l <= logPCutoff ) {
                            pFraction += exp(l - logPCutoff);
                        }
                    } 
                }
                long double logPValue = logPCutoff + log(pFraction);

                std::cout << "Data for Set" << set << " with 2-sided p-values are\na\tc\tb\td\t-log10PValue\tPValue\n"
                          << a << '\t' 
                          << c << '\t' 
                          << b << '\t' 
                          << d << '\t' 
                          << -logPValue/log(10.) 
                          << '\t' << exp(logPValue) << '\n';
                delete [] logFac;
                ++set;
                a = b = c = d = n = 0;
            }
        }
        else {
            std::cerr << "Could not open file " << in1 << '\n';
        }
        file1.close();
    }
}

#endif // VGA_FUNCTIONS_L_HPP
