#define _USE_MATH_DEFINES
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
#include<cmath>
#include "Menu.h"
using namespace std;

using namespace sf;

bool clockwise(Node a, Node b, Node c) {
	return a.get_X()*(b.get_Y() - c.get_Y()) + b.get_X()*(c.get_Y() - a.get_Y()) + c.get_X()*(a.get_Y() - b.get_Y()) < 0;
}

bool counter_clockwise(Node a, Node b, Node c) {
	return a.get_X()*(b.get_Y() - c.get_Y()) + b.get_X()*(c.get_Y() - a.get_Y()) + c.get_X()*(a.get_Y() - b.get_Y()) > 0;
}

bool compare_angles(Node  first, Node  second)
{
	return (first.get_angle() < second.get_angle());
}

bool point_belongs_to_triangle(Triangle current_triangle, Node current_point)
{
	double a, b, c;

	a = (current_triangle.vertex[0].get_X() - current_point.get_X()) * (current_triangle.vertex[1].get_Y() - current_triangle.vertex[0].get_Y()) - (current_triangle.vertex[1].get_X() - current_triangle.vertex[0].get_X()) * (current_triangle.vertex[0].get_Y() - current_point.get_Y());

	b = (current_triangle.vertex[1].get_X() - current_point.get_X()) * (current_triangle.vertex[2].get_Y() - current_triangle.vertex[1].get_Y()) - (current_triangle.vertex[2].get_X() - current_triangle.vertex[1].get_X()) * (current_triangle.vertex[1].get_Y() - current_point.get_Y());

	c = (current_triangle.vertex[2].get_X() - current_point.get_X()) * (current_triangle.vertex[0].get_Y() - current_triangle.vertex[2].get_Y()) - (current_triangle.vertex[0].get_X() - current_triangle.vertex[2].get_X()) * (current_triangle.vertex[2].get_Y() - current_point.get_Y());

	if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
	{
		return true;
	}

	return false;
}

bool is_triangle(Triangle& tr)
{
	double ab = Edge(tr.vertex[0], tr.vertex[1]).length_of_edge();

	double bc = Edge(tr.vertex[1], tr.vertex[2]).length_of_edge();

	double ca = Edge(tr.vertex[2], tr.vertex[0]).length_of_edge();

	if (ab + bc == ca)
	{
		return false;
	}
	if (ca + bc == ab)
	{
		return false;
	}
	if (ab + ca == bc)
	{
		return false;
	}

	return true;
}

void print(vector<Edge> convex_hull_edges)
{
	int size_of_hull = convex_hull_edges.size();

	sf::RenderWindow window(sf::VideoMode(1300, 700), "Triangulation!");

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
}

template < typename T>
bool is_belong(T& node, vector<T> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == node)
		{
			return true;
		}
	}

	return false;
}

template < typename T>
int find(T& node, vector<T> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == node)
		{
			return i;
		}
	}

	return -1;
}

bool delaunay_condition(Edge& connected_edge)
{
	Node first_node = connected_edge.neigbords[0].get_unique_point(connected_edge);

	Node second_node = connected_edge.neigbords[1].get_unique_point(connected_edge);

	double cosA;

	double sinA;

	double cosB;

	double sinB;

	double alpha1;

	double alpha2;

	double beta1;

	double beta2;

	Edge a(first_node, connected_edge.get_start_point());

	Edge b(first_node, connected_edge.get_finish_point());


	cosA = ((a.get_start_point().get_X() - a.get_finish_point().get_X()) * (b.get_start_point().get_X() - b.get_finish_point().get_X()) + (a.get_start_point().get_Y() - a.get_finish_point().get_Y())*(b.get_start_point().get_Y() - b.get_finish_point().get_Y())) / (a.length_of_edge() * b.length_of_edge());

	alpha1 = acos(cosA);

	sinA = ((a.get_start_point().get_X() - a.get_finish_point().get_X()) * (b.get_start_point().get_Y() - b.get_finish_point().get_Y()) + (a.get_start_point().get_X() - a.get_finish_point().get_X())*(b.get_start_point().get_Y() - b.get_finish_point().get_Y())) / (a.length_of_edge() * b.length_of_edge());

	alpha2 = asin(sinA);

	Edge A(second_node, connected_edge.get_start_point());

	Edge B(second_node, connected_edge.get_finish_point());

	cosB = ((A.get_start_point().get_X() - A.get_finish_point().get_X()) * (B.get_start_point().get_X() - B.get_finish_point().get_X()) + (A.get_start_point().get_Y() - A.get_finish_point().get_Y())*(B.get_start_point().get_Y() - B.get_finish_point().get_Y())) / (A.length_of_edge() * B.length_of_edge());

	beta1 = acos(cosB);

	sinB = ((A.get_start_point().get_X() - A.get_finish_point().get_X()) * (B.get_start_point().get_Y() - B.get_finish_point().get_Y()) + (A.get_start_point().get_X() - A.get_finish_point().get_X())*(B.get_start_point().get_Y() - B.get_finish_point().get_Y())) / (A.length_of_edge() * B.length_of_edge());

	beta2 = asin(sinB);

	if (alpha1 + beta1 <= M_PI)
	{
		return true;
	}

	return false;
}

