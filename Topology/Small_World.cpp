#ifndef SMALL_WORLD_CPP
#define SMALL_WORLD_CPP


#include "common_base.cpp"

class Small_World : public topology_base
{public:

    Small_World(const int n, const int k):
    	topology_base( vector<vector<int>>(n,vector<int>(k)) )
    {}

    //function to evolve links
    void evolve_links(const double p_)
    {
		p=p_;
		int n=nbr.size();
		int k=nbr[0].size();
		int k_left= k/2;
		int k_right= (k%2==0)?k/2: k/2+1;

		static uniform_real_distribution<double>  probability_distribution(0, 1);
		for(int i=0; i<n; i++)
		{
			if( probability_distribution(generator) < p )
				nbr[i] = sample(0,n-1,k,i); /// random neighbors
			else
			{   ///regular neighbors
				int c=0;
				for(int j=-k_left; j<=k_right; j++)
				{
					if(j==0)continue;
					nbr[i][c]=(n+i+j)%n ;
					c++;
				}
			}
		}
	}

	string tag(const string swtype="S")
	{
		ostringstream ss;
		ss<<"SW"<<swtype<<"_n="<<nbr.size()
		  <<"_k="<<nbr.back().size()<<"_p="<<p;
		return ss.str();
	}
private:
	double p=0;
};



int mainSW()
{
    Small_World s(10,5);
    s.evolve_links(0.3);

	cout<<s.tag()<<endl;
	cout<<s<<endl;
	cout<<"size = "<<s.size()<<endl;

	return 0;
}



#endif
