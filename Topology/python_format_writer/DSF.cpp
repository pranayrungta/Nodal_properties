#include "./../DSF.cpp"
#include<sstream>
#include<fstream>

int main()
{
    vector<int> orderRange{3,4};

	ofstream f("DSF.txt");
	f<<"[ "<<endl;
    for(auto order : orderRange)
    {
        DSF network(order);
        ostringstream ss;
        //ss<<"'order="<<order<<"' ";
        ss<<"{ 'order':"<<order<<"},";

        f<<"[  "<<ss.str()<<endl;
        f<<network<<","<<endl;
        //f<<"# degree distribution"<<endl;
        //f<<getDegreeDistribution(network);
        f<<"] ,"<<endl<<endl;

        cout<<"\r "<<ss.str()<<"   "<<flush;
    }
    f<<"]";
}
