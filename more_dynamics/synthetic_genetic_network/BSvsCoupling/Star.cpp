#ifndef PARAMETERS
#define PARAMETERS

#include "./../../../Topology/common_base.cpp"
constexpr double positive_well = 1.42;
constexpr double negative_well = 0.19;
constexpr double mid_well = 0.77;
namespace parameter
{
	const string datafile = "btc_Star.txt";

    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,
                                 1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8} ;

    constexpr int perturbCount=2;
    constexpr int repetitions=100;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = mid_well;
    constexpr double perturbRange_final = mid_well + 2*(positive_well-mid_well);
}

#endif // PARAMETERS

#include "star_Processor.cpp"
