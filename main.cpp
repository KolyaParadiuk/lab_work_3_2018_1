
#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm> 
#include <SFML/Graphics.hpp>
#include"Node.h"
#include"Edge.h"
#include"Triangle.h"
#include <ctime>
#include<set>


using namespace std;

using namespace sf;





bool cw(Node a, Node b, Node c) {
	return a.get_X()*(b.get_Y() - c.get_Y()) + b.get_X()*(c.get_Y() - a.get_Y()) + c.get_X()*(a.get_Y() - b.get_Y()) < 0;
}

bool ccw(Node a, Node b, Node c) {
	return a.get_X()*(b.get_Y() - c.get_Y()) + b.get_X()*(c.get_Y() - a.get_Y()) + c.get_X()*(a.get_Y() - b.get_Y()) > 0;
}

bool cmp_angle(Node  first, Node  second)
{
	return (first.get_angle() < second.get_angle());
}
void print(vector<Edge> convex_hull_edges)
{
	int size_of_hull = convex_hull_edges.size();

	sf::RenderWindow window(sf::VideoMode(1300, 700), "Triangulation!");
	//while (window.isOpen())
	//{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		for (int i = 0; i < size_of_hull; i++)
		{


			Vertex point_to_draw[]
			{
				Vertex(Vector2f(convex_hull_edges[i].get_start_point().get_X(), convex_hull_edges[i].get_start_point().get_Y())),
				Vertex(Vector2f(convex_hull_edges[i].get_finish_point().get_X(), convex_hull_edges[i].get_finish_point().get_Y()))

			};
			window.draw(point_to_draw, 2, sf::Lines);

		}
		window.display();
		system("pause");
	//}
}

void prin_point(Node point)
{

}

template < typename T>
bool is_belong( T& node, vector<T> vec ) 
{

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == node) return true;
	}
	return false;

}

class Grafs
{
public:
	Grafs(vector<Node> &);
	~Grafs();
	void convex_hull();

	
	Node get_centre();
	vector<Edge> get_convex_hull();
	vector<Edge> dalone_triangulation();

	

	




private:
	vector<Node> points;
	vector<Edge> convex_hull_Edges;
	vector<Edge> delone_triangulation_edges;
	Node centre_of_selection;
	vector<Node> convex_hull_points;
	
	void set_polar_angels();
	void find_centre_of_points();
	Node recognise_centre();
	void combine();


	vector<Node> find_second_nodes( Node& ver);//find all nodes conected with ver
	vector<Node> find_third_vertex( Edge edge);//find third vertex too build triangle with edge 
	void add_triangle(Triangle& tr,vector<Triangle> &vector);
	void add_edge(Edge e, vector<Edge>& vec);
	//add triangle to delone_trangles if it is uniq



};

Grafs::Grafs(vector<Node> &arg):points(arg)
{

}

Grafs::~Grafs()
{
}

void Grafs::convex_hull()
{	
	convex_hull_points = points;
	/*find_centre_of_points();
	recognise_centre();*/
	
	if (convex_hull_points.size() == 1)  return;
	sort(convex_hull_points.begin(), convex_hull_points.end());
	Node p1 = convex_hull_points[0], p2 = convex_hull_points.back();
	vector<Node> up, down;
	up.push_back(p1);
	down.push_back(p1);
	for (size_t i = 1; i<convex_hull_points.size(); ++i) {
		if (i == convex_hull_points.size() - 1 || cw(p1, convex_hull_points[i], p2)) {
			while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], convex_hull_points[i]))
				up.pop_back();
			up.push_back(convex_hull_points[i]);
		}
		if (i == convex_hull_points.size() - 1 || ccw(p1, convex_hull_points[i], p2)) {
			while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], convex_hull_points[i]))
				down.pop_back();
			down.push_back(convex_hull_points[i]);
		}
	}
	convex_hull_points.clear();
	for (size_t i = 0; i<up.size(); ++i)
		convex_hull_points.push_back(up[i]);
	for (size_t i = down.size() - 2; i>0; --i)
		convex_hull_points.push_back(down[i]);

	convex_hull_Edges.push_back(Edge(convex_hull_points[0], convex_hull_points[convex_hull_points.size()-1]));
	for (int i = 0; i < convex_hull_points.size()-1; i++)
	{
		convex_hull_Edges.push_back(Edge(convex_hull_points[i], convex_hull_points[i+1]));
	}

}

