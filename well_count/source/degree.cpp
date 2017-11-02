#include "btc_clc_degree.cpp"

class Degree:public Processor
{public:
	Degree(const string filename):
		Processor(filename){};

	void calculate_avg_positive_count(
			const int pc, const double c)override
	{
		countH.clear(); countL.clear();
		for(auto& dp : data){
			vector<int> perturbNodes = highest_degree(dp.nbr,pc);
			countH[dp.tag] += positive_count_one_config(
										c,dp,perturbNodes);
			perturbNodes= lowest_degree(dp.nbr,pc);
			countL[dp.tag] += positive_count_one_config(
										c,dp,perturbNodes); }
		for(auto& i: countH)
			i.second /= config_count[i.first];
		for(auto& i: countL)
			i.second /= config_count[i.first];
	}
};

int main()
{using namespace parameter;

	Degree process(datafile);
	for(const int pc : perturbCountRange){
		process.openfiles(pc);
		for(const double c:cRange)
			process.write_to_file(pc,c);
		process.closefiles(); }
}
