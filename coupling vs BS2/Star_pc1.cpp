#include "./../Topology/common_base.cpp"

#ifndef PARAMETERS
#define PARAMETERS
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	const string datafile = "./../Betweeness centrality/data/btc_Star.txt";

    const vector<double> cRange {0.2 , 0.221052631579 , 0.242105263158 , 0.263157894737 , 0.284210526316 , 0.305263157895 , 0.326315789474 , 0.347368421053 , 0.368421052632 , 0.389473684211 , 0.410526315789 , 0.431578947368 , 0.452631578947 , 0.473684210526 , 0.494736842105 , 0.515789473684 , 0.536842105263 , 0.557894736842 , 0.578947368421 , 0.6 } ;

    constexpr int perturbCount=1;
    constexpr int repetitions=100;

    constexpr double transients = 50;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}
#endif // PARAMETERS

//#include "randomly_chosen/star_Processor.cpp"
#include "btc_source/star_Processor.cpp"
