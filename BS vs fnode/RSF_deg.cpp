#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
	string datafile = "./../../Betweeness centrality/data/clc_RSF_k=2_ic=100.txt";

    const vector<double> cRange {0.2,0.5,1.0,2.0} ;
    const vector<int> perturbCountRange{2, 4, 6, 8, 10, 12, 14, 16, 18, 20,
										22, 24, 26, 28, 30, 32, 34, 36, 38};

    constexpr int repetitions =100 ;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}
#endif // PARAMETERS




#include "common.cpp"

int main()
{using parameter::cRange;
using parameter::datafile;
using parameter::perturbCountRange;

	const vector<data_point> data = read_data_from_file(datafile);
	Dynamics_base analyser;

	for(auto c : cRange)
	{
		///-------processing------
		map<int,map<int,map<int,BS_count>>> results;
		for(auto& dp:data)
		{
			auto& arg = dp.args;
			for(int perturbCount : perturbCountRange)
			{
				BS_count& r=results[ arg.at("n") ][ arg.at("k") ][perturbCount];

				vector<int> perturbNodes = analyser.highest_degree(dp.nbr,perturbCount);
				r.BSh+=analyser.BS_one_config(c,dp,perturbNodes);

				perturbNodes = analyser.lowest_degree(dp.nbr,perturbCount);
				r.BSl +=analyser.BS_one_config(c,dp,perturbNodes);

				r.count++;

				cout<<"\r n="<<arg.at("n")<<" k="<< arg.at("k")
					<<" c="<<c<<" count="<<r.count<<"  "<<flush;
			}
		}
		///------dividing for avg--------
		for(auto& n_kp:results)
		for(auto& k_pv:n_kp.second)
		for(auto& fn_V: k_pv.second)
		{
			fn_V.second.BSh/=fn_V.second.count;
			fn_V.second.BSl/=fn_V.second.count;
		}
		///------writing to file----------
		for(auto& n_kp:results)
		for(auto& k_pv:n_kp.second)
		{
			ostringstream ssh;
			ostringstream ssl;
			ssh<<"RSF_n="<<n_kp.first<<"_k="<<k_pv.first<<"_degh_c="<<c;
			ssl<<"RSF_n="<<n_kp.first<<"_k="<<k_pv.first<<"_degl_c="<<c;
			write_fnodeVsBS(ssh.str(),ssl.str(),k_pv.second);
		}
	}
}
