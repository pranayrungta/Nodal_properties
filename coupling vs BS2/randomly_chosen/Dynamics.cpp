#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
	constexpr int repetitions =2 ;
    constexpr double transients = 3;
    constexpr double dt = 0.01;

    constexpr int perturbCount = 10;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}
#include "./../../read_data/read_data.cpp"

#endif // PARAMETERS


#include "./../../Dynamics_base.cpp"

class Dynamics :private Dynamics_base
{public:
	double BS_rand_nodes_perturb(const double& c, const data_point& dp)
	{using parameter::repetitions;
	using parameter::perturbCount;
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
//			for(int i=0; i<x.size(); i++)
//				cout<<"node "<<i<<" : "<<x[i]<<endl;
		}
		B_S_ /= repetitions;
		return B_S_ ;
	}
};
