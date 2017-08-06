#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "./../../../Topology/common_base.cpp"
constexpr double positive_well = 1;
constexpr double negative_well = -1;
namespace parameter
{
    constexpr int perturbCount = 10;
    constexpr int repetitions=100;

    constexpr double dt = 0.01;
    constexpr double transients = 100;

    constexpr double initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}
#include "./../../../read_data/read_data.cpp"

#endif // PARAMETERS

struct local_Dynamics
{
	double  xu = 1.0   ;
	double  xl = -1.0  ;
	double  alp = 1.8  ;
	double  bet = 3.0  ;

	double operator()(const double& x)const
	{
		if(x<xl)
			return -alp*x +bet*xl;
		else if(x<=xu)
			return -alp*x +bet*x;
		else
			return -alp*x +bet*xu;
	}
};
class Dynamics
{public:
    vector<double> x;
    vector<double> Dx;
    local_Dynamics g;

    void fnode_BS_initialize(const vector<int>& fnodes);
    double syncWell();
    void evolveNodes(const double c,const vector<vector<int>>& network);

	vector<int> samplehighest(const multimap<double,int>& btc, const int perturbCount);
	vector<int> samplelowest(const multimap<double,int>& btc, const int perturbCount);

    constexpr static double unsync = 0;

	/// calculates basin stability for a fixed configuration and different initial conditions
	double BShighest_one_config(const double& c, const data_point& dp, const int perturbCount);

	double BSlowest_one_config(const double& c, const data_point& dp, const int perturbCount);
};





///------------implementation of class functions----------------

/// calculates basin stability for a fixed configuration and different initial conditions
double Dynamics::BShighest_one_config(const double& c, const data_point& dp, const int perturbCount)
{using parameter::repetitions;
using parameter::transients;
using  parameter::dt;
	if(dp.nbr.size()!=x.size())
	{
		x.resize(dp.nbr.size());
		Dx.resize(dp.nbr.size());
	}
	auto highest_btc_Nodes = samplehighest(dp.ndpr,perturbCount);

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


double Dynamics::BSlowest_one_config(const double& c, const data_point& dp, const int perturbCount)
{using parameter::repetitions;
using parameter::transients;
using  parameter::dt;
	if(dp.nbr.size()!=x.size())
	{
		x.resize(dp.nbr.size());
		Dx.resize(dp.nbr.size());
	}
	auto lowest_btc_Nodes = samplelowest(dp.ndpr,perturbCount);

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



void Dynamics::fnode_BS_initialize(const vector<int>& fnodes)
{using parameter::initial_well;
using parameter::spread;
using parameter::perturbRange_initial;
using parameter::perturbRange_final;

using real_dist = uniform_real_distribution<double>;

    static real_dist init_well(initial_well-spread, initial_well+spread);
    for(int i=0; i<x.size() ; i++)
    {
        x[i]= init_well(generator) ;
        Dx[i]=0;
    }

    static real_dist perturbRange(perturbRange_initial, perturbRange_final);
    for(auto nodeNo : fnodes)
        x[nodeNo] = perturbRange(generator);
}



///function to check if all nodes are in same well
double Dynamics::syncWell()
{
    double& first = x[0];
    for(int i=1; i<x.size(); i++)
        if(x[i]*first<0)
            return unsync;

    if(first>0)return positive_well;
    if(first<0)return negative_well;
}

///function to evolve sites
void Dynamics::evolveNodes(const double c,const vector<vector<int>>& network)
{using parameter::dt;
    int n= x.size();
    double nf=0;

    int i,j;
    //Calculating derivatives
    for(i=0; i<n; i++)
    {
        nf=0;
        for( j=0; j<network[i].size(); j++ )
            nf+=x[ network[i][j] ];
        nf /= network[i].size();

        Dx[i] = g(x[i]) + c*(nf- x[i]) ;
    }
    //Evolving nodes
    for( i=0; i<n; i++)
        x[i] += Dx[i] * dt  ;
}



vector<int> Dynamics::samplehighest(const multimap<double,int>& btc, const int perturbCount)
{
	if(btc.size()<perturbCount)
	{
		cout<<"btc multimap has less elements than requested"<<endl;
		exit(1);
	}
	vector<int> values(perturbCount);
	auto highest = btc.end();
	for(int i=0; i<perturbCount; i++)
	{
		highest--;
		values[i] = (*highest).second;
	}
	return values;
}

vector<int> Dynamics::samplelowest(const multimap<double,int>& btc, const int perturbCount)
{
	if(btc.size()<perturbCount)
	{
		cout<<"btc multimap has less elements than requested"<<endl;
		exit(1);
	}
	vector<int> values(perturbCount);
	auto lowest = btc.begin();
	for(int i=0; i<perturbCount; i++)
	{
		values[i] = (*lowest).second;
		lowest++;
	}
	return values;
}

