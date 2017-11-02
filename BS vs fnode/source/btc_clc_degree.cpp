#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
	string datafile = "./../btc_RSFsample.txt";

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



#include "./../../read_data/read_data.cpp"
#include "./../../Dynamics_base.cpp"
#include<unordered_set>

class Processor
{public:

	Processor(const string filename);

	void openfiles(const double c);

	void write_to_file(const int pc, const double c);

	void closefiles();

protected:
	const vector<data_point> data;
	unordered_set<string> unique_tags;
	map<string,int> count_config;

	Dynamics_base analyser;
	map<string,double> BSh;
	map<string,double> BSl;
	map<string,ofstream*> filesh;
	map<string,ofstream*> filesl;

	virtual void calculteBS(const int pc, const double c);
};





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
		BSh[dp.tag] += analyser.BS_one_config(c,dp,perturbNodes);
		perturbNodes= analyser.samplelowest(dp.ndpr,pc);
		BSl[dp.tag] += analyser.BS_one_config(c,dp,perturbNodes);
	}

	for(auto& i: BSh)
		i.second /= count_config[i.first];
	for(auto& i: BSl)
		i.second /= count_config[i.first];
}

void Processor::openfiles(const double c)
{
	for(auto& tag:unique_tags)
	{
		ostringstream ssh;
		ostringstream ssl;

		ssh<<tag<<"_h_c="<<c<<".txt";
		ssl<<tag<<"_l_c="<<c<<".txt";

		filesh[tag]= new ofstream(ssh.str());
		filesl[tag]= new ofstream(ssl.str());

		(*filesh[tag])<<"#pc"<<"\t"<<"BShighest"<<endl;
		(*filesl[tag])<<"#pc"<<"\t"<<"BSlowest"<<endl;
	}
}

void Processor::write_to_file(const int pc, const double c)
{
    if(pc==0)
    {
        for(auto& tag:unique_tags)
        {
            (*filesh[tag])<<pc<<"\t"<<1<<endl;
            (*filesl[tag])<<pc<<"\t"<<1<<endl;
        }
    }
    else
    {
        calculteBS(pc,c);
        for(auto& tag:unique_tags)
        {
            (*filesh[tag])<<pc<<"\t"<<BSh[tag]<<endl;
            (*filesl[tag])<<pc<<"\t"<<BSl[tag]<<endl;
        }
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

