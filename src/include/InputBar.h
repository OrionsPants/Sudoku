#pragma once

#include <SFML/Graphics.hpp>

#include "Solver.h"
#include "types.h"

#include <array>
#include <functional>

template <typename T>
class Button
{
public:
	Button()
	{
		shape.setFillColor(colors.bg);
	}
	void SetFunction(const std::function<T()> func)
	{
		ClickFunction = func;
	}
	void SetSize(const sf::Vector2f& size)
	{
		shape.setSize(size);
	}
	void SetPosition(const sf::Vector2f& position)
	{
		shape.setPosition(position);
	}
	void SetBorder(const float thickness)
	{
		shape.setOutlineColor(colors.border);
		shape.setOutlineThickness(thickness);
	}
	void SetLabel(const std::string& label)
	{
		label_text = label;
		text.setString(label);
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(colors.fg);
		text.setOrigin(text.getLocalBounds().getSize() / 2.0f +
					   text.getLocalBounds().getPosition());
		text.setPosition(shape.getGlobalBounds().getPosition() +
						 shape.getLocalBounds().getSize() / 2.f);
	}

	void MoveBy(const sf::Vector2f& offset)
	{
		const auto top_left = shape.getPosition();
		shape.setPosition(top_left + offset);
		SetLabel(label_text);
	}
	std::string label_text;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape shape;
	std::function<T()> ClickFunction;

	ColorSet colors = {sf::Color::Black, sf::Color::White, sf::Color::Black, sf::Color::Blue};
};

class InputBar
{
public:
	InputBar(GridManager& gm) : r_grid_manager(gm)
	{
		InitButtons();
	}

	void ClickAtPosition(const sf::Vector2i& position)
	{
		for(auto& button : m_buttons)
		{
			const auto& bounds = button.shape.getGlobalBounds();

			if(position.x < bounds.left + bounds.width && position.x > bounds.left &&
			   position.y > bounds.top && position.y < bounds.top + bounds.height)
			{
				button.ClickFunction();
				break;
			}
		}
	}

private:
	void InitButtons()
	{
		GridManager& gm = r_grid_manager;
		sf::Font font;

		if(!font.loadFromFile("./resources/fonts/futura.ttf"))
		{
			throw std::runtime_error("Failed to load font");
		}

		for(int x = 0; x < 12; x++)
		{
			m_buttons.push_back(Button<bool>());
			auto& button = m_buttons[x];

			button.SetSize({button_width, button_height});
			const float x_pos = (button_width + border_width) * x + border_width;
			const float y_pos = 0.0f;
			button.SetPosition({x_pos, y_pos});
			button.font = font;
			button.SetBorder(2.0f);
			if(x < 9)
			{
				button.SetLabel(std::to_string(x + 1));
				button.SetFunction([x, &gm]() {
					std::cout << "Filled Number: " << x + 1 << std::endl;
					gm.SetCellDigit(x + 1);
					return true;
				});
			}
			else
			{
				switch(x)
				{
				case 9:
					button.SetLabel("del");
					button.SetFunction([&gm]() {
						gm.EraseCellDigit();
						std::cout << "Deleted cell" << std::endl;
						return true;
					});
					break;
				case 10:
					button.SetLabel("p");
					button.SetFunction([]() {
						std::cout << "Clicked pencil" << std::endl;
						return true;
					});
					break;
				case 11:
					button.SetLabel("sol");
					button.SetFunction([&gm]() {
						gm.FillWithSolution();
						std::cout << "Clicked solved" << std::endl;
						return true;
					});
					break;
				}
			}
		}

		const float curr_x_center =
			m_buttons[0].shape.getPosition().x + button_width * 6.0f + border_width * 5.0f;
		for(auto& button : m_buttons)
		{
			button.MoveBy({400 - curr_x_center, 660});
		}
	}

public:
	std::vector<Button<bool>> m_buttons;

private:
	float button_width = 35.0f;
	float button_height = 35.0f;
	float border_width = 3.0f;

	sf::Vector2f m_position;
	GridManager& r_grid_manager;
};
