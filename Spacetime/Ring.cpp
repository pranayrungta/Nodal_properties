#ifndef PARAMETERS
#define PARAMETERS

#include "./../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	string datafile = "./../Betweeness centrality/data/btc_Ring.txt";

    const vector<double> cRange {1.0} ;
    constexpr int perturbCount=4;//4

    constexpr double transients = 50;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}

#endif
#include "source/ring_Processor.cpp"
