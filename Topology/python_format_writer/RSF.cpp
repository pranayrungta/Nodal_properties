#include "./../RSF.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{7};
    vector<int> kRange{1};
    int iniCond = 3;

	ofstream f("RSFsample.txt");
	f<<"[ "<<endl;
    for(auto n : nRange)
    for(auto k : kRange)
    for(int ic=1; ic<=iniCond; ic++)
    {
        RSF network(n,k);
        ostringstream ss;
        //ss<<"'RSF"<<"_n="<<n<<"_k="<<k<<"_ic="<<ic<<"' ";
        ss<<"{ 'n':"<<n<<", 'k':"<<k <<"}, #RSF ic="<<ic;

        f<<"[  "<<ss.str()<<endl;
        f<<network<<","<<endl;
        //f<<"# degree distribution"<<endl;
        //f<<getDegreeDistribution(network);
        f<<"] ,"<<endl<<endl;

        cout<<"\n "<<ss.str()<<"   "<<flush;
    }
    f<<"]";
}

