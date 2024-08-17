#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "InputBar.h"

class Renderer
{
public:
	Renderer() = delete;
	Renderer(const GridUI& gridui, const InputBar& input_bar)
		: r_grid_ui(gridui)
		, r_input_bar(input_bar)
	{ }

	void Render(sf::RenderWindow& window)
	{
		for(auto& el : r_grid_ui.cells)
		{
			window.draw(el);
		}
		for(auto& el : r_grid_ui.cells_text)
		{
			window.draw(el);
		}
		for(auto& el : r_input_bar.m_buttons)
		{
			window.draw(el.shape);
		}
		for(auto& el : r_input_bar.m_buttons)
		{
			window.draw(el.text);
		}
		for(auto& el : r_grid_ui.box_outlines)
		{
			window.draw(el);
		}
	}

private:
	const GridUI& r_grid_ui;
	const InputBar& r_input_bar;
};