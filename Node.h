#pragma once
#include <cmath>

class Node
{	
private:
	 double coordinate_x;
	 double coordinate_y;
	 double polar_angle ;
public:
	Node();
	Node(double x, double y);
	Node(const Node& );
	~Node();

	bool operator  <(const Node& b);
	Node& operator =(const Node&);

	bool operator ==(const Node&); 
	bool operator !=(const Node&);
	double get_X();
	double get_Y();
	double get_angle();



	void FindPolarAngle(Node CenterOfMass);

};