void rebuild_triangle(Edge& connected_edge, vector<Triangle>& triagles, vector<Edge>& edges)
{
	int index_of_first = -1, index_of_second = -1;

	index_of_first = find(connected_edge.neigbords[0], triagles);

	index_of_second = find(connected_edge.neigbords[1], triagles);

	int edge_index = find(connected_edge, edges);

	Node first(connected_edge.neigbords[0].get_unique_point(connected_edge));

	Node second(connected_edge.neigbords[1].get_unique_point(connected_edge));

	Edge unique_edge(first, second);

	Edge a(first, connected_edge.get_start_point());

	int a_ind = find(a, edges);

	edges[a_ind].remove_neighbord(triagles[index_of_first]);

	Edge b(first, connected_edge.get_finish_point());

	int b_ind = find(b, edges);

	edges[b_ind].remove_neighbord(triagles[index_of_first]);

	Edge c(second, connected_edge.get_start_point());

	int c_ind = find(c, edges);

	edges[c_ind].remove_neighbord(triagles[index_of_second]);

	Edge d(second, connected_edge.get_finish_point());

	int d_ind = find(d, edges);

	edges[d_ind].remove_neighbord(triagles[index_of_second]);

	vector<Edge> triangle_edges;

	Triangle first_triangle(unique_edge.get_start_point(), connected_edge.get_start_point(), unique_edge.get_finish_point());

	triangle_edges.push_back(Edge(first_triangle.vertex[0], first_triangle.vertex[1]));

	triangle_edges.push_back(Edge(first_triangle.vertex[1], first_triangle.vertex[2]));

	triangle_edges.push_back(Edge(first_triangle.vertex[2], first_triangle.vertex[0]));

	if (is_belong(a, triangle_edges))
	{
		edges[a_ind].set_neighbord(first_triangle);
	}

	if (is_belong(b, triangle_edges))
	{
		edges[b_ind].set_neighbord(first_triangle);
	}

	if (is_belong(c, triangle_edges))
	{
		edges[c_ind].set_neighbord(first_triangle);
	}

	if (is_belong(d, triangle_edges))
	{
		edges[d_ind].set_neighbord(first_triangle);
	}




	Triangle second_triangle(unique_edge.get_start_point(), connected_edge.get_finish_point(), unique_edge.get_finish_point());
	triangle_edges.clear();
	triangle_edges.push_back(Edge(second_triangle.vertex[0], second_triangle.vertex[1]));
	triangle_edges.push_back(Edge(second_triangle.vertex[1], second_triangle.vertex[2]));
	triangle_edges.push_back(Edge(second_triangle.vertex[2], second_triangle.vertex[0]));

	if (is_belong(a, triangle_edges))
		edges[a_ind].set_neighbord(second_triangle);
	if (is_belong(b, triangle_edges))
		edges[b_ind].set_neighbord(second_triangle);
	if (is_belong(c, triangle_edges))
		edges[c_ind].set_neighbord(second_triangle);
	if (is_belong(d, triangle_edges))
		edges[d_ind].set_neighbord(second_triangle);


	unique_edge.set_neighbord(first_triangle);
	unique_edge.set_neighbord(second_triangle);

	edges[edge_index] = unique_edge;
	triagles[index_of_first] = first_triangle;
	triagles[index_of_second] = second_triangle;
}

class Grafs
{
public:

	Grafs(vector<Node> &);

	~Grafs();

	void convex_hull();

	vector<Node> rand_unique_points(int number_of_dots);

