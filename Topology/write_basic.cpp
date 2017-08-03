#ifndef WRITE_BASIC_CPP
#define WRITE_BASIC_CPP

#include<iostream>
#include<map>
#include<vector>
using namespace std;

template<typename T1, typename T2>
ostream& write_map(ostream& os, const map<T1,T2>& var,
				   const string start="{\n",
				   const string ending = "\n}",
				   const string key_val_sep = " : ",
				   const string elem_sep = ",\n"
				  )
{
	os<<start;
    if(var.size()>0)
    {
    	auto i = var.begin();
        os<<(*i).first<<key_val_sep<<(*i).second;
        for(i++; i!=var.end(); i++)
			os<<elem_sep<<(*i).first<<key_val_sep<<(*i).second;
    }
	return os<<ending;
}

template<typename t1,typename t2>
ostream& operator<<(ostream& os, const map<t1,t2>& x)
{	return write_map(os,x,"","","\t","\n");	}


template<typename T>
ostream& write_vector(ostream& os, const vector<T>& var,
					   const string start="[ ",
					   const string ending = " ]",
					   const string elem_sep = ", "
					 )
{
    os<<start;
    if(var.size()>0)
    {
        os<< var[0];
        for(int i=1; i<var.size(); i++)
            os<<elem_sep<<var[i];
    }
    os<<ending;
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& var)
{	return write_vector(os,var);	}




int mainWrite()
{
	vector<int> x{52,6,5,7,8,4,2,5,9};
	x[3]=45;
	x[4]=15;
	x[2]=5;

//	cout<<x<<endl;
	write_vector(cout,x);
}


#endif
