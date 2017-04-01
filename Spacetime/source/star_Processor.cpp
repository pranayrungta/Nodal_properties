#ifndef PARAMETERS
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	string datafile = "btc_Star.txt";

    const vector<double> cRange {1} ;
    constexpr int perturbCount=90;

    constexpr double transients = 10;
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
    for(auto& dp : data)
	{
		auto& arg = dp.args;
		for(auto c : cRange)
		{
			ostringstream ssh;
			ostringstream ssl;
			ssh<<"Star_n="<<arg.at("n")<<"_c="<<c<<"_h_pc="<<perturbCount;
			ssl<<"Star_n="<<arg.at("n")<<"_c="<<c<<"_l_pc="<<perturbCount;

			ofstream fh(ssh.str()+".spt");
			ofstream fl(ssl.str()+".spt");

			auto seed=time(NULL);
			generator.seed(seed);
			analyser.spt_highest_one_config(fh,c,dp);

			generator.seed(seed);
			analyser.spt_lowest_one_config(fl,c,dp);

			cout<<"\r n="<<arg.at("n")<<" c="<<c<<"  "<<flush;
		}
	}
}
