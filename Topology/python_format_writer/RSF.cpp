#include "./../RSF.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{7};
    vector<int> kRange{1,2};
    int iniCond = 3;

	ofstream f("RSF.txt");
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

