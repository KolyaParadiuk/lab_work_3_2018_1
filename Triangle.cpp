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
