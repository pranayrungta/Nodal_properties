#ifndef PARAMETERS
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	string datafile = "dataSample.txt";

    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9} ;
    constexpr int perturbCount=1;

    constexpr int repetitions =2 ;

    constexpr double transients = 3;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}

#endif // PARAMETERS


#include "./../../read_data/read_data.cpp"
#include "RecoveryTime.cpp"
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
        fh<<"#coupling"<<"\t"<<"RThighest"<<endl;
        fl<<"#coupling"<<"\t"<<"RThighest"<<endl;

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
			r.bshighest+=analyser.recTime_highest_one_config(c,dp);
			r.bslowest +=analyser.recTime_lowest_one_config(c,dp);
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
