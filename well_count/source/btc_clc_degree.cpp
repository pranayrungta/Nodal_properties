#ifndef PARAMETERS /// for testing only
#include "parameters.cpp"
#endif

#include "./../../read_data/read_data.cpp"
#include "./../../Dynamics_base.cpp"
#include<unordered_set>
#include<unordered_map>



class Processor : protected Dynamics_base
{public:
	Processor(const string filename);

	void openfiles(const int pc);

	void write_to_file(const int pc, const double c);

	void closefiles();

protected:
	const vector<data_point> data;
	unordered_set<string> unique_tags;
	unordered_map<string,int> config_count;
	unordered_map<string,double>    countH, countL;
	unordered_map<string,ofstream*> filesh, filesl;

	int positive_well_count();

	double positive_count_one_config(const double& c,
		const data_point& dp, const vector<int>& perturb_nodes);

	virtual void calculate_avg_positive_count(
					const int pc, const double c);
};












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

void Processor::openfiles(const int pc)
{
	for(auto& tag:unique_tags) {
		ostringstream ssh, ssl;

		ssh<<tag<<"_h_pc="<<pc<<".txt";
		ssl<<tag<<"_l_pc="<<pc<<".txt";

		filesh[tag]= new ofstream(ssh.str());
		filesl[tag]= new ofstream(ssl.str());

		(*filesh[tag])<<"#coupling"<<"\t"<<"positivecountHighest"<<endl;
		(*filesl[tag])<<"#coupling"<<"\t"<<"positivecountLowest"<<endl;  }
}

void Processor::write_to_file(const int pc, const double c)
{
	calculate_avg_positive_count(pc,c);
	for(auto& tag:unique_tags) {
		(*filesh[tag])<<c<<"\t"<<countH[tag]<<endl;
		(*filesl[tag])<<c<<"\t"<<countL[tag]<<endl; }
}

void Processor::closefiles()
{
	for(auto& i : filesh) {
		(i.second)->close();
		delete i.second; }
	for(auto& i : filesl) {
		(i.second)->close();
		delete i.second; }
	filesh.clear();
	filesl.clear();
}

int Processor::positive_well_count()
{
	int c=0;
	for(auto xi: x)
		if(xi>0)c++;
	return c;
}

double Processor::positive_count_one_config(const double& c,
		const data_point& dp, const vector<int>& perturb_nodes)
{using parameter::repetitions;
using parameter::transients;
using  parameter::dt;
	if(dp.nbr.size()!=x.size()) {
		x.resize(dp.nbr.size());
		Dx.resize(dp.nbr.size()); }

	double avgCount= 0;
	for(int repNo=0; repNo<repetitions; repNo++) {
		fnode_BS_initialize(perturb_nodes);
		for(double t=0; t<transients; t+=dt)
			evolveNodes(c,dp.nbr);
		avgCount += positive_well_count(); }
	avgCount /= repetitions;
	return avgCount;
}

void Processor::calculate_avg_positive_count(
					const int pc, const double c)
{
	countH.clear(); countL.clear();
	for(auto& dp : data)
	{
		vector<int> perturbNodes = samplehighest(dp.ndpr,pc);
		countH[dp.tag] += positive_count_one_config(
									c,dp,perturbNodes);
		perturbNodes= samplelowest(dp.ndpr,pc);
		countL[dp.tag] += positive_count_one_config(
									c,dp,perturbNodes);
	}
	for(auto& i: countH)
		i.second /= config_count[i.first];
	for(auto& i: countL)
		i.second /= config_count[i.first];
}
