#ifndef PARAMETERS ///for testing only
#include "parameters.cpp"
#endif // PARAMETERS

#include "./../../read_data/read_data.cpp"
#include "./../../Dynamics_base.cpp"
#include<unordered_set>
#include<unordered_map>



class Processor
{public:

	Processor(const string filename);

	void openfiles(const int pc);

	void write_to_file(const int pc, const double c);

	void closefiles();

protected:
	const vector<data_point> data;
	unordered_set<string> unique_tags;
	unordered_map<string,int> count_config;

	Dynamics_base analyser;
	unordered_map<string,double> BSh;
	unordered_map<string,double> BSl;
	unordered_map<string,ofstream*> filesh;
	unordered_map<string,ofstream*> filesl;

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
