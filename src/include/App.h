#pragma once

#include <SFML/Graphics.hpp>

#include "GridManager.h"
#include "InputBar.h"
#include "InputHandler.h"
#include "Renderer.h"
#include "Solver.h"
#include "types.h"

class App
{

public:
	App()
		: m_background_color(sf::Color(255, 255, 255, 255))
		, m_window(sf::VideoMode(800, 800), "Sudoku")
		, m_input_handler(m_grid_manager, m_window, m_solver, m_input_bar)
		, m_renderer(m_grid_manager.GetUI(), m_input_bar)
		, m_input_bar(m_grid_manager)
	{
		SetDefaultContextSettings();
		m_grid_manager.SetGridCenterPosition({400.0f, 400.0f});
	}

public:
	void Run();

private:
	void Initialise();
	void SetDefaultContextSettings();

private:
	Renderer m_renderer;
	Solver m_solver;
	InputBar m_input_bar;
	sf::RenderWindow m_window;
	GridManager m_grid_manager;
	InputHandler m_input_handler;
	uint16 m_framerate_limit = 60;
	sf::ContextSettings settings;
	sf::Color m_background_color;
};