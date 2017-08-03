
#include "./../read_data/read_data.cpp"
#include "./../Dynamics_base.cpp"
#include<sstream>

struct BS_count
{
	double bshighest=0;
	double bslowest=0;
	int count=0;
};

void write_CvsBS(const string& filename_highest,
				 const string& filename_lowest,
				 const map<double,BS_count>& coup_BScount)
{
	ofstream fh(filename_highest);
	ofstream fl(filename_lowest);
	fh<<"#coupling"<<"\t"<<"BShighest"<<endl;
	fl<<"#coupling"<<"\t"<<"BSlowest"<<endl;

	for(auto& cv: coup_BScount)
	{
		fh<<cv.first<<"\t"<<cv.second.bshighest<<endl;
		fl<<cv.first<<"\t"<<cv.second.bslowest<<endl;
	}
}
