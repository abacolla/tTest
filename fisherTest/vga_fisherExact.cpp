/* Albino Bacolla
 MDACC
 Molecular & Cellular Oncology
 6767 Bertner Avenue
 Houston TX 77033
 abacolla@mdanderson.org
 July 2019

vga_fisherExact.cpp -- compute Fisher exact test
*/

#include <iostream>
#include "vga_stat_functions.hpp"

int main(int argc, char* argv[]) {

    using namespace vga;
    if (argc != 2) {
        std::cout << "\nSynopsis: compute Fisher exact test on 2x2 Contingency Table\n"
                  << "Usage: vga_fisher file1\n"
                  << "Note: file1 = 1-col (or data separated by space) file containing a c b d values repeated one or more times\n"
                  << "Example: vga_fisher data1.txt\n\n"
                  << "a c b d in Contingency Table are as follows:\n"
                  << "++++++++++++++++++++++++++++++++++\n"
                  << "+         treatment1  treatment2 +\n"
                  << "+ group1       a         b       +\n"
                  << "+ group2       c         d       +\n"
                  << "++++++++++++++++++++++++++++++++++\n\n";  

        return 1;
    }


    getFisher fish;
    fish.getP(argv[1]);

    return 0;
}
