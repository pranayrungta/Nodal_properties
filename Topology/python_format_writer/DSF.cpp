#include "./../DSF.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> orderRange{2,3};

	ofstream f("DSF.txt");
	f<<"[ "<<endl<<endl;
    for(auto order : orderRange)
    {
        DSF network(order);
        f<<"[  '"<<network.tag()<<"',"<<endl;
        f<<network<<"] ,"<<endl<<endl;

        cout<<network.tag()<<endl;
    }
    f<<"]";
}
