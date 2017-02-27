#include "./../Topology/common_base.cpp"
#include<map>
#include<vector>
using namespace std;

using links = vector<vector<int>>;
using bt = multimap<double,int>;

struct data_point
{
	links nbr;
	bt btc;
	data_point(links&& nbrs, bt&& btcy)
	{
		nbr.swap(nbrs);
		btc.swap(btcy);
	}
};
#include "data.cpp"


