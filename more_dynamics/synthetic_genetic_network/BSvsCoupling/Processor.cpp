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
    const vector<int> perturbCountRange{1,2};
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
#include<unordered_set>

class Processor
{public:

	Processor(const string filename);

	void openfiles(const int pc);

	void write_to_file(const int pc, const double c);

	void closefiles();

protected:
	const vector<data_point> data;
	unordered_set<string> unique_tags;
	map<string,int> count_config;

	Dynamics analyser;
	map<string,double> BSh;
	map<string,double> BSl;
	map<string,ofstream*> filesh;
	map<string,ofstream*> filesl;

	virtual void calculteBS(const int pc, const double c);
};



int main()
{using namespace parameter;

	Processor process(datafile);
	for(const int pc : perturbCountRange)
	{
		process.openfiles(pc);
		for(const double c:cRange)
			process.write_to_file(pc,c);
		process.closefiles();
	}
}



///--------------implementation of class functions------------
Processor::Processor(const string filename):
	data( read_data_from_file(filename) )
{
	for(auto& dp: data)
	{
		unique_tags.insert(dp.tag);
		count_config[dp.tag]++;
	}
}

void Processor::calculteBS(const int pc, const double c)
{
	BSh.clear();
	BSl.clear();
	for(auto& dp : data)
	{
		BSh[dp.tag] += analyser.BShighest_one_config(c,dp,pc);
		BSl[dp.tag] += analyser.BSlowest_one_config(c,dp,pc);
	}

	for(auto& i: BSh)
		i.second /= count_config[i.first];
	for(auto& i: BSl)
		i.second /= count_config[i.first];
}

void Processor::openfiles(const int pc)
{
	for(auto& tag:unique_tags)
	{
		ostringstream ssh;
		ostringstream ssl;

		ssh<<tag<<"_h_pc="<<pc<<".txt";
		ssl<<tag<<"_l_pc="<<pc<<".txt";

		filesh[tag]= new ofstream(ssh.str());
		filesl[tag]= new ofstream(ssl.str());

		(*filesh[tag])<<"#coupling"<<"\t"<<"BShighest"<<endl;
		(*filesl[tag])<<"#coupling"<<"\t"<<"BSlowest"<<endl;
	}
}

void Processor::write_to_file(const int pc, const double c)
{
	calculteBS(pc,c);
	for(auto& tag:unique_tags)
	{
		(*filesh[tag])<<c<<"\t"<<BSh[tag]<<endl;
		(*filesl[tag])<<c<<"\t"<<BSl[tag]<<endl;
	}
}

void Processor::closefiles()
{
	for(auto& i : filesh)
	{
		(i.second)->close();
		delete i.second;
	}
	for(auto& i : filesl)
	{
		(i.second)->close();
		delete i.second;
	}
	filesh.clear();
	filesl.clear();
}

