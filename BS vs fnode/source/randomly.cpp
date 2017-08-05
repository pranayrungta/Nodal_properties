#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
	string datafile = "./../btc_RSFsample.txt";

    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9} ;
    const vector<int> perturbCountRange{1};

	constexpr int repetitions =2 ;
    constexpr double transients = 3;
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

class Dynamics :private Dynamics_base
{public:
	double BS_rand_nodes_perturb(const int perturbCount,const double& c, const data_point& dp)
	{using parameter::repetitions;
	using parameter::transients;
	using  parameter::dt;

		if(dp.nbr.size()!=x.size())
		{
			x.resize(dp.nbr.size());
			Dx.resize(dp.nbr.size());
		}
		double B_S_ = 0;
		for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
		{
			auto perturbNodes = sample(0,dp.nbr.size()-1,perturbCount,-1);
			fnode_BS_initialize( perturbNodes );
			for(double t=0; t<transients; t+=dt)
				evolveNodes(c,dp.nbr);
			if(syncWell()==parameter::initial_well)
				B_S_++;
		}
		B_S_ /= repetitions;
		return B_S_ ;
	}
};



class Processor
{public:

	Processor(const string filename);

	void openfiles(const double c);

	void write_to_file(const int pc, const double c);

	void closefiles();

private:
	const vector<data_point> data;
	unordered_set<string> unique_tags;
	map<string,int> count_config;

	Dynamics analyser;
	map<string,double> BS;
	map<string,ofstream*> files;

	void calculteBS(const int pc, const double c);
};




int main()
{using namespace parameter;

	Processor process(datafile);
	for(const double c:cRange)
	{
		process.openfiles(c);
		for(const int pc : perturbCountRange)
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
	BS.clear();
	for(auto& dp : data)
		BS[dp.tag] += analyser.BS_rand_nodes_perturb(pc,c,dp);

	for(auto& i: BS)
		i.second /= count_config[i.first];
}

void Processor::openfiles(const double c)
{
	for(auto& tag:unique_tags)
	{
		ostringstream ss;
		ss<<tag<<"_c="<<c<<".txt";
		files[tag]= new ofstream(ss.str());
		(*files[tag])<<"#pc"<<"\t"<<"BS"<<endl;
	}
}

void Processor::write_to_file(const int pc, const double c)
{
	calculteBS(pc,c);
	for(auto& tag:unique_tags)
		(*files[tag])<<pc<<"\t"<<BS[tag]<<endl;
}

void Processor::closefiles()
{
	for(auto& i : files)
	{
		(i.second)->close();
		delete i.second;
	}
	files.clear();
}
