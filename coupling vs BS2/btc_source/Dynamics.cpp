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
	/// calculates basin stability for a fixed configuration and different initial conditions
	double BShighest_one_config(const double& c, const data_point& dp);

	double BSlowest_one_config(const double& c, const data_point& dp);
};





///------------implementation of class functions----------------

/// calculates basin stability for a fixed configuration and different initial conditions
double Dynamics::BShighest_one_config(const double& c, const data_point& dp)
{using parameter::repetitions;
using parameter::transients;
using  parameter::dt;
	if(dp.nbr.size()!=x.size())
	{
		x.resize(dp.nbr.size());
		Dx.resize(dp.nbr.size());
	}
	auto highest_btc_Nodes = samplehighest(dp.btc);

	double BShighest = 0;
	for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
	{
		fnode_BS_initialize(highest_btc_Nodes);
		for(double t=0; t<transients; t+=dt)
			evolveNodes(c,dp.nbr);
		if(syncWell()==parameter::initial_well)
			BShighest++;
	}
	BShighest /= repetitions;
	return BShighest;
}


double Dynamics::BSlowest_one_config(const double& c, const data_point& dp)
{using parameter::repetitions;
using parameter::transients;
using  parameter::dt;
	if(dp.nbr.size()!=x.size())
	{
		x.resize(dp.nbr.size());
		Dx.resize(dp.nbr.size());
	}
	auto lowest_btc_Nodes = samplelowest(dp.btc);

	double BSlowest = 0;
	for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
	{
		fnode_BS_initialize( lowest_btc_Nodes );
		for(double t=0; t<transients; t+=dt)
			evolveNodes(c,dp.nbr);
		if(syncWell()==parameter::initial_well)
			BSlowest++;
	}
	BSlowest /= repetitions;
	return BSlowest;
}
