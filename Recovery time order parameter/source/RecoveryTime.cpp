#ifndef PARAMETERS
#define PARAMETERS

#include "./../../Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
    const vector<double> cRange {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9} ;

    vector<int> perturbCountRange{10};
    constexpr int repetitions =100 ;

    constexpr double transients = 100;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}
#include "./../../read_data/read_data.cpp"

#endif // PARAMETERS


#include "./../../Dynamics_base.cpp"

class Dynamics : public Dynamics_base
{public:
	/// calculates basin stability for a fixed configuration and different initial conditions
	double recTime_one_config(const double& c, const data_point& dp, const vector<int>& perturbNodes )
	{using parameter::repetitions;
	using parameter::transients;
	using  parameter::dt;
		if(dp.nbr.size()!=x.size())
		{
			x.resize(dp.nbr.size());
			Dx.resize(dp.nbr.size());
		}

		double avg_rec_time=0;
		for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
		{
			fnode_BS_initialize(perturbNodes);
			double rec_time=0;
			for(double t=0; t<transients; t+=dt)
			{
				evolveNodes(c,dp.nbr);
				if(syncWell()==parameter::initial_well)
				{
					rec_time=t;
					break;
				}
			}
			if(rec_time==0)
				rec_time=transients;
			avg_rec_time+=rec_time;
		}
		avg_rec_time/=repetitions;
		return avg_rec_time;
	}
};

