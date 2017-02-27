#include "./../Ring.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{100};
    vector<int> kRange{2};


	ofstream f("Ring.txt");
	f<<"[ "<<endl;
    for(auto n : nRange)
    for(auto k : kRange)
    {
        Ring network(n,k);
        ostringstream ss;
        //ss<<"'Ring"<<"_n="<<n<<"_k="<<k<<"' ";
        ss<<"{'n':"<<n<<", 'k':"<<k<<"},";

        f<<"[  "<<ss.str()<<endl;
        f<<network<<"] ,"<<endl<<endl;

        cout<<"\r "<<ss.str()<<"   "<<flush;
    }
    f<<"]";
}


