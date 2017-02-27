#ifndef READ_BASIC_CPP
#define READ_BASIC_CPP


#include "./../Topology/common_base.cpp"
#include<cstdlib>
#include<fstream>

void wrong_format(const string i="-1");


void ignoreComments(istream& is);
istream& operator>>(istream& is,vector<int>& temp);
istream& operator>>(istream& is, map<string,int>& temp);
vector<vector<int>> read_topology(istream& is);
istream& operator>>(istream& is, multimap<double,int>& temp);


ostream& operator<<(ostream& os, multimap<double,int>& temp)
{
	for (auto& i : temp)
		os<<i.first<<" : "<<i.second<<endl;
	return os;
}




int mainReadbasic()
{
	ifstream f("try.txt");

	char ch;
	map<string,int> args;
	vector<vector<int>> network;
	multimap<double,int> btc;

	f>>args;
	network = read_topology(f);
	f>>btc;

	cout<<args<<endl;
	cout<<network<<endl;
	cout<<btc<<endl;
}







///-----implementation of functions---------
void ignoreComments(istream& is)
{
	char ch;
	string s;
	is>>ch;
	while(ch=='#')
	{
		getline(is,s);
		is>>ch;
	}
	is.unget();
}

void wrong_format(const string i)
{
	cout<<"wrong format at "<<i<<endl;
	exit(1);
}

istream& operator>>(istream& is,vector<int>& temp)
{
	char ch; int n;
	is>>ch;
	if(ch!='[')wrong_format("vector<int> a");
	temp.resize(0);
	is>>ch;
	if(ch==']')return is;
	is.unget();

	is>>n;
	while( is>>ch )
	{
		temp.push_back(n);
		if(ch!=',')break;

		is>>n;
	}
	if(ch!=']')wrong_format("vector<int> b");
	return is;
}

istream& operator>>(istream& is, map<string,int>& temp)
{
	char ch; string s; int n;
	is>>ch;
	if(ch!='{')wrong_format("multimap<string,int> a");
	temp.clear();
	is>>ch;
	if(ch=='}')return is;
	is.unget();

	is>>s>>n;
	s = s.substr(1,s.size()-3);
	while( is>>ch )
	{
		temp[s] = n;
		if(ch!=',')break;

		is>>s>>n;
		s = s.substr(1,s.size()-3);
	}
	if(ch!='}')wrong_format("multimap<string,int> b");
	return is;
}

vector<vector<int>> read_topology(istream& is)
{
	vector<vector<int>> network;
	char ch; vector<int> nbr; int n;

	is>>ch;
	if(ch!='{')wrong_format("read_topology a");
	ignoreComments(is);
	is>>ch;
	if(ch=='}')return network;
	is.unget();

	is>>n>>ch>>nbr;
	if(ch!=':')wrong_format("read_topology b");
	while( is>>ch )
	{
		while( n+1>network.size() )network.push_back(vector<int>{});
		network[n] = nbr;
		if(ch!=',')break;

		is>>n>>ch>>nbr;
		if(ch!=':')wrong_format("read_topology c");
	}
	if(ch!='}')wrong_format("read_topology d");
	return network;
}

istream& operator>>(istream& is, multimap<double,int>& temp)
{
	char ch; int n; double x;
	is>>ch;
	if(ch!='{')wrong_format("multimap<double,int> a");
	temp.clear();
	is>>ch;
	if(ch=='}')return is;
	is.unget();

	is>>n>>ch>>x;
	while( is>>ch )
	{
		temp.insert( pair<double,int>(x,n) );
		if(ch!=',')break;

		is>>n>>ch>>x;
	}
	if(ch!='}')wrong_format("multimap<double,int> b");
	return is;
}

#endif
