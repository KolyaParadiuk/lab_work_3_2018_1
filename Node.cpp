#include "Node.h"
#include"Edge.h"

#define _USE_MATH_DEFINES
#include <math.h>

bool Node::operator <(const Node& b) {
	return this->coordinate_x < b.coordinate_x || this->coordinate_x == b.coordinate_x && this->coordinate_x < b.coordinate_y ;
}

Node & Node::operator=(const Node & that)
{
	this->coordinate_x = that.coordinate_x;
	this->coordinate_y = that.coordinate_y;
	this->polar_angle = that.polar_angle;

	return *this;
}

bool Node::operator==(const Node &that)
{
	return(this->coordinate_x == that.coordinate_x && this->coordinate_y == that.coordinate_y);
}

bool Node::operator!=(const Node &that)
{
	return(this->coordinate_x != that.coordinate_x || this->coordinate_y != that.coordinate_y);
}

double Node::get_X()
{
	return coordinate_x;
}

double Node::get_Y()
{
	return coordinate_y;
}

double Node::get_angle()
{
	return polar_angle;
}






Node::Node() : coordinate_x(0.0), coordinate_y(0.0) ,polar_angle(0.0)
{}

Node::Node(double x, double y) : coordinate_x(x), coordinate_y(y),polar_angle(0)
{}

Node::Node(const Node &that):coordinate_x(that.coordinate_x),coordinate_y(that.coordinate_y),polar_angle(that.polar_angle)
{}



Node::~Node()
{

}

void Node::FindPolarAngle(Node CenterOfMass)
{
	Edge Edge(CenterOfMass,*this);
	if (Edge.lnegth_of_edge() == 0) polar_angle = 0;
	else
		if (this->coordinate_x > CenterOfMass.get_X() && this->coordinate_y >= CenterOfMass.get_Y())
			polar_angle = atan((this->coordinate_y - CenterOfMass.get_Y()) / (this->coordinate_x - CenterOfMass.get_X()));
		else
			if (this->coordinate_x > CenterOfMass.get_X() && this->coordinate_y < CenterOfMass.get_Y())
				polar_angle = atan((this->coordinate_y - CenterOfMass.get_Y()) / (this->coordinate_x - CenterOfMass.get_X())) + 2 * M_PI;
			else
				if (this->coordinate_x < CenterOfMass.get_X())
					polar_angle = atan((this->coordinate_y - CenterOfMass.get_Y()) / (this->coordinate_x - CenterOfMass.get_X())) + M_PI;
				else
					if (this->coordinate_x == CenterOfMass.get_X() && this->coordinate_y > CenterOfMass.get_Y())
						polar_angle = M_PI / 2;
					else
						if (this->coordinate_x == CenterOfMass.get_X() && this->coordinate_y < CenterOfMass.get_Y())
							polar_angle = 3*M_PI / 2;

				
}  
