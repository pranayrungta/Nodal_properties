#ifndef DSF_CPP
#define DSF_CPP

#include "common_base.cpp"


class DSF : public topology_base
{public:
    ///-------constructor--------------------------
    DSF(const int orderofNetwork, const int dummy=-1):
    	topology_base({})
	{
		order = orderofNetwork;
		int no_of_nodes = pow(3, order);
		nbr = vector<vector<int>>(no_of_nodes);

		allLevel_connections();
	}

	string tag()
	{
		ostringstream ss;
		ss<<"DSF_o="<<order;
		return ss.str();
	}
private:
    int order;

    void node_connection(const int starting_node, const int level, const int level_connection);

    void level_connections(const int level);

    void allLevel_connections()
	{
		for(int level=1; level<=order; level++)
			level_connections(level);
	}
};


int mainDSF()
{
    DSF net(2);
    cout<<DSF(2)<<endl;

    auto dd = getDegreeDistribution(net);
    cout<<"Degree distribution :\n"<<dd<<endl;
	cout<<net.tag();
    return 0;
}






///-------constructor--------------------------
void DSF :: node_connection(const int starting_node, const int level, const int level_connection)
{
    if(level ==1)
    {
        int first_node  = starting_node + level_connection + 1;
        int second_node = starting_node + level_connection + 2;

        nbr[starting_node].push_back(first_node);
        nbr[starting_node].push_back(second_node);
        nbr[first_node].push_back(starting_node);
        nbr[second_node].push_back(starting_node);
    }
    else
    {
        int present_lconnection =0;
        present_lconnection = level_connection + pow(3,level-1);
        node_connection(starting_node, level-1, present_lconnection);

        present_lconnection = level_connection + pow(3,level-1)*2;
        node_connection(starting_node, level-1, present_lconnection);
    }
}

void DSF :: level_connections(const int level)
{
    int node_no_increases = pow(3, level);
    for(int node_no=0; node_no<nbr.size(); node_no+=node_no_increases)
    {
        int level_connection=0;
        node_connection(node_no,level,level_connection);
    }
}


#endif
