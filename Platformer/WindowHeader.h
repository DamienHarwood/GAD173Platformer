#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class MainRenderWindow
{
public:
	//window size
	const int windowWidth = 1025;
	const int windowHeight = 650;
	//mouse position
	sf::Vector2f worldPos;
	sf::RenderWindow window;
	//functions
	void clear()
	{
		window.clear(sf::Color::White);
		
	}

	void close()
	{
		window.close();
	}
};