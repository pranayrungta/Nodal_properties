#include "./../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	string datafile = "btc_RSF_k=2.txt";

    const vector<double> cRange {1} ;
    constexpr int perturbCount=15;

    constexpr double transients = 20;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}
#include "source/RSF_Processor.cpp"
