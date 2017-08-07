#ifndef PARAMETERS
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
    constexpr int perturbCount = 10;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;

	int repetitions=-1;
}

#endif







#include "./../../read_data/read_data.cpp"
#include "./../../Dynamics_base.cpp"
class Dynamics : public Dynamics_base
{public:

	void spt_one_config(ostream& os, const double& c, const data_point& dp,const vector<int> perturbNodes)
	{using parameter::transients;
	using  parameter::dt;
		if(dp.nbr.size()!=x.size())
		{
			x.resize(dp.nbr.size());
			Dx.resize(dp.nbr.size());
		}

		os<<"time\\nodes";
		for(int i=0; i<x.size(); i++)
			os<<"\t"<<i;
		os<<endl;

        fnode_BS_initialize( perturbNodes );
        for(double t=0; t<transients; t+=dt)
        {
			os<<t;
			for(int i=0; i<x.size(); i++)
				os<<"\t"<<x[i];
			os<<endl;

            evolveNodes(c,dp.nbr);
        }
	}
};
