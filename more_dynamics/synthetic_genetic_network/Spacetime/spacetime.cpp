#ifndef PARAMETERS
#define PARAMETERS

#include "./../../../Topology/common_base.cpp"
constexpr double positive_well = 1.42;
constexpr double negative_well = 0.19;
constexpr double mid_well = 0.77;
namespace parameter
{
    const vector<double> cRange {0.9, 1.0, 1.1} ;

    constexpr int perturbCount = 10;
    constexpr int repetitions=100;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = mid_well;
    constexpr double perturbRange_final = mid_well + 2*(positive_well-mid_well);
}
#include "./../../../read_data/read_data.cpp"

#endif // PARAMETERS
///-----------------------------------------------------------


#include "./../Dynamics.cpp"

class Spacetime : protected Dynamics
{public:
	/// calculates basin stability for a fixed configuration and different initial conditions
	void spt_highest_one_config(ostream& os,const double& c, const data_point& dp, const int pc)
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


	void spt_lowest_one_config(ostream& os, const double& c, const data_point& dp, const int pc)
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