void Grafs::find_centre_of_points()
{
	size_t size = points.size();
	double coord_X=0;
	double coord_Y=0;

	for (int i = 0; i < size; i++)
	{
		coord_X += points[i].get_X();
		coord_Y += points[i].get_Y();
	}

	coord_X /= size;
	coord_Y /= size;

	Node res(coord_X,coord_Y);

	centre_of_selection = res;

}

Node Grafs::recognise_centre()
{
	find_centre_of_points();
	Edge result(centre_of_selection,points[0]);
	double length=result.lnegth_of_edge();
	for (int i = 1; i < points.size(); i++)
	{
		Edge temp(centre_of_selection,points[i]);
		if (is_belong(points[i-1], convex_hull_points) && !is_belong(points[i], convex_hull_points))
		{
			result = temp;
			length = temp.lnegth_of_edge();
		}
		if (temp.lnegth_of_edge() < length  && !is_belong(points[i], convex_hull_points))
		{
			result = temp;
			length = temp.lnegth_of_edge();
		}


	}
	centre_of_selection = result.get_finish_point();
	return result.get_finish_point();
}

Node Grafs::get_centre()
{
	return centre_of_selection;
}

vector<Edge> Grafs::get_convex_hull()
{
	return convex_hull_Edges;
}

vector<Edge> Grafs::dalone_triangulation()
{

	vector<Triangle> delone_triangles;
	recognise_centre();
	set_polar_angels();

	sort(points.begin(),points.end(), cmp_angle);
	
	if (convex_hull_points.size() != points.size()) 
	{	
		for (int i = 1; i < points.size() - 1; i++)
		{
			add_edge(Edge(points[i], points[i + 1]), delone_triangulation_edges);
			
		}
			add_edge(Edge(points[1], points[points.size() - 1]), delone_triangulation_edges);
			
		
	}
	for (int i = 1; i < points.size(); i++)
		{
		add_edge(Edge(centre_of_selection, points[i]), delone_triangulation_edges);
		}
	

	


	combine();

	

	print(delone_triangulation_edges);
	
	for (int i = 0; i < delone_triangulation_edges.size(); i++)
	{


		if (!is_belong(delone_triangulation_edges[i], convex_hull_Edges))
		{
			vector<Node> vertex = find_third_vertex(delone_triangulation_edges[i]);
			for (int j = 0; j < vertex.size(); j++)
			{
				Triangle temp(delone_triangulation_edges[i].get_finish_point(), delone_triangulation_edges[i].get_start_point(),vertex[j]);
				delone_triangulation_edges[i].set_neighbord(temp);
				add_triangle(temp, delone_triangles);

			}
		}
		

	}
	for (int i = 0; i < delone_triangulation_edges.size(); i++)
	{

		if (is_belong(delone_triangulation_edges[i], convex_hull_Edges))
		{
			vector<Node> vertex = find_third_vertex(delone_triangulation_edges[i]);
			for (int j = 0; j < vertex.size(); j++)
			{
				Triangle temp(delone_triangulation_edges[i].get_finish_point(), delone_triangulation_edges[i].get_start_point(), vertex[j]);
				if (is_belong(temp, delone_triangles))
				{
					delone_triangulation_edges[i].set_neighbord(temp);

				}

			}
		}


	}




	return vector<Edge>();
}

void Grafs::set_polar_angels()
{
	for (int i = 0; i < points.size();i++)
	{
		points[i].FindPolarAngle(centre_of_selection);
	}
}

