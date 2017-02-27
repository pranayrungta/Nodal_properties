#include "./../Star.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{100};

	ofstream f("Star.txt");
	f<<"[ "<<endl;
    for(auto n : nRange)
    {
        Star network(n);
        ostringstream ss;
        ss<<"{'n':"<<n<<"},";

        f<<"[  "<<ss.str()<<endl;
        f<<network<<"] ,"<<endl<<endl;

        cout<<"\r "<<ss.str()<<"   "<<flush;
    }
    f<<"]";
}

