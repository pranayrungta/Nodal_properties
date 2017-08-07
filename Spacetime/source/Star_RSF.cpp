#ifndef PARAMETERS
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	string datafile = "btc_Star.txt";

    const vector<double> cRange {1} ;
    const vector<int> perturbCountRange{90};

    constexpr double transients = 10;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;

	int repetitions=-1;
}

#endif

#include "spacetime.cpp"
#include<sstream>


int main()
{using parameter::cRange;
using parameter::datafile;
using parameter::perturbCountRange;

	const vector<data_point> data = read_data_from_file(datafile);
	Dynamics analyser;


	///-------processing------
	for(const int pc: perturbCountRange)
	for(const double c : cRange)
    for(auto& dp:data)
	{
		auto seed=time(NULL);

		ostringstream ssh;
		ssh<<dp.tag<<"_c="<<c<<"_h_pc="<<pc;
		ofstream fh(ssh.str()+".spt");

		generator.seed(seed);
		vector<int> perturbNodes= analyser.samplehighest(dp.ndpr,pc);
		analyser.spt_one_config(fh,c,dp,perturbNodes);


		ostringstream ssl;
		ssl<<dp.tag<<"_c="<<c<<"_l_pc="<<pc;
		ofstream fl(ssl.str()+".spt");

		generator.seed(seed);
		perturbNodes= analyser.samplelowest(dp.ndpr,pc);
		analyser.spt_one_config(fl,c,dp,perturbNodes);

		cout<<"\r  "<<dp.tag<<" c="<<c<<"  "<<flush;
	}
}
