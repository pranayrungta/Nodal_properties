#include "./../../read_data/read_data.cpp"
#include<iostream>
#include<map>
using namespace std;

int main()
{
	const string filename = "btc_Star.txt";
	const string outfilename = "freq_"+filename;

	auto data = read_data_from_file(filename);

	map<double,int> frequency;

	double total_count=0;
	for(auto& dp : data)
	{
		auto& ndpr = dp.ndpr;
		for(auto& i : ndpr)
		{
			frequency[i.first]++;
			total_count++;
		}
	}

	ofstream f(outfilename);
	f<<"# btc"<<"\t"<<"count"<<"\t"<<"prob"<<endl;
	for(auto& i:frequency)
		f<<i.first<<"\t"<<i.second<<"\t"
		   <<i.second/total_count<<endl;

}
