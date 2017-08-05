#include "./../Star.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> nRange{10,8};

	ofstream f("Star.txt");
	f<<"[ "<<endl<<endl;
    for(auto n : nRange)
    {
        Star network(n);
        f<<"[  '"<<network.tag()<<"',"<<endl;
        f<<network<<"] ,"<<endl<<endl;

        cout<<network.tag()<<endl;
    }
    f<<"]";
}