void Grafs::combine()
{
	bool flag=true;
	for (int i = 0; i < convex_hull_Edges.size(); i++)
	{
		for (int j=0;j<delone_triangulation_edges.size();j++)
		{
			if (convex_hull_Edges[i] == delone_triangulation_edges[j])
			{
				flag = false;
			}
		}
		if (flag)
		{
			delone_triangulation_edges.push_back(convex_hull_Edges[i]);
		}
		else
		{
			flag = true;
		}
	}
}

vector<Node> Grafs::find_second_nodes( Node & ver)
{
	
		vector<Node>temp;

		for (int i = 0; i < delone_triangulation_edges.size(); i++)
		{
			if (ver == delone_triangulation_edges[i].get_finish_point())
			{
				temp.push_back(delone_triangulation_edges[i].get_start_point());
			}
			else
			{
				if(ver == delone_triangulation_edges[i].get_start_point())
					temp.push_back(delone_triangulation_edges[i].get_finish_point());
			}
		}

			return temp;

}

vector<Node> Grafs::find_third_vertex( Edge  edge)
{

	vector<Node> vertex;
	Node temp = edge.get_start_point();
	vector<Node >conected_with_start_point=find_second_nodes(temp);
	temp = edge.get_finish_point();
	vector<Node >conected_with_finish_point = find_second_nodes(temp);
	for (int i = 0; i < conected_with_start_point.size(); i++)
	{
		for (int j = 0; j < conected_with_finish_point.size(); j++)
			{
				if (conected_with_start_point[i] == conected_with_finish_point[j])
				{
					vertex.push_back(conected_with_finish_point[j]);
				}
			}
	}
	



	return vertex;
}

void Grafs::add_triangle(Triangle & tr, vector<Triangle> &vector)
{
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i] == tr) return;
	}
	vector.push_back(tr);

}

void  Grafs::add_edge(Edge e, vector<Edge> &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == e) return;
	}
	vec.push_back(e);
}






void main()
{
	ifstream inp_file("input.txt");
	Node first_coordinate;
	Node second_coordinate;
	const int M1=1;
	const int M2 = 2;
	int N = 6;
	double x;
	double y;
	Vertex line_to_draw[M2];
	vector<Vertex[M2]> lines;
	vector<Node> points;
	vector<Edge> convex_hull_edges;

	srand(time(0));
	for (int i = 0; i < N ; i++)
	{

		//x =50+ rand()%1200;
		//y = 50+ rand() % 600;
		inp_file >> x;
		inp_file >> y;
		Node temp(x,y);
		points.push_back(temp);
	}
	


	Grafs test(points);
	test.convex_hull();

	convex_hull_edges = test.get_convex_hull();
	int size_of_hull = convex_hull_edges.size();

		sf::RenderWindow window(sf::VideoMode(1300, 700), "SFML works!");
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			
			for (int i = 0; i < N; i++)
			{
				first_coordinate = points[i];

				Vertex point_to_draw[]
				{
					Vertex(Vector2f(first_coordinate.get_X(), first_coordinate.get_Y()))
				};
				window.draw(point_to_draw, 1, sf::Points);
			}

		
			/*Node temp = test.get_centre();
			Vertex point_to_draw[]
			{
				Vertex(Vector2f(temp.get_X(), temp.get_Y()))
			};
			window.draw(point_to_draw, 1, sf::Points);
			
*/
			
			for (int i = 0; i < size_of_hull; i++)
			{
		

				Vertex point_to_draw[]
				{
					Vertex(Vector2f(convex_hull_edges[i].get_start_point().get_X(), convex_hull_edges[i].get_start_point().get_Y())),
					Vertex(Vector2f(convex_hull_edges[i].get_finish_point().get_X(), convex_hull_edges[i].get_finish_point().get_Y()))

				};
				window.draw(point_to_draw, 2, sf::Lines);
			
			}

			
			window.display();
			break;
		}

		test.dalone_triangulation();
	

		system("pause");

}