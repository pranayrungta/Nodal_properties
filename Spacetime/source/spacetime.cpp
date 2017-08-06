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
	/// calculates basin stability for a fixed configuration and different initial conditions
	void spt_highest_one_config(ostream& os,const double& c, const data_point& dp,const int pc)
	{using parameter::transients;
	using  parameter::dt;
		if(dp.nbr.size()!=x.size())
		{
			x.resize(dp.nbr.size());
			Dx.resize(dp.nbr.size());
		}
		auto highest_btc_Nodes = samplehighest(dp.ndpr,pc);

		os<<"time\\nodes";
		for(int i=0; i<x.size(); i++)
			os<<"\t"<<i;
		os<<endl;

        fnode_BS_initialize(highest_btc_Nodes);
        for(double t=0; t<transients; t+=dt)
        {
			os<<t;
			for(int i=0; i<x.size(); i++)
				os<<"\t"<<x[i];
			os<<endl;

            evolveNodes(c,dp.nbr);
        }
	}


	void spt_lowest_one_config(ostream& os, const double& c, const data_point& dp,const int pc)
	{using parameter::transients;
	using  parameter::dt;
		if(dp.nbr.size()!=x.size())
		{
			x.resize(dp.nbr.size());
			Dx.resize(dp.nbr.size());
		}
		auto lowest_btc_Nodes = samplelowest(dp.ndpr,pc);

		os<<"time\\nodes";
		for(int i=0; i<x.size(); i++)
			os<<"\t"<<i;
		os<<endl;

        fnode_BS_initialize( lowest_btc_Nodes );
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

