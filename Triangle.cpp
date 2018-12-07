#include "Triangle.h"

Triangle::Triangle()
{

}

Triangle::Triangle(Node x, Node y, Node z) 
{

	vertex.push_back(x);
	vertex.push_back(y);
	vertex.push_back(z);
}

Triangle::~Triangle()
{
}

bool Triangle::operator==(const Triangle &that)
{
	bool flag;

	for (int i = 0; i < 3; i++)
	{
		flag = false;
		for (int j = 0; j < 3; j++)
		{
			if (this->vertex[i] == that.vertex[j])
				flag=true;
		}
		if (!flag)return false;

		
	}
	return true;
}

Node Triangle::get_unique_point(Edge& e)
{
	for (int i = 0; i < 3; i++)
	{
		if (vertex[i] == e.get_start_point() || vertex[i] == e.get_finish_point())
		{
			i++;
		}
		else
		{
			return vertex[i];
		}
	}
}

Node Triangle::get_center_of_circle()
{
	double d = 2 * (vertex[0].get_X() * (vertex[1].get_Y() - vertex[2].get_Y() + vertex[1].get_X()) + vertex[1].get_X() * (vertex[2].get_Y() - vertex[0].get_Y()) + vertex[2].get_X()*(vertex[0].get_Y() - vertex[1].get_Y()));

	double x = ((vertex[0].get_X() * vertex[0].get_X() + vertex[0].get_Y() * vertex[0].get_Y())*(vertex[1].get_Y() - vertex[2].get_Y()) + (vertex[1].get_X() * vertex[1].get_X() + vertex[1].get_Y() * vertex[1].get_Y())*(vertex[2].get_Y() - vertex[0].get_Y()) + (vertex[2].get_X() * vertex[2].get_X() + vertex[2].get_Y() * vertex[2].get_Y()) * (vertex[0].get_Y() - vertex[1].get_Y())) / d;

	double y = ((vertex[0].get_X() * vertex[0].get_X() + vertex[0].get_Y() * vertex[0].get_Y())*(vertex[2].get_X() - vertex[1].get_X()) + (vertex[1].get_X() * vertex[1].get_X() + vertex[1].get_Y() * vertex[1].get_Y())*(vertex[0].get_X() - vertex[2].get_X()) + (vertex[2].get_X() * vertex[2].get_X() + vertex[2].get_Y() * vertex[2].get_Y()) * (vertex[1].get_X() - vertex[0].get_X())) / d;;

	Node temp(x, y);

	return temp;
}