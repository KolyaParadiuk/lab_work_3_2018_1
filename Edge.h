#pragma once
#include"Node.h"
#include<vector>

class Node;
class Triangle;
class Edge
{
public:
	Edge();
	Edge( Node&, Node&);
	~Edge();

	Node get_start_point();
	Node get_finish_point();


	double lnegth_of_edge();
	Edge operator = (const Edge& );
	bool operator == (const Edge&);


private:
	std::vector<Triangle> neigbords;
	Node start_point;
	Node fin_point;

};

#include"Triangle.h"
