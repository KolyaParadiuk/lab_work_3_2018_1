#pragma once
#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:

	Menu(float width, float height);

	~Menu();

	void draw(sf::RenderWindow &window);

	void MoveUp();

	void MoveDown();

	int GetPressedItem();

private:

	int selectedItemIndex;

	sf::Font font;

	sf::Text menu[MAX_NUMBER_OF_ITEMS];
};