#pragma once

#include"Node.h"
#include<vector>

class Edge;
class Triangle
{
public:
	Triangle();
	Triangle(Node x, Node y, Node z);
	~Triangle();
	bool operator ==(const Triangle&);
	Node get_unique_point(Edge & e);
	Node get_center_of_circle();
	std::vector<Node> vertex;
private:
	Node centre_circumcircule;

};

#include"Edge.h"