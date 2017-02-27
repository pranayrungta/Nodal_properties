#include "./../common_base.cpp"
#include<random>
#include<ctime>

class RSF : public topology_base
{public:

    RSF(const int n, const int k);

    /// function to rewire network
    void recreateNetwork();

private:
    struct probPair{
        double p;
        bool selected;
        probPair():p(0), selected(0) {}
    };

    struct cumProbPair{
        double p;
        int  node;
        cumProbPair():p(0), node(0) {}
    };

    vector<probPair> prob;
    vector<cumProbPair> cumProb;
    int activeNodes;
    int cumProbEnd;

    void makeInitialConfig(const int starting_no);

    void calculateProbability();
    void calculateCumulativeProbability();
    int  searchNode(const double randprob);

    void addNewNode();

    void updateProbaility(const double scaling)
    {
		for(int i=0 ; i<activeNodes; i++)
			prob[i].p /=scaling;
	}

    void completeNetwork()
    {
		for(int i=activeNodes; i<nbr.size(); i++)
			addNewNode();
	}
};


int main()
{
	for(int i=0; i<1000;i++)
		RSF sf(100,3);
    //cout<<sf;

//    auto dd = getDegreeDistribution(sf);
//
//    cout<<sf<<"\nDegree distribution :\n"<<dd<<endl<<endl;
    return 0;
}






//    /// function of class node to display details
//    ostream& display(ostream& os) const ;
//---display content of all member variables--
//ostream& RSF::display(ostream& os) const
//{
//    os<<endl<<"-----Details--------"<< endl;
//
//    os<<endl;
//    topology_base::display(os);
//
//    os<<endl<<"Node \t Prob \t flag "<<endl;
//    for(int i=0; i<prob.size(); i++)
//        os<< i<< "\t"<< prob[i].p  << "\t"<< prob[i].selected<< endl;
//
//    os<<endl<< "cumProb \t node"<<endl;
//    for(auto i : cumProb)
//        os<< i.p  << "\t"<< i.node<< endl;
//
//	os<<endl<<endl;
//    os<< " active nodes = " <<activeNodes<< endl;
//    os<< " cumProbEnd = "   <<cumProbEnd << endl;
//    os<< " prob capacity = "<<prob.capacity()<< endl;
//    os<< " cumProb capacity = "<<cumProb.capacity() << endl<<endl;
//    return os;
//}


///------- implementation of class functions----------
//----constructor-------
RSF::RSF(const int n, const int k):
	topology_base(vector<vector<int>>(n, vector<int>(k))),
    prob(n), cumProb(n), activeNodes(0), cumProbEnd(0)
{
    makeInitialConfig(k+1);
    completeNetwork();

    vector<probPair>().swap(prob);
    vector<cumProbPair>().swap(cumProb);

    cumProbEnd = 0;
}

void RSF::recreateNetwork()
{
    int n=nbr.size();
    int k=nbr[nbr.size()-1].size();

    nbr.resize(0);
    nbr.resize(n,vector<int>(k));

    prob.resize(n);
    cumProb.resize(n);

    activeNodes = 0;
    cumProbEnd = 0;

    makeInitialConfig(k+1);
    completeNetwork();
    prob.resize(0);
    cumProb.resize(0);
    cumProbEnd = 0 ;
}

//----initialize as a ring-------
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


//-----calculate probability from nbr vector-----
void RSF::calculateProbability()
{
    double sum = 0;
    for(int i=0; i<activeNodes; i++)
        sum += nbr[i].size();

    for(int i=0; i<activeNodes; i++)
    {
        prob[i].p = nbr[i].size()/sum;
        prob[i].selected = false;
    }
}

//----cumulative probability from all 0 flag prob vector-----
void RSF::calculateCumulativeProbability()
{
    cumProbEnd = 0;
    double cp= 0;
    for( int i=0; i<activeNodes; i++)
        if(!prob[i].selected)
        {
            cp+=prob[i].p;
            cumProb[cumProbEnd].p = cp ;
            cumProb[cumProbEnd].node = i;
            cumProbEnd++;
        }
}

//search node in cumProb for a given probability
int RSF::searchNode(const double randprob)
{
    int l=0, u=cumProbEnd-1, m=0;
    while(l<u)
    {
        m=(l+u)/2;
        if(randprob<=cumProb[m].p)
            u=m;
        else
            l=m+1;
    }
    return cumProb[u].node;
}

//**** main function - adds a new node to the system ****
void RSF::addNewNode()
{
    int selectedNode = 0;
    double r=0 , newprob=0;
	uniform_real_distribution<double>  random_probability(0, 1);

    for(int k=0; k<nbr[activeNodes].size(); k++)
    {
        if(k==0)
            calculateProbability();
        else
        {
            prob[selectedNode].selected = true;
            newprob = 1-prob[selectedNode].p;
            updateProbaility(newprob);
        }

        calculateCumulativeProbability();
        r = random_probability(generator);
        selectedNode = searchNode(r);

        nbr[activeNodes][k] = selectedNode;
        nbr[selectedNode].push_back(activeNodes);
    }
    activeNodes++;
}