	vector<Node> read_from_file_points(string& file_name);

	vector<Edge> get_convex_hull();

	vector<Edge> delaunay_triangulation();

	void print_delaunay_triangulation();

	void print_convex_hull();

	vector<Edge> get_delaunay_triangulation_edges();

	void voronoi_diagram();

	vector<Edge> get_voronoi_edges();

	//void print_voronoi_diagram();

private:

	vector<Node> points;

	vector<Node> convex_hull_points;

	vector<Edge> convex_hull_Edges;

	vector<Triangle> delaunay_triangles;

	vector<Edge> delaunay_triangulation_edges;

	vector<Edge> voronoi_diagram_edges;

	void set_polar_angels(vector<Node>&);

	void combine();

	vector<Node> find_second_nodes(Node& ver);//find all nodes conected with ver

	vector<Node> find_third_vertex(Edge edge);//find third vertex too build triangle with edge 

	void add_triangle(Triangle& tr, vector<Triangle> &vector);

	void add_edge(Edge e, vector<Edge>& vec);
};

void Grafs::voronoi_diagram()
{
	for (int i = 0; i < delaunay_triangulation_edges.size(); i++)
	{
		if (!is_belong(delaunay_triangulation_edges[i], convex_hull_Edges))
		{
			Node start(delaunay_triangulation_edges[i].neigbords[0].get_center_of_circle()), finish(delaunay_triangulation_edges[i].neigbords[1].get_center_of_circle());

			voronoi_diagram_edges.push_back(Edge(start, finish));
		}
	}
}

vector<Edge> Grafs::get_voronoi_edges()
{
	return voronoi_diagram_edges;
}

Grafs::Grafs(vector<Node> &arg) :points(arg)
{

}

Grafs::~Grafs()
{
}

void Grafs::convex_hull()
{
	convex_hull_points = points;

	if (convex_hull_points.size() == 1)
	{
		return;
	}

	sort(convex_hull_points.begin(), convex_hull_points.end());

	Node p1 = convex_hull_points[0], p2 = convex_hull_points.back();

	vector<Node> up, down;

	up.push_back(p1);

	down.push_back(p1);

	for (size_t i = 1; i < convex_hull_points.size(); ++i)
	{
		if (i == convex_hull_points.size() - 1 || clockwise(p1, convex_hull_points[i], p2))
		{
			while (up.size() >= 2 && !clockwise(up[up.size() - 2], up[up.size() - 1], convex_hull_points[i]))
			{
				up.pop_back();
			}

			up.push_back(convex_hull_points[i]);
		}

		if (i == convex_hull_points.size() - 1 || counter_clockwise(p1, convex_hull_points[i], p2))
		{
			while (down.size() >= 2 && !counter_clockwise(down[down.size() - 2], down[down.size() - 1], convex_hull_points[i]))
			{
				down.pop_back();
			}

			down.push_back(convex_hull_points[i]);
		}
	}
	convex_hull_points.clear();

	for (size_t i = 0; i < up.size(); ++i)
	{
		convex_hull_points.push_back(up[i]);
	}

	for (size_t i = down.size() - 2; i > 0; --i)
	{
		convex_hull_points.push_back(down[i]);
	}

	convex_hull_Edges.push_back(Edge(convex_hull_points[0], convex_hull_points[convex_hull_points.size() - 1]));

	for (int i = 0; i < convex_hull_points.size() - 1; i++)
	{
		convex_hull_Edges.push_back(Edge(convex_hull_points[i], convex_hull_points[i + 1]));
	}
}

vector<Edge> Grafs::get_convex_hull()
{
	return convex_hull_Edges;
}

