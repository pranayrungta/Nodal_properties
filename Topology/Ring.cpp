#ifndef RING_CPP
#define RING_CPP

#include "common_base.cpp"

class Ring : public topology_base
{public:
    //Constructor
    Ring (const int n, const short k):
    	topology_base(vector<vector<int>>(n,vector<int>(k)))
	{
		int k_left= k/2;
		int k_right= (k%2==0)?k/2: k/2+1;

		for(int i=0; i<n; i++)
		{
			//regular neighbors
			int j=0, c=0;
			for(j=-k_left;j<0; j++)
			{
				nbr[i][c] = (n+i+j)%n ;
				c++;
			}
			for(j=1;j<=k_right; j++)
			{
				nbr[i][c] = (n+i+j)%n ;
				c++;
			}
		}
	}

	string tag()
	{
		ostringstream ss;
		ss<<"Ring_n="<<nbr.size()<<"_k="<<nbr.back().size();
		return ss.str();
	}
};


int mainRing()
{
    Ring a(10,2);
//    a.display_details();
    cout<<a<<a[0]<<endl;
    //cout<<Ring(88,3);
    cout<<a.tag();
    return 0;
}

#endif
