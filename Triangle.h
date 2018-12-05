#pragma once

#include"Node.h"
#include<vector>

class Edge;
class Triangle
{
public:
	Triangle();
	~Triangle();
	//bool operator ==(const Edge&);
private:
	std::vector<Edge> edges;
	Node centre_circumcircule;

};

#include"Edge.h"