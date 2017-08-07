#ifndef READ_DATA_CPP
#define READ_DATA_CPP

#include "read_basic.cpp"

struct data_point
{
	string tag;
	vector<vector<int>> nbr;
	multimap<double,int> ndpr;
};

data_point read_data_point(istream& is)
{
	data_point temp;
	char ch;

	is>>ch;
	if(ch!='[')wrong_format("read_data_point [");

	string s;	is>>s;
	if( s[0]!='\'' or s[s.size()-2]!='\'' or s.back()!=',' )
		wrong_format("read_data_point tag,");
	temp.tag = s.substr(1,s.size()-3);

	temp.nbr = read_topology(is);

	is>>ch;
	if(ch!=',')wrong_format("read_data_point topology,");
	is>>temp.ndpr>>ch;

	if(ch!=']')wrong_format("read_data_point ]");
	return temp;
}

vector<data_point> read_data(istream& is)
{
	ignoreComments(is);
	char ch;
	vector<data_point> temp_data;
	is>>ch;
	if(ch!='[')wrong_format("read_data [");
	is>>ch;
	if(ch==']')return temp_data;
	is.unget();

	temp_data.push_back( read_data_point(is) );
	while( is>>ch )
	{
		if(ch!=',')break;
		temp_data.push_back( read_data_point(is) );
	}
	if(ch!=']')wrong_format("read data ]");
	return temp_data;
}

vector<data_point> read_data_from_file(const string& s)
{
	ifstream f(s);
	if(f.good())return read_data(f);
	else
	{
		cout<<"Invalid filename : "<<s<<endl;
		exit(1);
	}
}

ostream& operator<<(ostream& os, const data_point& i)
{
	os<<i.tag<<endl;
	os<<i.nbr<<endl;
	os<<i.ndpr<<endl<<endl;
}

int mainreadData()
{
	string s = "clc_RSFsample.txt";
	vector<data_point> data = read_data_from_file(s);
	for(auto& i : data)
		cout<<i;
}

#endif
