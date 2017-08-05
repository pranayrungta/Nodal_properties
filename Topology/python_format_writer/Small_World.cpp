#include "./../Small_World.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{10,8};
    vector<int> kRange{2};
    vector<double> pRange{0.3,0.5};
    int iniCond = 3;

	ofstream f("SWS.txt");
	f<<"[ "<<endl<<endl;
    for(auto n : nRange)
    for(auto k : kRange)
	{
		Small_World network(n,k);
		for(auto p : pRange)
		for(int ic=1; ic<=iniCond; ic++)
		{
			network.evolve_links(p);
			f<<"[  '"<<network.tag()<<"_p="<<p<<"',  # ic="<<ic<<endl;
			f<<network<<"] ,"<<endl<<endl;

			cout<<network.tag()<<"\tic="<<ic<<endl;
		}
		cout<<endl;
	}
    f<<"]";
}
