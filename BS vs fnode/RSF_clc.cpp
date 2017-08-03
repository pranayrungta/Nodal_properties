#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
	string datafile = "./../../Betweeness centrality/data/clc_RSF_k=2_ic=100.txt";

    const vector<double> cRange {0.2,0.5,1.0,2.0} ;
    const vector<int> perturbCountRange[2, 4, 6, 8, 10, 12, 14, 16, 18, 20,
										22, 24, 26, 28, 30, 32, 34, 36, 38];

    constexpr int repetitions =100 ;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}

#endif // PARAMETERS

#include "./../read_data/read_data.cpp"
#include "Dynamics.cpp"
#include<sstream>

struct BS_count
{
	double clc_h=0;
	double clc_l=0;
	int count=0;
};
using rsf_results = map<int,map<int,map<int,BS_count>>>;


void write_to_file(const rsf_results& results,const double coupling)
{
	for(auto& n_kp:results)
    for(auto& k_pv:n_kp.second)
    {
        ostringstream ssh;
        ostringstream ssl;
        ssh<<"RSF_n="<<n_kp.first<<"_k="<<k_pv.first<<"_clch_c="<<coupling;
        ssl<<"RSF_n="<<n_kp.first<<"_k="<<k_pv.first<<"_clcl_c="<<coupling;

        ofstream fh(ssh.str()+".txt");
        ofstream fl(ssl.str()+".txt");
        fh<<"#pc"<<"\t"<<"BShighest"<<endl;
        fl<<"#pc"<<"\t"<<"BSlowest"<<endl;

        for(auto& pv: k_pv.second)
        {
            fh<<pv.first<<"\t"<<pv.second.clc_h<<endl;
            fl<<pv.first<<"\t"<<pv.second.clc_l<<endl;
        }
    }
}


int main()
{using parameter::cRange;
using parameter::datafile;
using parameter::perturbCountRange;

	const vector<data_point> data = read_data_from_file(datafile);
	Dynamics analyser;

	for(auto c : cRange)
	{
		///-------processing------
		rsf_results results;
		for(auto& dp:data)
		{
			auto& arg = dp.args;
			for(int perturbCount : perturbCountRange)
			{
				BS_count& r=results[ arg.at("n") ][ arg.at("k") ][perturbCount];

				vector<int> perturbNodes = analyser.samplehighest(dp.btc,perturbCount);
				r.clc_h+=analyser.BS_one_config(c,dp,perturbNodes);

				perturbNodes = analyser.samplelowest(dp.btc,perturbCount);
				r.clc_l +=analyser.BS_one_config(c,dp,perturbNodes);

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
			cv.second.clc_h/=cv.second.count;
			cv.second.clc_l/=cv.second.count;
		}
		write_to_file(results,c);
	}
}
