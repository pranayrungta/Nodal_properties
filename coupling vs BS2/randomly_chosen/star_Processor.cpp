#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
	string datafile = "./../btc_Star.txt";

    const vector<double> cRange {1} ;
    constexpr int perturbCount=50;

    constexpr int repetitions =1 ;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}

#endif // PARAMETERS

#include "./../../read_data/read_data.cpp"
#include "Dynamics.cpp"
#include<sstream>

struct BS_count
{
	double bs=0;
	int count=0;
};
using star_results = map<int,map<double,BS_count>>;


void write_to_file(const star_results& results)
{using parameter::perturbCount;

	for(auto& nv:results)
    {
        ostringstream ssl;
        ssl<<"Star_n="<<nv.first<<"_pc="<<perturbCount;

        ofstream fl(ssl.str()+".txt");
        fl<<"#coupling"<<"\t"<<"BSlowest"<<endl;

        for(auto& cv: nv.second)
            fl<<cv.first<<"\t"<<cv.second.bs<<endl;
    }
}


int main()
{using parameter::cRange;
using parameter::datafile;

	const vector<data_point> data = read_data_from_file(datafile);
	Dynamics analyser;

	///-------processing------
	star_results results;
    for(auto& dp : data)
	{
		auto& arg = dp.args;
		for(auto c : cRange)
		{
			BS_count& r=results[ arg.at("n") ][c];
			r.bs +=analyser.BS_rand_nodes_perturb(c,dp);
			r.count++;

			cout<<"\r n="<<arg.at("n")<<" c="<<c
			    <<" count="<<r.count<<"  "<<flush;
		}
	}
	///------dividing for avg--------
	for(auto& nv:results)
	for(auto& cv: nv.second)
		cv.second.bs /=cv.second.count;

	write_to_file(results);
}
