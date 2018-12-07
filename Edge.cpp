#include"Edge.h"
#include <cmath>


Edge::Edge()
{
}

Edge::Edge( Node & start,  Node &finish)
{
	this->start_point = start;
	fin_point = finish;

}


Edge::~Edge()
{


}

Node& Edge::get_start_point()
{
	return start_point;
}

Node& Edge::get_finish_point()
{
	return fin_point;
}

void Edge::set_neighbord(Triangle & that)
{

	for (int i = 0; i < neigbords.size(); i++)
		if (neigbords[i] == that) return;
		
	neigbords.push_back(that);		
		
}

double Edge::lnegth_of_edge()
{
	return (sqrt(pow((fin_point.get_X()-start_point.get_X()),2)+ pow((fin_point.get_Y() - start_point.get_Y()), 2)));
}

Edge Edge::operator=(const Edge &that)
{
	this->start_point = that.start_point;
	this->fin_point = that.fin_point;

	this->neigbords.clear();
	for (int i = 0; i < that.neigbords.size(); i++)
	{
		neigbords.push_back(that.neigbords[i]);
	}
	return *this;
}

bool Edge::operator==(const Edge &that)
{
	return ((this->start_point==that.start_point && this->fin_point == that.fin_point) || (this->start_point == that.fin_point && this->fin_point == that.start_point));
}
