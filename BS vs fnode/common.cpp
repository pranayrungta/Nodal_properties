#include "./../read_data/read_data.cpp"
#include "./../Dynamics_base.cpp"
#include<sstream>

struct BS_count
{
	double BSh=0;
	double BSl=0;
	int count=0;
};


void write_fnodeVsBS(const string& filename_highest,
					 const string& filename_lowest,
					 const map<int,BS_count>& fnode_BScount)
{
	ofstream fh(filename_highest);
	ofstream fl(filename_lowest);
	fh<<"#pc"<<"\t"<<"BShighest"<<endl;
	fl<<"#pc"<<"\t"<<"BSlowest"<<endl;

	for(auto& fn_V: fnode_BScount)
	{
		fh<<fn_V.first<<"\t"<<fn_V.second.BSh<<endl;
		fl<<fn_V.first<<"\t"<<fn_V.second.BSl<<endl;
	}
}
