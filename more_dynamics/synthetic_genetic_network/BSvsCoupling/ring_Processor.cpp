#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../../../Topology/common_base.cpp"
constexpr double positive_well = 1.42;
constexpr double negative_well = 0.19;
constexpr double mid_well = 0.77;
namespace parameter
{
	const string datafile = "btc_Ring_ic=50.txt";

    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,
                                 1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8} ;

    constexpr int perturbCount=2;
    constexpr int repetitions=100;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = mid_well;
    constexpr double perturbRange_final = mid_well + 2*(positive_well-mid_well);
}

#endif // PARAMETERS

#include "./../../../read_data/read_data.cpp"
#include "./../Dynamics.cpp"
#include<sstream>

struct BS_count
{
	double bshighest=0;
	double bslowest=0;
	int count=0;
};
using rsf_results = map<int,map<int,map<double,BS_count>>>;


void write_to_file(const rsf_results& results)
{using parameter::perturbCount;

	for(auto& nv:results)
    for(auto& kv :nv.second)
    {
        ostringstream ssh;
        ostringstream ssl;
        ssh<<"Ring_n="<<nv.first<<"_k="<<kv.first<<"_h_pc="<<perturbCount;
        ssl<<"Ring_n="<<nv.first<<"_k="<<kv.first<<"_l_pc="<<perturbCount;

        ofstream fh(ssh.str()+".txt");
        ofstream fl(ssl.str()+".txt");
        fh<<"#coupling"<<"\t"<<"BShighest"<<endl;
        fl<<"#coupling"<<"\t"<<"BSlowest"<<endl;

        for(auto& cv: kv.second)
        {
            fh<<cv.first<<"\t"<<cv.second.bshighest<<endl;
            fl<<cv.first<<"\t"<<cv.second.bslowest<<endl;
        }
    }
}


int main()
{using parameter::cRange;
using parameter::datafile;

	const vector<data_point> data = read_data_from_file(datafile);
	Dynamics analyser;

	///-------processing------
	rsf_results results;
    for(auto& dp:data)
	{
		auto& arg = dp.args;
		for(auto c : cRange)
		{
			BS_count& r=results[ arg.at("n") ][ arg.at("k") ][c];
			r.bshighest+=analyser.BShighest_one_config(c,dp);
			r.bslowest +=analyser.BSlowest_one_config(c,dp);
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
	write_to_file(results);
}
