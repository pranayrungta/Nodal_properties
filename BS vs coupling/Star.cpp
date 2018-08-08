#ifndef PARAMETERS
#define PARAMETERS

#include "./../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	const string datafile = "./../../Network Properties/data/btc_Star_n=100.txt";

    const vector<double> cRange {0.25} ;
    const vector<int> perturbCountRange{1};

    constexpr int repetitions=1000;

    constexpr double transients = 50;
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
