#ifndef PARAMETERS /// for testing only
#include "parameters.cpp"
#endif

#include "./../../read_data/read_data.cpp"
#include "./../../Dynamics_base.cpp"
#include<unordered_set>

class Processor : protected Dynamics_base
{public:
	Processor(const string filename);

	void openfiles(const int pc);

	void write_to_file(const int pc, const double c);

	void closefiles();

private:
	const vector<data_point> data;
	unordered_set<string> unique_tags;
	map<string,int> config_count;
	map<string,double> pcountR;
	map<string,ofstream*> files;

	int positive_well_count();

	double positive_count_one_config(const int perturbCount,
								const double& c, const data_point& dp);

	void calculate_avg_positive_count(const int pc, const double c);
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
		config_count[dp.tag]++;
	}
}

void Processor::openfiles(int pc)
{
	for(auto& tag:unique_tags)
	{
		ostringstream ss;
		ss<<tag<<"_pc="<<pc<<".txt";
		files[tag]= new ofstream(ss.str());
		(*files[tag])<<"#coupling"<<"\t"<<"+veCount_randomPerturb\n";
	}
}

void Processor::write_to_file(int pc,double c)
{
	calculate_avg_positive_count(pc,c);
	for(auto& tag:unique_tags)
		(*files[tag])<<c<<"\t"<<pcountR[tag]<<endl;
}

void Processor::closefiles()
{
	for(auto& i : files){
		(i.second)->close();
		delete i.second; }
	files.clear();
}

int Processor::positive_well_count()
{
	int c=0;
	for(auto xi: x)
		if(xi>0)c++;
	return c;
}

double Processor::positive_count_one_config(const int perturbCount,
								const double& c, const data_point& dp)
{using parameter::repetitions;
using parameter::transients;
using  parameter::dt;
	if(dp.nbr.size()!=x.size()) {
		x.resize(dp.nbr.size());
		Dx.resize(dp.nbr.size()); }

	double avgCount= 0;
	for(int repNo=0; repNo<repetitions; repNo++){
		const vector<int> perturb_nodes=
							sample(0,dp.nbr.size()-1,perturbCount,-1);
		fnode_BS_initialize(perturb_nodes);
		for(double t=0; t<transients; t+=dt)
			evolveNodes(c,dp.nbr);
		avgCount += positive_well_count(); }
	avgCount /= repetitions;
	return avgCount;
}

void Processor::calculate_avg_positive_count(int pc,double c)
{
	pcountR.clear();
	for(auto& dp : data)
		pcountR[dp.tag] += positive_count_one_config(pc,c,dp);
	for(auto& i: pcountR)
		i.second /= config_count[i.first];
}
