#pragma once

#include <SFML/Graphics.hpp>

#include "Solver.h"
#include "types.h"

#include <array>

/*

enum ButtonType
{
	Digit = 0,
	Pencil,
	Erase,
	Solve,
	None
};

struct InputButton
{
	ButtonType type;
	sf::Font font;
	int digit;
	std::string label;
	sf::Text text;
	sf::Vector2f size;
	sf::Vector2f position;
	sf::Color text_color;
	sf::Color background_color;
	sf::Color border_color;
	float border_width;

	sf::RectangleShape rect;

	void Draw(sf::RenderWindow& window)
	{
		text.setFont(font);
		text.setString(label);
		text.setFillColor(text_color);

		text.setOrigin(text.getLocalBounds().getSize() / 2.0f +
					   text.getLocalBounds().getPosition());
		text.setPosition(rect.getGlobalBounds().getPosition() +
						 rect.getLocalBounds().getSize() / 2.f);

		window.draw(rect);
		window.draw(text);
	}

	void Set()
	{
		rect.setFillColor(background_color);
		rect.setOutlineColor(border_color);
		rect.setOutlineThickness(border_width);
		rect.setPosition(position);
		rect.setSize(size);
		text.setString(label);
	}
};



class InputBar
{
public:
	InputBar(const sf::Vector2f screen_dimensions)
	{
		// take center of screen, minus half the input bar width, and 15% from bottom of screen

		m_position = sf::Vector2f(screen_dimensions.x * 0.5f - button_width * 4.5f,
								  screen_dimensions.y - screen_dimensions.y * 0.15f);
		InitButtons();
	}

	void Draw(sf::RenderWindow& window)
	{
		for(auto& button : m_buttons)
		{
			button.Draw(window);
		}
	}

	bool ClickAtPosition(const sf::Vector2i& position, Grid& grid, Solver& solver)
	{
		int idx = GetButtonIdxFromPosition(position);

		if(idx == -1)
			return false;

		switch(m_buttons[idx].type){
			case ButtonType::Digit:
				return grid.SetCellDigit(m_buttons[idx].digit);
			case ButtonType::Erase:
				return grid.EraseCellDigit();
			case ButtonType::Pencil:
				return grid.TogglePencilMode();
			case ButtonType::Solve:
				solver.Solve(grid.digits);
			case ButtonType::None:
			return false;
		}
		return false;
	}

	int GetButtonIdxFromPosition(const sf::Vector2i& position)
	{
		for(int i = 0; i < m_buttons.size(); i++)
		{
			InputButton& but = m_buttons[i];
			if(position.x > but.position.x && position.x < (but.position.x + button_width) &&
			   position.y > but.position.y && position.y < (but.position.y + button_height))
			{
				return i;
			}
		}
		return -1;
	}
	const std::vector<InputButton>& GetButtons()
	{
		return const_cast<std::vector<InputButton>&>(m_buttons);
	}

private:
	void InitButtons()
	{
		sf::Font font;

		if(!font.loadFromFile("./resources/fonts/futura.ttf"))
		{
			throw std::runtime_error("Failed to load font");
		}

		for(int x = 0; x < 9; x++)
		{
			InputButton button;
			button.digit = x+1;
			button.background_color = sf::Color::White;
			button.text_color = sf::Color::Black;
			button.border_color = sf::Color::Blue;
			button.border_width = 3.0f;
			button.size = sf::Vector2f(button_width, button_height);
			button.position = sf::Vector2f(m_position.x + (button_width + button.border_width) * x,
										   m_position.y) -
							  2.0f * sf::Vector2f(button.border_width, 0.0f);
			button.font = font;
			button.label = std::to_string(x + 1);

			button.Set();
			button.type = ButtonType::Digit;
			m_buttons.push_back(button);
		}

		

		InputButton pencil_button;
		pencil_button.background_color = sf::Color::White;
		pencil_button.text_color = sf::Color::Black;
		pencil_button.border_color = sf::Color::Blue;
		pencil_button.border_width = 3.0f;
		pencil_button.size = sf::Vector2f(button_width, button_height);
		pencil_button.position =
			sf::Vector2f(m_position.x + (button_width + pencil_button.border_width) * 7,
						 m_position.y + button_height + pencil_button.border_width) -
			2.0f * sf::Vector2f(pencil_button.border_width, 0.0f);
		pencil_button.font = font;
		pencil_button.label = "P";

		pencil_button.Set();
		pencil_button.type = ButtonType::Pencil;
		m_buttons.push_back(pencil_button);

		InputButton button;
		button.background_color = sf::Color::White;
		button.text_color = sf::Color::Black;
		button.border_color = sf::Color::Blue;
		button.border_width = 3.0f;
		button.size = sf::Vector2f(button_width, button_height);
		button.position = sf::Vector2f(m_position.x + (button_width + button.border_width) * 8,
									   m_position.y + button_height + button.border_width) -
						  2.0f * sf::Vector2f(button.border_width, 0.0f);
		button.font = font;
		button.label = "X";

		button.Set();
		button.type = ButtonType::Erase;
		m_buttons.push_back(button);

		InputButton solve_button;
		solve_button.background_color = sf::Color::White;
		solve_button.text_color = sf::Color::Black;
		solve_button.border_color = sf::Color::Blue;
		solve_button.border_width = 3.0f;
		solve_button.size = sf::Vector2f(button_width, button_height);
		solve_button.position = sf::Vector2f(m_position.x + (button_width + button.border_width) * 9,
									   m_position.y + button_height + button.border_width) -
						  2.0f * sf::Vector2f(button.border_width, 0.0f);
		solve_button.font = font;
		solve_button.label = "S";

		solve_button.Set();
		solve_button.type = ButtonType::Solve;
		m_buttons.push_back(solve_button);
	}

	std::vector<InputButton>& GetButtons() const
	{
		return const_cast<std::vector<InputButton>&>(m_buttons);
	}

private:
	float button_width = 35.0f;
	float button_height = 35.0f;

	sf::Vector2f m_position;
	std::vector<InputButton> m_buttons;
};


*/