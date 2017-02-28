#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
	string datafile = "./../btc_Star.txt";

    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9} ;
    constexpr int perturbCount=1;

    constexpr int repetitions =2 ;

    constexpr double transients = 3;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}
//#include "source/Processor.cpp"
#endif // PARAMETERS

#include "./../../read_data/read_data.cpp"
#include "Dynamics.cpp"
#include<sstream>

struct BS_count
{
	double bshighest=0;
	double bslowest=0;
	int count=0;
};
using rsf_results = map<int,map<double,BS_count>>;


void write_to_file(const rsf_results& results)
{using parameter::perturbCount;

	for(auto& nv:results)
    {
        ostringstream ssh;
        ostringstream ssl;
        ssh<<"Star_n="<<nv.first<<"_h_pc="<<perturbCount;
        ssl<<"Star_n="<<nv.first<<"_l_pc="<<perturbCount;

        ofstream fh(ssh.str()+".txt");
        ofstream fl(ssl.str()+".txt");
        fh<<"#coupling"<<"\t"<<"BShighest"<<endl;
        fl<<"#coupling"<<"\t"<<"BSlowest"<<endl;

        for(auto& cv: nv.second)
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
    for(auto& dp : data)
	{
		auto& arg = dp.args;
		for(auto c : cRange)
		{
			BS_count& r=results[ arg.at("n") ][c];
			r.bshighest+=analyser.BShighest_one_config(c,dp);
			r.bslowest +=analyser.BSlowest_one_config(c,dp);
			r.count++;

			cout<<"\r n="<<arg.at("n")<<" c="<<c
			    <<" count="<<r.count<<"  "<<flush;
		}
	}
	///------dividing for avg--------
	for(auto& nv:results)
	for(auto& cv: nv.second)
	{
		cv.second.bshighest/=cv.second.count;
		cv.second.bslowest /=cv.second.count;
	}
	write_to_file(results);
}
