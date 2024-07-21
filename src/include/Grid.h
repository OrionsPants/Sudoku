#pragma once

#include "types.h"
#include "utils.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <filesystem>
#include <iostream>
#include <optional>
#include <vector>

class Cell
{
public:
	Cell()
	{
		Init(10.f);
	}
	Cell(const float side_length, sf::Font _font)
	{
		Init(side_length);
		font = _font;
	}
	void Init(float side_length)
	{
		shape = sf::RectangleShape(sf::Vector2f(side_length, side_length));
		shape.setFillColor(background_color);
		shape.setOutlineColor(border_color);
		shape.setOutlineThickness(border_thickness);
	}

	void SetText(std::string txt)
	{
		text.setString(txt);
	}
	void SetColor(const sf::Color& col)
	{
		shape.setFillColor(col);
	}

	void SetPos(sf::Vector2f pos)
	{
		shape.setPosition(pos);
	}

	sf::RectangleShape& GetShape()
	{
		return shape;
	}

public:
	void Draw(sf::RenderWindow& window)
	{
		text.setFont(font);
		text.setFillColor(sf::Color::Black);
		text.setOrigin(text.getGlobalBounds().getSize() / 2.0f - text.getLocalBounds().getPosition());
		text.setPosition(shape.getPosition() + 0.5f * shape.getSize());

		std::cout << "Rect position: " << shape.getPosition().x << " " << shape.getPosition().y << "\nglobal bounds size: "
				  << text.getGlobalBounds().getSize().x << " " << text.getGlobalBounds().getSize().y << "\nlocal bounds position: " <<
				  text.getLocalBounds().getPosition().x << " " << text.getLocalBounds().getPosition().y << std::endl;

		window.draw(shape);
		window.draw(text);
	}

private:
	sf::Font font;

	sf::RectangleShape shape;
	sf::Text text;

	sf::Color background_color = sf::Color::White;
	sf::Color border_color = sf::Color::Black;

	float border_thickness = 5.0f;

	unsigned int main_digit;
};

class Grid
{
public:
	Grid(sf::Vector2f position)
	{

		m_position = position;
		m_position.x -= (cell_side_length * width / 2);
		m_position.y -= (cell_side_length * height / 2);

		InitCells();
	}

	void RenderToWindow(sf::RenderWindow& window)
	{

		for(auto& cell : cells)
		{
			cell.Draw(window);
		}
	}

private:
	void InitCells()
	{
		sf::Font font;

		std::filesystem::path cwd = std::filesystem::current_path();
		std::cout << cwd.u8string() << std::endl;

		if(!font.loadFromFile("./resources/fonts/futura.ttf"))
		{
			throw std::runtime_error("Failed to load font");
		}

		for(size_t y = 0; y < height; y++)
		{
			for(size_t x = 0; x < width; x++)
			{
				const size_t idx = y * width + x;
				cells[idx] = Cell(cell_side_length, font);
				cells[idx].SetPos(sf::Vector2f(cell_side_length * x, cell_side_length * y) + m_position);
				cells[idx].SetText(std::to_string(idx % 9));
			}
		}
	}

private:
	sf::Vector2f m_position;

	const size_t width = 9;
	const size_t height = 9;

	const float cell_side_length = 50;

	std::array<Cell, 81> cells;
};