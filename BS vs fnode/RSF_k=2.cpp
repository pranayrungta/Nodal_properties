#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	const string datafile = "./../../Network Properties/data/btc_RSF_n=100_k=2_ic=100.txt";

    const vector<double> cRange { 0.2, 0.4, 0.6, 0.7, 0.8, 0.9, 1.1, 1.2, 1.3, 1.4 } ;
    const vector<int> perturbCountRange{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};

    constexpr int repetitions=100;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}

#endif // PARAMETERS

//#include "source/randomly.cpp"
#include "source/btc_clc.cpp"
//#include "source/degree.cpp"
