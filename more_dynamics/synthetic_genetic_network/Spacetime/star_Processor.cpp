#ifndef PARAMETERS
#define PARAMETERS

#include "./../../../Topology/common_base.cpp"
constexpr double positive_well = 1.42;
constexpr double negative_well = 0.19;
constexpr double mid_well = 0.77;
namespace parameter
{

	string datafile = "./../../../Betweeness centrality/data/btc_Star.txt";

    const vector<double> cRange {0.9,1.0,1.1} ;

    constexpr int perturbCount = 1;
    constexpr int repetitions=-1;// not required here

    constexpr double transients = 20;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = mid_well;
    constexpr double perturbRange_final = mid_well + 2*(positive_well-mid_well);
}

#endif // PARAMETERS

#include "./../../../read_data/read_data.cpp"
#include "spacetime.cpp"
#include<sstream>


int main()
{using parameter::cRange;
using parameter::datafile;
using parameter::perturbCount;

	const vector<data_point> data = read_data_from_file(datafile);
	Spacetime analyser;

	///-------processing------
    for(auto& dp : data)
	{
		auto& arg = dp.args;
		for(auto c : cRange)
		{
			auto seed=time(NULL);

			ostringstream ssh;
			ssh<<"Star_n="<<arg.at("n")<<"_c="<<c<<"_h_pc="<<perturbCount;
			ofstream fh(ssh.str()+".spt");
			generator.seed(seed);
			analyser.spt_highest_one_config(fh,c,dp);

//			ostringstream ssl;
//			ssl<<"Star_n="<<arg.at("n")<<"_c="<<c<<"_l_pc="<<perturbCount;
//			ofstream fl(ssl.str()+".spt");
//			generator.seed(seed);
//			analyser.spt_lowest_one_config(fl,c,dp);

			cout<<"n="<<arg.at("n")<<" c="<<c<<"  "<<endl;
		}
	}
}
