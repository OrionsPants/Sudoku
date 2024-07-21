#pragma once

#include <SFML/Graphics.hpp>

#include "types.h"
#include "Grid.h"



class App
{

public:
	App()
		: m_background_color(sf::Color(45, 20, 20, 255))
		, m_grid(sf::Vector2f(800/2, 600/2))
	{
		
		SetDefaultContextSettings();
	}

public:
	void Run()
	{
		sf::RenderWindow window(sf::VideoMode(800, 600), "Sudoku", sf::Style::Default, settings);
		window.setFramerateLimit(m_framerate_limit);

		while(window.isOpen())
		{
			HandleEvents(window);
			window.clear(m_background_color);

            m_grid.RenderToWindow(window);
			window.display();
		}
	}

private:
	void HandleEvents(sf::RenderWindow& window)
	{
		for(auto event = sf::Event{}; window.pollEvent(event);)
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}
	void SetDefaultContextSettings()
	{
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 8;
		settings.sRgbCapable = true;
	}

private:

	Grid m_grid;

	uint16 m_framerate_limit = 60;
	sf::ContextSettings settings;
	sf::Color m_background_color;
};