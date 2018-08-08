#include "./../RSF.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{100};
    vector<int> kRange{2};
    int iniCond = 1;

	ostringstream ss;
	ofstream f("RSF_n=100_m=2_ic=1.txt");
	f<<"[ "<<endl<<endl;
    for(auto n : nRange)
    for(auto k : kRange)
    for(int ic=1; ic<=iniCond; ic++)
    {
        RSF network(n,k);
        f<<"[  '"<<network.tag()<<"', \t# ic="<<ic<<endl;
        f<<network<<"] ,"<<endl<<endl;

		cout<<network.tag()<<"\tic="<<ic<<endl;
    }
    f<<"]";
}

