#include "./../RSF.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{200};
    vector<int> kRange{1};
    int iniCond = 1000;

	ostringstream ss;
	ofstream f("RSF_n=200_k=1_ic=1000.txt");
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

