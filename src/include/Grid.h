#pragma once

#include "types.h"
#include "utils.h"

#include <SFML/Graphics.hpp>

#include <array>
#include <filesystem>
#include <iostream>
#include <optional>
#include <unordered_map>
#include <vector>

constexpr int grid_width = 9;
constexpr int grid_height = 9;

struct Grid
{
	Grid() { }
	Grid(const uint width_, const uint height_)
		: width(width_)
		, height(height_)
	{
		current_digits = std::vector<uint>(width * height, 0);
		solution = std::vector<uint>(width * height, 0);
		FillExample();

		InitLockedCells();
	}

	void FillExample()
	{
		uint invalid_board[] = {0, 9, 0, 0, 4, 0, 0, 5, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 2, 0, 0,
								0, 0, 3, 1, 4, 6, 0, 0, 0, 6, 0, 0, 0, 0, 7, 0, 4, 8, 0, 0, 1,
								0, 0, 9, 0, 0, 6, 7, 5, 0, 0, 0, 8, 0, 5, 0, 0, 0, 7, 3, 0, 0,
								9, 3, 0, 4, 2, 8, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 2, 0};
		memcpy(current_digits.data(), invalid_board, 81 * sizeof(int));
	}

	void InitLockedCells()
	{
		for(int i = 0; i < current_digits.size(); i++)
		{
			if(current_digits[i] != 0)
			{
				locked_cells.insert({i, true});
			}
			else
			{
				locked_cells.insert({i, false});
			}
		}
	}

	bool IsCellLocked(const uint cell_idx)
	{
		if(locked_cells.find(cell_idx) == locked_cells.end())
		{
			throw std::runtime_error("Could not find cell in lock check!");
		}
		return locked_cells.at(cell_idx);
	}

	void SetDigit(const uint index, const uint value)
	{
		if(IsCellLocked(index))
			return;

		current_digits[index] = value;
	}

	void DeleteDigit(const uint index)
	{
		if(IsCellLocked(index))
			return;

		current_digits[index] = 0;
	}

	std::vector<uint> current_digits;
	std::unordered_map<uint, bool> locked_cells;
	std::vector<uint> solution;

	uint width;
	uint height;
};

struct GridUI
{
	GridUI() { }
	GridUI(const sf::Vector2f position_,
		   const sf::Vector2f cell_size_,
		   const float outer_border_thickness,
		   const float inner_border_thickness,
		   const sf::Font font_)
		: position(position_)
		, cell_size(cell_size_)
		, border_percentage(inner_border_thickness / cell_size.x)
		, box_outline_thickness(outer_border_thickness)
		, font(font_)
	{
		InitCellPositions();
		InitGridColorsAndShape();
	}

	void HighlightCellAndCross(const uint index)
	{
		uint row = index / 9;
		uint col = index % 9;
		for(uint i = 0; i < 9; i++)
		{
			cells[i + row * 9].setFillColor(highlight_color_secondary);
			cells[col + i * 9].setFillColor(highlight_color_secondary);
		}
		cells[index].setFillColor(highlight_color_main);
	}

	void ResetHighlighting()
	{
		for(auto& cell : cells)
		{
			cell.setFillColor(background_color_normal);
		}
	}

	void SetCellText(uint index, uint value){
		auto& text = cells_text[index];
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Black);
		text.setString(std::to_string(value));
		text.setOrigin(text.getLocalBounds().getSize() / 2.0f +
						text.getLocalBounds().getPosition());
		text.setPosition(cells[index].getGlobalBounds().getPosition() +
							cells[index].getLocalBounds().getSize() / 2.f);
		if(value == 0)
			text.setString("");
	}

	void Update(const Grid& grid)
	{
		SetText(grid.current_digits);
	}

	void SetText(const std::vector<uint>& digits)
	{
		for(int i = 0; i < digits.size(); i++)
		{
			SetCellText(i, digits[i]);
		}
	}

	void SetGridCenter(const sf::Vector2f& pos)
	{
		sf::Vector2f current_left_top_corner = cells[0].getPosition();
		sf::Vector2f dimensions = cell_size * (9.0f + border_percentage);
		sf::Vector2f current_center = dimensions / 2.0f - current_left_top_corner;
		for(auto& cell : cells)
		{
			cell.setPosition(cell.getPosition() + pos - current_center);
		}
		position += pos - current_center;
		SetOutlinePosition();
	}

	void InitCellPositions()
	{
		for(int y = 0; y < 9; y++)
		{
			for(int x = 0; x < 9; x++)
			{
				cells[x + y * 9].setPosition({x * cell_size.x + cell_size.x * border_percentage,
											  y * cell_size.y + cell_size.y * border_percentage});
			}
		}
	}

	void InitGridColorsAndShape()
	{
		for(auto& cell : cells)
		{
			cell.setSize(cell_size - (cell_size * border_percentage));
			cell.setFillColor(background_color_normal);
			cell.setOutlineColor(border_color_light);
			cell.setOutlineThickness(cell_size.x * border_percentage);
		}
		SetOutlinePosition();
	}

	void SetOutlinePosition()
	{
		for(int i = 0; i < 4; i++)
		{
			auto& outline = box_outlines[i];
			outline.setFillColor(border_color_normal);
			outline.setSize({cell_size.x * (9 + border_percentage * 2.0f), 2.5f});
			outline.setPosition({position.x, position.y + i * (cell_size.y * 3)});
		}

		for(int i = 4; i < 8; i++)
		{
			auto& outline = box_outlines[i];
			outline.setFillColor(border_color_normal);
			outline.setSize({2.5f, cell_size.y * (9 + border_percentage)});
			outline.setPosition({position.x + (i - 4) * (cell_size.x * 3), position.y});
		}
	}

	std::array<sf::RectangleShape, 8> box_outlines;
	std::array<sf::RectangleShape, 81> cells;
	std::array<sf::Text, 81> cells_text;

	sf::Vector2f cell_size = sf::Vector2f(50.f, 50.f);
	float border_percentage = 0.03f;
	float box_outline_thickness = 3.f;
	uint font_size = 24;
	sf::Vector2f position;

	sf::Color background_color_normal = sf::Color::White;
	sf::Color background_color_alert = sf::Color::Red;
	sf::Color border_color_normal = sf::Color::Black;
	sf::Color border_color_light = sf::Color(120, 120, 120, 255);
	sf::Color highlight_color_main = sf::Color(125, 125, 125, 255);
	sf::Color highlight_color_secondary = sf::Color(160, 160, 160, 255);
	sf::Font font;
};

