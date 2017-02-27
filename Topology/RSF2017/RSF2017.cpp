#include "./../common_base.cpp"
#include<random>
#include<ctime>

class RSF : public topology_base
{public:

    RSF(const int n, const int k);

    /// function of class node to display details
    ostream& display(ostream& os) const ;

    /// function to rewire network
    void recreateNetwork();
private:

    struct cumSize_node_Pair{
        int cum;
        int node;
        cumSize_node_Pair():cum(0), node(0) {}
    };

    vector<bool> selected;
    vector<cumSize_node_Pair> cumSize;
    int activeNodes;
    int cumEnd;
    const int m;



    void makeInitialConfig(const int starting_no);

	void completeNetwork();

	void initializeSelected();

	int search_cumSize_index(const int randint);

	/// index = one be removed from cumSize
	void update_cumSize_from(int index);

	void add_new_node();
};



int main()
{
	for(int i=0; i<1000;i++)
		RSF sf(100,3);

    return 0;
}



///-------------
ostream& RSF::display(ostream& os) const
{
	os<<endl<<"-----Details--------"<< endl;

	os<<endl;
	topology_base::display(os);

	os<<endl<<"NodeNo \t selected "<<endl;
	for(int i=0; i<selected.size(); i++)
		os<< i<< "\t"<< selected[i]<< endl;

	os<<endl<< "cum \t node"<<endl;
	for(auto& i : cumSize)
		os<< i.cum<< "\t"<< i.node<< endl;

	os<<endl<<endl;
	os<< " active nodes = " <<activeNodes<< endl;
	os<< " cumEnd = "   <<cumEnd << endl;
	os<< " prob capacity = "<<selected.capacity()<< endl;
	os<< " cumSize capacity = "<<cumSize.capacity() << endl<<endl;
	return os;
}




RSF::RSF(const int n, const int k):
	topology_base(vector<vector<int>>(n, vector<int>(k))),
	selected(n), cumSize(n), activeNodes(0), cumEnd(0),m(k)
{
	makeInitialConfig(k+1);
	completeNetwork();
}

void RSF::completeNetwork()
{
	while(activeNodes<nbr.size())
		add_new_node();
}

void RSF::recreateNetwork()
{
    int n=nbr.size();

    nbr.clear();
    nbr.resize(n,vector<int>(m));

	selected.resize(n);
    cumSize.resize(n);
    cumEnd = 0;

    makeInitialConfig(m+1);
    completeNetwork();
    cumEnd = 0 ;
}

void RSF::makeInitialConfig(const int starting_no)
{
    activeNodes = starting_no ;
    /// creating clique for active nodes
    int j=0;
    vector<int> links (starting_no-1);
    for(int node_no=0; node_no<starting_no; node_no++)
    {
        for(j=0; j<node_no; j++)
            links[j] = j;
        for(j=node_no; j<starting_no-1 ; j++)
            links[j] = j+1;
        nbr[node_no] = links ;
    }
}


void RSF::initializeSelected()
{
	for(int i=0; i<activeNodes; i++)
		selected[i]=false;
}


int RSF::search_cumSize_index(const int randint)
{
	int l=0, u=cumEnd-1, m=0;
	while(l<u)
	{
		m=(l+u)/2;
		if(randint<=cumSize[m].cum)
			u=m;
		else
			l=m+1;
	}
	return u;
}


///// index = one be removed from cumSize
//void RSF::update_cumSize_from(int index)
//{
//	for(int i= cumSize[index].node+1; i<activeNodes; i++)
//		if(!selected[i])
//		{
//			if(index==0) cumSize[index].cum = nbr[i].size();
//			else cumSize[index].cum = cumSize[index-1].cum +
//									  nbr[i].size();
//			cumSize[index].node=i;
//			index++;
//		}
//	cumEnd = index;
//}

/// index = one be removed from cumSize
void RSF::update_cumSize_from(int)
{
	cumEnd=0;
	int cp=0;
	for(int i=0; i<activeNodes; i++)
		if(!selected[i])
		{
			cp+=nbr[i].size();
			cumSize[cumEnd].cum=cp;
			cumSize[cumEnd].node=i;
			cumEnd++;
		}
}


void RSF::add_new_node()
{
	initializeSelected();

	/// setting variables to calculate from update cumulative inside loop
	cumSize[0].node=-1;
	int cumSize_search_index=0;

	for(int k=0; k<m; k++)
	{
		update_cumSize_from(cumSize_search_index);

		uniform_int_distribution<int> dist(1,cumSize[cumEnd-1].cum);
		int randint = dist(generator);
		cumSize_search_index = search_cumSize_index(randint);

		int selected_node = cumSize[cumSize_search_index].node;
		selected[selected_node]=true;

		nbr[activeNodes][k] = selected_node;
		nbr[selected_node].push_back(activeNodes);
	}
	activeNodes++;
}
