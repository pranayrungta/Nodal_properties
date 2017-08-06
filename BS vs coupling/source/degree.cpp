#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
	string datafile = "./../btc_RSFsample.txt";

    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9} ;
    const vector<int> perturbCountRange {1} ;

    constexpr int repetitions =2 ;

    constexpr double transients = 3;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}

#endif // PARAMETERS



#include "btc_clc_degree.cpp"

class Degree:public Processor
{public:

	Degree(const string filename):
		Processor(filename){};

	void calculteBS(const int pc, const double c)override
	{
		BSh.clear();
		BSl.clear();
		for(auto& dp : data)
		{
			vector<int> perturbNodes = analyser.highest_degree(dp.nbr,pc);
			BSh[dp.tag] += analyser.BS_one_config(c,dp,perturbNodes);
			perturbNodes= analyser.lowest_degree(dp.nbr,pc);
			BSl[dp.tag] += analyser.BS_one_config(c,dp,perturbNodes);
		}

		for(auto& i: BSh)
			i.second /= count_config[i.first];
		for(auto& i: BSl)
			i.second /= count_config[i.first];
	}
};




int main()
{using namespace parameter;

	Degree process(datafile);
	for(const int pc : perturbCountRange)
	{
		process.openfiles(pc);
		for(const double c:cRange)
			process.write_to_file(pc,c);
		process.closefiles();
	}
}
