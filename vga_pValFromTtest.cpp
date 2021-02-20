/* Albino Bacolla
  MDACC
  Molecular & Cellular Oncology
  6767 Bertner Avenue
  Houston TX 77033
  abacolla@mdanderson.org
  May 6, 2020
  vga_pValFromTtestcpp -- return mean, sd, p-value from 2 files containing values
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include "vga_stat_functions.hpp"
#include "vga_tTest_unequal_sd_s.hpp"

using namespace vga;

int main(int argc, char* argv[]) {
	// Step 1 - Usage
	if (argc != 3 ||
		!strcmp(argv[1], "-h") != 0 ||
		!strcmp(argv[1], "--help") != 0) {
		std::cout << "\nReturn mean, sd and p-value from t-test comparison" << '\n';
		std::cout << "Usage: vga_tTest <file1> <file2>" << '\n';
		std::cout << "<file1> and <file2> contain single-column data without headings\n" << '\n';
		return 0;
	}

	// Step 2 - Get mean and SD
	pValFromTtest<double> set1;
	set1.read(argv[1]);
	size_t n1 = set1.getSize();
	double mean1 = set1.getMean();
	double sd1 = set1.getSD();

	pValFromTtest<double> set2;
	set2.read(argv[2]);
	size_t n2 = set2.getSize();
	double mean2 = set2.getMean();
	double sd2 = set2.getSD();

	// Step 2 - compute p-value and print
	double pVal = two_samples_t_test_unequal_sd(mean1, sd1, n1, mean2, sd2, n2, 0.05);

	std::cout << "File\tN\tmean\tSD\tp-value\n"; 
	std::cout << argv[1] << '\t' << n1 << '\t' << mean1 << '\t' << sd1 << '\n';
	std::cout << argv[2] << '\t' << n2 << '\t' << mean2 << '\t' << sd2 << '\t' 
			  << std::setprecision(3) << std::scientific << pVal << '\n';
}