vector<Edge> Grafs::delaunay_triangulation()
{
	set_polar_angels(convex_hull_points);

	sort(convex_hull_points.begin(), convex_hull_points.end(), compare_angles);

	for (int i = 1; i < convex_hull_points.size(); i++)
	{

		if (i < convex_hull_points.size() - 1)
		{
			Triangle temp(convex_hull_points[0], convex_hull_points[i], convex_hull_points[i + 1]);

			add_triangle(temp, delaunay_triangles);
		}

		add_edge(Edge(convex_hull_points[0], convex_hull_points[i]), delaunay_triangulation_edges);
	}

	combine();

	//print(delaunay_triangulation_edges);

	for (int i = 0; i < points.size(); i++)
	{
		for (int j = 0; j < convex_hull_points.size(); j++)
		{
			if (points[i] == convex_hull_points[j])
			{
				points.erase(points.begin() + i);

				j = convex_hull_points.size();

				i--;
			}
		}
	}

	for (size_t i = 0; i < points.size(); i++)
	{
		int size_ = delaunay_triangles.size();

		for (int j = 0; j < size_; j++)
		{
			if (point_belongs_to_triangle(delaunay_triangles[j], points[i]))
			{
				for (int k = 0; k < delaunay_triangles[j].vertex.size(); k++)
				{
					Edge E(points[i], delaunay_triangles[j].vertex[k]);

					if (find(E, delaunay_triangulation_edges) == -1)
					{
						add_edge(E, delaunay_triangulation_edges);
					}

					Node C;

					if (k == delaunay_triangles[j].vertex.size() - 1)
					{
						C = delaunay_triangles[j].vertex[0];
					}
					else
					{
						C = delaunay_triangles[j].vertex[k + 1];
					}

					Triangle temp(points[i], delaunay_triangles[j].vertex[k], C);

					if (is_triangle(temp))
					{
						add_triangle(temp, delaunay_triangles);
					}
					else
					{
						Edge tempwq(delaunay_triangles[j].vertex[k], C);
						if (find(tempwq, delaunay_triangulation_edges) != -1)
						{
							delaunay_triangulation_edges.erase(delaunay_triangulation_edges.begin() + find(tempwq, delaunay_triangulation_edges));
						}
					}
				}

				delaunay_triangles.erase(delaunay_triangles.begin() + j);

				j--;

				size_--;
			}
		}
	}

	for (int i = 0; i < delaunay_triangulation_edges.size(); i++)
	{
		vector<Node>temp = find_third_vertex(delaunay_triangulation_edges[i]);

		for (int j = 0; j < temp.size(); j++)
		{
			Triangle T(temp[j], delaunay_triangulation_edges[i].get_start_point(), delaunay_triangulation_edges[i].get_finish_point());

			if (is_belong(T, delaunay_triangles))
			{
				delaunay_triangulation_edges[i].set_neighbord(T);
			}
		}
	}

	//print(delone_triangulation_edges);

	for (int i = 0; i < delaunay_triangulation_edges.size(); i++)
	{
		if (delaunay_triangulation_edges[i].neigbords.size() == 2)
		{
			if (!delaunay_condition(delaunay_triangulation_edges[i]))
			{
				rebuild_triangle(delaunay_triangulation_edges[i], delaunay_triangles, delaunay_triangulation_edges);

				i = -1;

				//print(delone_triangulation_edges);
			}
		}
	}

	//print(delaunay_triangulation_edges);

	return delaunay_triangulation_edges;
}

void Grafs::print_delaunay_triangulation()
{
	print(delaunay_triangulation_edges);
}

void Grafs::print_convex_hull()
{
	print(convex_hull_Edges);
}

void Grafs::set_polar_angels(vector<Node>& _points)
{
	int res = 0;

	for (int j = 1; j < _points.size(); j++)
	{
		if (_points[res].get_Y() > _points[j].get_Y()) res = j;
	}
	for (int i = 0; i < _points.size(); i++)
	{
		_points[i].FindPolarAngle(_points[res]);
	}
}

void Grafs::combine()
{
	bool flag = true;

	for (int i = 0; i < convex_hull_Edges.size(); i++)
	{
		for (int j = 0; j < delaunay_triangulation_edges.size(); j++)
		{
			if (convex_hull_Edges[i] == delaunay_triangulation_edges[j])
			{
				flag = false;
			}
		}

		if (flag)
		{
			delaunay_triangulation_edges.push_back(convex_hull_Edges[i]);
		}

		else
		{
			flag = true;
		}
	}
}

vector<Edge> Grafs::get_delaunay_triangulation_edges()
{
	return delaunay_triangulation_edges;
}

vector<Node> Grafs::find_second_nodes(Node & ver)
{
	vector<Node>temp;

	for (int i = 0; i < delaunay_triangulation_edges.size(); i++)
	{
		if (ver == delaunay_triangulation_edges[i].get_finish_point())
		{
			temp.push_back(delaunay_triangulation_edges[i].get_start_point());
		}
		else
		{
			if (ver == delaunay_triangulation_edges[i].get_start_point())
			{
				temp.push_back(delaunay_triangulation_edges[i].get_finish_point());
			}
		}
	}

	return temp;
}

