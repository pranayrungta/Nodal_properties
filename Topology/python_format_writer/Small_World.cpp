#include "./../Topology/Small_World.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{81};
    vector<int> kRange{2};
    vector<double> pRange{0.3,0.6,0.9};
    int iniCond = 1;

	ofstream f("SWS.txt");
	f<<"[ "<<endl;
    for(auto n : nRange)
    for(auto k : kRange)
	{
		Small_World network(n,k);
		for(auto p : pRange)
		for(int ic=1; ic<=iniCond; ic++)
		{
			network.evolve_links(p);
			ostringstream ss;
			//ss<<"'SWS"<<"_n="<<n<<"_k="<<k<<"_p="<<p<<"_ic="<<ic<<"' ";
			ss<<"{'n':"<<n<<", 'k':"<<k<<", 'p':"<<p<<"},  # ic="<<ic;

			f<<"[  "<<ss.str()<<endl;
			f<<network<<"] ,"<<endl<<endl;

			cout<<"\r "<<ss.str()<<"   "<<flush;
		}
	}
    f<<"]";
}
