#include "Topology/common_base.cpp"
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


vector<data_point> data;
void fill_data()
{

data.reserve(2);
data.push_back(data_point({   {4,1},
					{0,2},
					{1,3},
					{2,4},
					{3,0},
				},
				{  { 14, 0},
				   { 11, 1},
				   { 11, 2},
				   { 11, 3},
				   { 19, 4},
				})
			);
data.push_back(data_point( {   {4,1},
			{0,2},
			{1,3},
			{2,4},
			{3,0},
		},
		{  { 14, 0},
		   { 11, 1},
		   { 11, 2},
		   { 11, 3},
		   { 19, 4},
		}
	  ));

};


int main()
{
	fill_data();
	cout<<data[0].nbr;
}