vector<Node> Grafs::find_third_vertex(Edge  edge)
{
	vector<Node> vertex;

	Node temp = edge.get_start_point();

	vector<Node >conected_with_start_point = find_second_nodes(temp);

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
		if (vector[i] == tr)
		{
			return;
		}
	}

	vector.push_back(tr);
}

void  Grafs::add_edge(Edge e, vector<Edge> &vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == e)
		{
			return;
		}
	}

	vec.push_back(e);
}

vector<Node> Grafs::rand_unique_points(int number_of_dots)
{
	srand(time(0));

	double x, y;

	bool flag = true;

	x = 400 + rand() % 850;

	y = 100 + rand() % 600;

	points.push_back(Node(x, y));

	while (points.size() < number_of_dots)
	{
		flag = true;

		x = 500 + rand() % 800;

		y = 20 + rand() % 500;

		Node temp(x, y);

		for (int j = 0; j < points.size(); j++)
		{
			if (points[j] == temp)
			{
				flag = false;

				break;
			}
		}
		if (flag)
		{
			points.push_back(temp);
		}
	}

	return points;
}

vector<Node> Grafs::read_from_file_points(string& file_name)
{
	ifstream inp_file(file_name);

	double x, y;

	while (inp_file && inp_file >> x && inp_file >> y)
	{
		points.push_back(Node(x, y));
	}

	return points;
}

void main()
{
	string file_name = "input.txt";

	Node first_coordinate;

	Node second_coordinate;

	const int M1 = 1;

	const int M2 = 2;

	int N = 10;

	Vertex line_to_draw[M2];

	vector<Vertex[M2]> lines;

	vector<Node> points;

	vector<Edge> convex_hull_edges;

	//Grafs test(points);

	//points = test.rand_unique_points(N);
	//points = test.read_from_file_points(file_name);

	/*test.convex_hull();
	test.delaunay_triangulation();
	test.voronoi_diagram();*/
	//convex_hull_edges = test.get_convex_hull();

	sf::RenderWindow window(sf::VideoMode(1300, 700), "SFML works!");

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			Grafs Test(points);
			if (points.size() >= 3)
			{
				Test.convex_hull();
				Test.delaunay_triangulation();
				Test.voronoi_diagram();
			}

			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;

				case Keyboard::Down:
					menu.MoveDown();
					break;

				case Keyboard::Return:

					switch (menu.GetPressedItem())
					{
					case 0:
						cout << "Convex Hull" << std::endl;
						convex_hull_edges = Test.get_convex_hull();
						break;
					case 1:
						cout << "Delaunay Triangulation" << std::endl;
						convex_hull_edges = Test.get_delaunay_triangulation_edges();
						break;
					case 2:
						cout << "Voronoi Diagram" << std::endl;
						convex_hull_edges = Test.get_voronoi_edges();
						break;
					}

					break;
				}

				break;
			case Event::Closed:
				window.close();

				break;

			}

		   if (Mouse::isButtonPressed(Mouse::Left))
			{
				points.push_back(Node(Mouse::getPosition().x,Mouse::getPosition().y));
				cout << Mouse::getPosition().x << " " << Mouse::getPosition().y << endl;
			    sleep(milliseconds(100));
			}
		}

		int size_of_hull = convex_hull_edges.size();

		window.clear();

		for (int i = 0; i < points.size(); i++)
		{
			first_coordinate = points[i];

			Vertex point_to_draw[]
			{
				Vertex(Vector2f(first_coordinate.get_X(), first_coordinate.get_Y()))
			};

			window.draw(point_to_draw, 1, sf::Points);
		}

		for (int i = 0; i < size_of_hull; i++)
		{
			Vertex point_to_draw[]
			{
				Vertex(Vector2f(convex_hull_edges[i].get_start_point().get_X(), convex_hull_edges[i].get_start_point().get_Y())),

				Vertex(Vector2f(convex_hull_edges[i].get_finish_point().get_X(), convex_hull_edges[i].get_finish_point().get_Y()))
			};

			window.draw(point_to_draw, 2, sf::Lines);
		}

		menu.draw(window);

		window.display();
	}

	//test.delaunay_triangulation();

	system("pause");
}