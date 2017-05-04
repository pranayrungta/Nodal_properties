#ifndef PARAMETERS
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	string datafile = "dataSample.txt";

    const vector<double> cRange {0.8,0.9} ;
    constexpr int perturbCount=1;

    constexpr double transients = 3;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}

#endif

#include "spacetime.cpp"
#include<sstream>

int main()
{using parameter::cRange;
using parameter::datafile;
using parameter::perturbCount;

	const vector<data_point> data = read_data_from_file(datafile);
	Dynamics analyser;

	///-------processing------
    for(auto& dp:data)
	{
		auto& arg = dp.args;
		for(auto c : cRange)
		{
			ostringstream ss;
			ss<<"Ring_n="<<arg.at("n")<<"_k="<<arg.at("k")<<"_c="<<c<<"_pc="<<perturbCount;

			ofstream f(ss.str()+".spt");
			analyser.spt_lowest_one_config(f,c,dp);

			cout<<"\r n="<<arg.at("n")<<" k="<< arg.at("k")
			    <<" c="<<c<<"  "<<flush;
		}
	}
}
