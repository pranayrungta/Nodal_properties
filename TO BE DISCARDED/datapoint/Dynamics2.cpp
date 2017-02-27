#include<fstream>

int progress=0;

class Dynamics
{public:
	vector<data_point> config;
    vector<double> x, Dx;

    Dynamics(string filename);

    void fnode_BS_initialize(const vector<int>& fnodes);
    int syncWell();
    void evolveNodes(const double c,const vector<vector<int>>& network);

	vector<int> samplehighest(const multimap<double,int>& btc);
	vector<int> samplelowest(const multimap<double,int>& btc);

	/// calculates basin stability for a fixed configuration and different initial conditions
	void aoic(const double& c, const data_point& dp, double& BShighest, double& BSlowest);
	/// calculates BS averaged over configurations
	void avg_over_config(const double c, double& BShighest, double& BSlowest);

private:
    constexpr static int unsync = 0;
};



int main()
{using parameter::cRange;
	Dynamics analyser("reader2/data.txt");

	ofstream f("result.txt");
	f<<"#coupling\tBShighest\tBSlowest"<<endl;
	double BShighest,BSlowest;
	for(const auto c : cRange)
	{
		analyser.avg_over_config(c,BShighest, BSlowest);
		f<<c<<"\t"<<BShighest<<"\t"<<BSlowest<<endl;
	}
}










///------------implementation of class functions----------------
Dynamics::Dynamics(string filename)
{
	ifstream f(filename);
	config = read_data(f);
	if(config.size()>0)
	{
		int size = config[0].nbr.size();
		x  = vector<double> (size);
		Dx = vector<double> (size);
	}
}

void Dynamics::fnode_BS_initialize(const vector<int>& fnodes)
{using parameter::initial_well;
using parameter::spread;
using parameter::perturbRange_initial;
using parameter::perturbRange_final;

    uniform_real_distribution<double>  distribution(initial_well-spread, initial_well+spread);
    for(int i=0; i<x.size() ; i++)
    {
        x[i]= distribution(generator) ;
        Dx[i]=0;
    }

    uniform_real_distribution<double>  perturbRange(perturbRange_initial, perturbRange_final);
    for(auto nodeNo : fnodes)
        x[nodeNo] = perturbRange(generator);
}



///function to check if all nodes are in same well
int Dynamics::syncWell()
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

        Dx[i] = ( x[i]- x[i]*x[i]*x[i] ) + c*(nf- x[i]) ;
    }
    //Evolving nodes
    for( i=0; i<n; i++)
        x[i] += Dx[i] * dt  ;
}



vector<int> Dynamics::samplehighest(const multimap<double,int>& btc)
{using parameter::perturbCount;
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

vector<int> Dynamics::samplelowest(const multimap<double,int>& btc)
{using parameter::perturbCount;
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


void Dynamics::aoic(const double& c, const data_point& dp,double& BShighest, double& BSlowest)
{using parameter::repetitions;
using parameter::transients;
using  parameter::dt;

	BShighest = 0;
	for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
	{
		fnode_BS_initialize( samplehighest(dp.btc) );
		for(double t=0; t<transients; t+=dt)
			evolveNodes(c,dp.nbr);
		if(syncWell()==parameter::initial_well)
			BShighest++;
	}
	BShighest /= repetitions;

	BSlowest = 0;
	for(int repetitionNo=0; repetitionNo<repetitions; repetitionNo++)
	{
		fnode_BS_initialize( samplelowest(dp.btc) );
		for(double t=0; t<transients; t+=dt)
			evolveNodes(c,dp.nbr);
		if(syncWell()==parameter::initial_well)
			BSlowest++;
	}
	BSlowest /= repetitions;
}


void Dynamics::avg_over_config(const double c, double& BShighest, double& BSlowest)
{
	BShighest=0;
	BSlowest =0;
	double high=0,low=0;
	for(auto& ith_config : config)
	{
		progress++;
		cout<<"c= "<<c<<"\tconfigNo: "<<progress<<endl;

		aoic(c,ith_config,high,low);
		BShighest += high;
		BSlowest += low;
	}
	BShighest/= config.size();
	BSlowest /= config.size();

}
