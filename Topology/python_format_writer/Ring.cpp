#include "./../Ring.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{100};
    vector<int> kRange{2};


	ofstream f("Ring.txt");
	f<<"[ "<<endl<<endl;
    for(auto n : nRange)
    for(auto k : kRange)
    {
        Ring network(n,k);
        f<<"[  '"<<network.tag()<<"',"<<endl;
        f<<network<<"] ,"<<endl<<endl;

        cout<<network.tag()<<endl;
    }
    f<<"]";
}


