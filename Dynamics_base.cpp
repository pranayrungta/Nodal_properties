#ifndef PARAMETERS ///for testing only
#define PARAMETERS

#include "Topology/common_base.cpp"
constexpr int positive_well = 1;
constexpr int negative_well = -1;
namespace parameter
{
    //constexpr int perturbCount = 10;
    constexpr double dt = 0.01;

    constexpr int initial_well= negative_well ;
    constexpr double spread= 0.25 ;
    constexpr double perturbRange_initial = 0;
    constexpr double perturbRange_final = 5;
}

#endif /// PARAMETERS


class Dynamics_base
{public:
    vector<double> x;
    vector<double> Dx;

    void fnode_BS_initialize(const vector<int>& fnodes);
    int syncWell();
    void evolveNodes(const double c,const vector<vector<int>>& network);

	vector<int> samplehighest(const multimap<double,int>& btc, int perturbCount);
	vector<int> samplelowest(const multimap<double,int>& btc, int perturbCount);

	vector<int> highest_degree(const vector<vector<int>>& nbrs, int perturbCount);
	vector<int> lowest_degree(const vector<vector<int>>& nbrs, int perturbCount);

    constexpr static int unsync = 0;
};



int maindymb()
{
	Dynamics_base t;
    cout<<t.x;
	return 0;
}
//-------------------------------------------------







///------------implementation of class functions----------------


void Dynamics_base::fnode_BS_initialize(const vector<int>& fnodes)
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
int Dynamics_base::syncWell()
{
    double& first = x[0];
    for(int i=1; i<x.size(); i++)
        if(x[i]*first<0)
            return unsync;

    if(first>0)return positive_well;
    if(first<0)return negative_well;
}

///function to evolve sites
void Dynamics_base::evolveNodes(const double c,const vector<vector<int>>& network)
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

        Dx[i] = ( x[i]- x[i]*x[i]*x[i] ) + c*(nf- x[i]) ;
    }
    //Evolving nodes
    for( i=0; i<n; i++)
        x[i] += Dx[i] * dt  ;
}



vector<int> Dynamics_base::samplehighest(const multimap<double,int>& btc, int perturbCount)
{
	if(btc.size()<perturbCount)
	{
		cout<<"multimap has less elements than requested"<<endl;
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

vector<int> Dynamics_base::samplelowest(const multimap<double,int>& btc, int perturbCount)
{
	if(btc.size()<perturbCount)
	{
		cout<<"multimap has less elements than requested"<<endl;
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



vector<int> Dynamics_base::highest_degree(const vector<vector<int>>& nbrs, int perturbCount)
{
	if(nbrs.size()<perturbCount)
	{
		cout<<"nbr has less elements than requested"<<endl;
		exit(1);
	}

	multimap<double,int> degree_node;
	for(int i=0; i<nbrs.size(); i++)
		degree_node.insert( pair<int,int>(nbrs[i].size(),i) );

	vector<int> values(perturbCount);
	auto highest = degree_node.end();
	for(int i=0; i<perturbCount; i++)
	{
		highest--;
		values[i] = (*highest).second;
	}
	return values;
}

vector<int> Dynamics_base::lowest_degree(const vector<vector<int>>& nbrs, int perturbCount)
{
	if(nbrs.size()<perturbCount)
	{
		cout<<"nbr has less elements than requested"<<endl;
		exit(1);
	}

	multimap<double,int> degree_node;
	for(int i=0; i<nbrs.size(); i++)
		degree_node.insert( pair<int,int>(nbrs[i].size(),i) );

	vector<int> values(perturbCount);
	auto lowest =  degree_node.begin();
	for(int i=0; i<perturbCount; i++)
	{
		values[i] = (*lowest).second;
		lowest++;
	}
	return values;
}
