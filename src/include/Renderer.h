#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "InputBar.h"

class Renderer
{
public:
	Renderer() = delete;
	Renderer(const GridUI& gridui)
		: r_grid_ui(gridui)
	{ }

	void Render(sf::RenderWindow& window)
	{
		for(auto& el : r_grid_ui.cells)
		{
			window.draw(el);
		}
		for(auto& el : r_grid_ui.box_outlines)
		{
			window.draw(el);
		}
		for(auto& el : r_grid_ui.cells_text)
		{
			window.draw(el);
		}
	}

private:
	const GridUI& r_grid_ui;
};