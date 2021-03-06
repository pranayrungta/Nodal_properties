#ifndef PARAMETERS
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
	string datafile = "dataSample.txt";

    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9} ;
    vector<int> perturbCountRange{10};

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
		vector<int> perturbNodes = analyser.samplehighest(dp.ndpr,pc);
		BSh[dp.tag] += analyser.recTime_one_config(c,dp,perturbNodes);
		perturbNodes= analyser.samplelowest(dp.ndpr,pc);
		BSl[dp.tag] += analyser.recTime_one_config(c,dp,perturbNodes);
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

		(*filesh[tag])<<"#coupling"<<"\t"<<"RThighest"<<endl;
		(*filesl[tag])<<"#coupling"<<"\t"<<"RTlowest"<<endl;
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
