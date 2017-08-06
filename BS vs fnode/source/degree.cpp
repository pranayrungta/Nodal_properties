#include "btc_clc_degree.cpp"

class Degree:public Processor
{public:
	Degree(const string filename):
		Processor(filename){}

	void calculteBS(const int pc, const double c)override
	{
		BSh.clear();
		BSl.clear();
		for(auto& dp : data)
		{
			vector<int> perturbNodes = analyser.highest_degree(dp.nbr,pc);
			BSh[dp.tag] += analyser.BS_one_config(c,dp,perturbNodes);
			perturbNodes= analyser.lowest_degree(dp.nbr,pc);
			BSl[dp.tag] += analyser.BS_one_config(c,dp,perturbNodes);
		}
		for(auto& i: BSh)
			i.second /= count_config[i.first];
		for(auto& i: BSl)
			i.second /= count_config[i.first];
	}
};




int main()
{using namespace parameter;

	Degree process(datafile);
	for(const double c:cRange)
	{
		process.openfiles(c);
		for(const int pc : perturbCountRange)
			process.write_to_file(pc,c);
		process.closefiles();
	}
}

