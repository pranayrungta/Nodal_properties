#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
	string datafile = "./../../Betweeness centrality/data/clc_RSF_k=2_ic=100.txt";

    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,
                                 1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8} ;
    const vector<int> perturbCountRange {1,5,20,10,40} ;

    constexpr int repetitions =100 ;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}

#endif // PARAMETERS


#include "./../common.cpp"

int main()
{using parameter::cRange;
using parameter::datafile;
using parameter::perturbCountRange;

	const vector<data_point> data = read_data_from_file(datafile);
	Dynamics_base analyser;

	for(int perturbCount : perturbCountRange)
	{
		///-------processing------
		map<int,map<int,map<double,BS_count>>> results;
		for(auto& dp:data)
		{
			auto& arg = dp.args;
			for(auto c : cRange)
			{
				BS_count& r=results[ arg.at("n") ][ arg.at("k") ][c];

				vector<int> perturbNodes = analyser.samplehighest(dp.btc,perturbCount);
				r.bshighest+=analyser.BS_one_config(c,dp,perturbNodes);
				perturbNodes = analyser.samplelowest(dp.btc,perturbCount);
				r.bslowest += analyser.BS_one_config(c,dp,perturbNodes);
				r.count++;

				cout<<"\r n="<<arg.at("n")<<" k="<< arg.at("k")
					<<" c="<<c<<" count="<<r.count<<"  "<<flush;
			}
		}
		///------dividing for avg--------
		for(auto& nv:results)
		for(auto& kv :nv.second)
		for(auto& cv: kv.second)
		{
			cv.second.bshighest/=cv.second.count;
			cv.second.bslowest/=cv.second.count;
		}
		///-------writing to file--------
		for(auto& nv:results)
		for(auto& kv :nv.second)
		{
			ostringstream ssh;
			ostringstream ssl;
			ssh<<"RSF_n="<<nv.first<<"_k="<<kv.first<<"_h_pc="<<perturbCount<<".txt";
			ssl<<"RSF_n="<<nv.first<<"_k="<<kv.first<<"_l_pc="<<perturbCount<<".txt";
			write_CvsBS(ssh.str(), ssl.str(), kv.second);
		}
	}
}