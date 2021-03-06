#pragma once
#include"Node.h"
#include<vector>

class Node;

class Triangle;

class Edge
{
public:
	Edge();

	Edge(Node&, Node&);

	~Edge();

	Node& get_start_point();

	Node& get_finish_point();

	void set_neighbord(Triangle &);

	void remove_neighbord(Triangle &);

	double length_of_edge();

	Edge operator = (const Edge&);

	bool operator == (const Edge&);

	std::vector<Triangle> neigbords;

private:

	Node start_point;

	Node fin_point;

};

#include"Triangle.h"