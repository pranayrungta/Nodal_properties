//#include "./../../Topology/common_base.cpp"
//constexpr int positive_well = 1;
//constexpr int negative_well = -1;
//namespace parameter
//{
//	string datafile = "dataSample.txt";
//
//    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9} ;
//    constexpr int perturbCount=1;
//
//    constexpr double transients = 3;
//    constexpr double dt = 0.01;
//
//    constexpr int initial_well= negative_well ;
//    constexpr double spread= 0.25 ;
//    constexpr double perturbRange_initial = 0;
//    constexpr double perturbRange_final = 5;
//}
//#include "source/Processor.cpp"


#include "./../../read_data/read_data.cpp"
#include "./../../Dynamics_base.cpp"
#include "spacetime.cpp"
#include<sstream>

int main()
{using parameter::cRange;
using parameter::datafile;
using parameter::perturbCount;

	const vector<data_point> data = read_data_from_file(datafile);
	Dynamics analyser;

	///-------processing------
    for(auto& dp:data)
	{
		auto& arg = dp.args;
		for(auto c : cRange)
		{
			ostringstream ssh;
			ostringstream ssl;
			ssh<<"Ring_n="<<arg.at("n")<<"_k="<<arg.at("k")<<"_h_pc="<<perturbCount;
			ssl<<"Ring_n="<<arg.at("n")<<"_k="<<arg.at("k")<<"_l_pc="<<perturbCount;

			ofstream fh(ssh.str()+".txt");
			ofstream fl(ssl.str()+".txt");

			analyser.recTime_highest_one_config(fh,c,dp);
			analyser.recTime_lowest_one_config(fl,c,dp);

			cout<<"\r n="<<arg.at("n")<<" k="<< arg.at("k")
			    <<" c="<<c<<"  "<<flush;
		}
	}
}

