#pragma once

#include "Grid.h"
#include "InputBar.h"
#include "Solver.h"
#include "types.h"

#include <memory>
#include <unordered_map>

const std::unordered_map<sf::Keyboard::Key, uint> numkeys = {{sf::Keyboard::Key::Num1, 1},
															 {sf::Keyboard::Key::Num2, 2},
															 {sf::Keyboard::Key::Num3, 3},
															 {sf::Keyboard::Key::Num4, 4},
															 {sf::Keyboard::Key::Num5, 5},
															 {sf::Keyboard::Key::Num6, 6},
															 {sf::Keyboard::Key::Num7, 7},
															 {sf::Keyboard::Key::Num8, 8},
															 {sf::Keyboard::Key::Num9, 9},
															 {sf::Keyboard::Key::Numpad1, 1},
															 {sf::Keyboard::Key::Numpad2, 2},
															 {sf::Keyboard::Key::Numpad3, 3},
															 {sf::Keyboard::Key::Numpad4, 4},
															 {sf::Keyboard::Key::Numpad5, 5},
															 {sf::Keyboard::Key::Numpad6, 6},
															 {sf::Keyboard::Key::Numpad7, 7},
															 {sf::Keyboard::Key::Numpad8, 8},
															 {sf::Keyboard::Key::Numpad9, 9}

};

class InputHandler
{
public:
	InputHandler() = delete;
	InputHandler(GridManager& grid_manager, sf::RenderWindow& window, Solver& solver, InputBar& input_bar)
		: grid_manager(grid_manager)
		, m_window(window)
		, r_input_bar(input_bar)
		, r_solver(solver)
	{ }

	void HandleInput()
	{
		for(auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::Resized:
				Resize(event.size.width, event.size.height);
				break;
			case sf::Event::MouseButtonPressed:
				MouseButtonPressed(event);
				break;
			case sf::Event::MouseButtonReleased:
				MouseButtonReleased(event);
				break;
			case sf::Event::KeyPressed:
				KeyPressed();
				break;
			case sf::Event::KeyReleased:
				KeyRelease();
				break;
			}
		}
	}

private:
	void Resize(const int x, const int y)
	{
		sf::View view = m_window.getDefaultView();
		view.setSize({static_cast<float>(x), static_cast<float>(y)});
		m_window.setView(view);
	}

	void KeyRelease()
	{
		key_pressed = false;
	}

	void KeyPressed()
	{
		key_pressed = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			exit(0);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) ||
		   sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			grid_manager.EraseCellDigit();
		}
		for(auto& key : numkeys)
		{
			if(sf::Keyboard::isKeyPressed(key.first))
			{
				grid_manager.SetCellDigit(key.second);
				break;
			}
		}
	}

	void MouseButtonPressed(const sf::Event& event)
	{
		if(event.mouseButton.button == sf::Mouse::Left && !mouse_left_is_pressed)
		{
			mouse_left_is_pressed = true;
			m_mouse_position = sf::Mouse::getPosition(m_window);

				grid_manager.ClickAtPosition(m_mouse_position);
				r_input_bar.ClickAtPosition(m_mouse_position);
		}
	}

	void MouseButtonReleased(const sf::Event& event)
	{
		if(event.mouseButton.button == sf::Mouse::Left)
		{
			mouse_left_is_pressed = false;
		}
	}

private:
	Solver& r_solver;
	sf::Vector2i m_mouse_position;
	bool mouse_left_is_pressed = false;
	bool key_pressed = false;

	sf::RenderWindow& m_window;
	InputBar& r_input_bar;
	GridManager& grid_manager;
};
