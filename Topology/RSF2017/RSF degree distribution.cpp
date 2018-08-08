#include "RSF2017.cpp"
#include<map>
#include<fstream>
#include<sstream>


int main()
{
    vector<int> nRange {1000} ;
    vector<int> kRange {1, 2} ;

    int repetitions = 100 ;



    cout<< "Total iterations : "
        <<nRange.size()*kRange.size()*repetitions
        <<endl<<endl;

    int progress = 0 ;
    for(int n : nRange)
    for(int k : kRange)
    {
        RSF links(n,k);
        map<int,int> avgFreq;

        for(int i=0; i<repetitions; i++)
        {
            links.recreateNetwork();
            ///---calculating degree distribution----
            map<int,int> degree;
            for(int i=0; i<links.size(); i++ )
                degree[links[i].size()]++;
            ///--------------------------------------

            for(auto& i : degree)
                avgFreq[i.first]+= i.second;

            progress++;
        }

        ///---calculating sum---------
        int sum=0;
        for(auto& i : avgFreq)
            sum += i.second;
        ///---------------------------

        ///-------writing to file--------
        ostringstream s;
        s<<"avgFreq"<<"_n="<<n<<"_k="<<k;
        ofstream f( s.str()+".txt" );
        f<< "# "<<s.str()<<endl;
        f<< "# repetitions = "<<repetitions<<endl;
        f<< "#"<<endl;
        f<< "#degree"<<"\t"<<"frequencyProbability"<<endl;
        for(auto& i:avgFreq)
            f<< i.first<<"\t"<<(i.second/(1.0*sum))<<endl;
        f.close() ;
        ///---------------------------
        cout<<"\r"<<"Progress ="<<progress<<"     "<<flush;
    }
    return 0;
}
