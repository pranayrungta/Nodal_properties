//#include "./../../Topology/common_base.cpp"
//#include "./../../read_data/read_data.cpp"
//constexpr int positive_well = 1;
//constexpr int negative_well = -1;
//namespace parameter
//{
//    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9} ;
//
//    constexpr int perturbCount = 10;
//    constexpr int repetitions =100 ;
//
//    constexpr double transients = 100;
//    constexpr double dt = 0.01;
//
//    constexpr int initial_well= negative_well ;
//    constexpr double spread= 0.25 ;
//    constexpr double perturbRange_initial = 0;
//    constexpr double perturbRange_final = 5;
//}
//#include "./../../Dynamics_base.cpp"
/////-----------------------------------------------------------



class Dynamics : public Dynamics_base
{public:
	/// calculates basin stability for a fixed configuration and different initial conditions
	double recTime_highest_one_config(const double& c, const data_point& dp)
	{using parameter::repetitions;
	using parameter::transients;
	using  parameter::dt;
		if(dp.nbr.size()!=x.size())
		{
			x.resize(dp.nbr.size());
			Dx.resize(dp.nbr.size());
		}
		auto highest_btc_Nodes = samplehighest(dp.btc);

		for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
		{
			fnode_BS_initialize(highest_btc_Nodes);
			for(double t=0; t<transients; t+=dt)
			{
				evolveNodes(c,dp.nbr);
				if(syncWell()==parameter::initial_well)
					return t;
			}
		}
		return transients;
	}


	double recTime_lowest_one_config(const double& c, const data_point& dp)
	{using parameter::repetitions;
	using parameter::transients;
	using  parameter::dt;
		if(dp.nbr.size()!=x.size())
		{
			x.resize(dp.nbr.size());
			Dx.resize(dp.nbr.size());
		}
		auto lowest_btc_Nodes = samplelowest(dp.btc);

		for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
		{
			fnode_BS_initialize( lowest_btc_Nodes );
			for(double t=0; t<transients; t+=dt)
			{
				evolveNodes(c,dp.nbr);
				if(syncWell()==parameter::initial_well)
					return t;
			}
		}
		return transients;
	}
};

