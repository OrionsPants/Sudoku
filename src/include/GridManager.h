#pragma once

#include "Grid.h"

class GridManager
{
public:
	GridManager();

	GridUI& GetUI();

	void SetGridCenterPosition(const sf::Vector2f& position);

	void UnclickCell();

	void ClickCell(const uint cell_idx);

	bool GetCellIdxFromPosition(const sf::Vector2i& position, uint& index);

	bool ClickAtPosition(const sf::Vector2i& position);

	bool SetCellDigit(const uint value);

	bool IsValidInput(const uint input_value);

	bool EraseCellDigit();
	/*

	void PanicMode()
	{
		for(auto& cell : cells)
		{
			cell.setFillColor(sf::Color(200, 125, 125, 255));
		}
	}
	void RelaxMode()
	{
		for(auto& cell : cells)
		{
			cell.setFillColor(cell_background_color);
		}
		UpdateHighlighting();
	}
	bool CheckSolution()
	{
		for(int i = 0; i < 81; i++)
		{
			if(digits[i] > 0 && digits[i] != solution[i])
				return false;
		}
		return true;
	}

private:


	void UpdateHighlighting()
	{
		int row = clicked_cell / 9;
		int col = clicked_cell % 9;

		for(int i = 0; i < 9; i++)
		{
			cells[row * 9 + i].setFillColor(sf::Color(175, 175, 175, 255));
		}
		for(int i = 0; i < 9; i++)
		{
			cells[col + 9 * i].setFillColor(sf::Color(175, 175, 175, 255));
		}
		for(int i = 0; i < 81; i++)
		{
			if(digits[i] == digits[clicked_cell] && digits[i] > 0)
			{
				cells[i].setFillColor(sf::Color(175, 175, 175, 255));
			}
		}

		cells[clicked_cell].setFillColor(sf::Color(150, 150, 150, 255));
	}

	

	

private:
	void InitCells()
	{
		int invalid_board[] = {0, 9, 0, 0, 4, 0, 0, 5, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 2, 0, 0,
					   0, 0, 3, 1, 4, 6, 0, 0, 0, 6, 0, 0, 0, 0, 7, 0, 4, 8, 0, 0, 1,
					   0, 0, 9, 0, 0, 6, 7, 5, 0, 0, 0, 8, 0, 5, 0, 0, 0, 7, 3, 0, 0,
					   9, 3, 0, 4, 2, 8, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 2, 0};

		if(!font.loadFromFile("./resources/fonts/futura.ttf"))
		{
			throw std::runtime_error("Failed to load font");
		}

		for(size_t y = 0; y < grid_height; y++)
		{
			for(size_t x = 0; x < grid_width; x++)
			{
				const size_t idx = y * grid_width + x;

				digits[idx] = invalid_board[idx];

				if(digits[idx] > 0)
				{
					locked_cell_idx.push_back(static_cast<int>(idx));
				}

				auto& cell = cells[idx];
				cell = sf::RectangleShape(cell_size * (1 - border_percentage));
				cell.setPosition(sf::Vector2f(cell_size.x * x, cell_size.y * y) + m_position);
				cell.setOutlineThickness(cell_size.x * border_percentage);
				cell.setOutlineColor(sf::Color(150, 150, 150, 255));

				auto& text = cells_text[idx];
				text = sf::Text(std::to_string(digits[idx]), font, font_size);
				text.setFillColor(sf::Color::Black);
				text.setOrigin(text.getLocalBounds().getSize() / 2.0f +
							   text.getLocalBounds().getPosition());
				text.setPosition(cells[idx].getGlobalBounds().getPosition() +
								 cells[idx].getLocalBounds().getSize() / 2.f);
			}
		}

		for(int i = 0; i < 8; i++)
		{
			auto& b_outline = box_outlines[i];
			if(i < 4)
			{
				b_outline = sf::RectangleShape(sf::Vector2f(
					(grid_width + border_percentage) * cell_size.x, box_outline_thickness));
			}
			else
			{
				b_outline = sf::RectangleShape(sf::Vector2f(
					box_outline_thickness, (grid_width + border_percentage) * cell_size.x));
			}

			b_outline.setOutlineThickness(0.0f);
			b_outline.setFillColor(sf::Color(25, 25, 25, 255));
		}
		sf::Vector2f top_bar =
			sf::Vector2f(-cell_size.x * border_percentage, -cell_size.y * border_percentage * 2) +
			m_position;
		box_outlines[0].setPosition(top_bar);
		box_outlines[1].setPosition(top_bar + sf::Vector2f(0.0f, cell_size.y * 3));
		box_outlines[2].setPosition(top_bar + sf::Vector2f(0.0f, cell_size.y * 6));
		box_outlines[3].setPosition(top_bar + sf::Vector2f(0.0f, cell_size.y * 9));
		sf::Vector2f left_bar =
			sf::Vector2f(-cell_size.x * border_percentage, -cell_size.y * border_percentage * 2) +
			m_position;
		box_outlines[4].setPosition(left_bar);
		box_outlines[5].setPosition(left_bar + sf::Vector2f(cell_size.x * 3, 0.0f));
		box_outlines[6].setPosition(left_bar + sf::Vector2f(cell_size.x * 6, 0.0f));
		box_outlines[7].setPosition(left_bar + sf::Vector2f(cell_size.x * 9, 0.0f));
	}
*/
	GridUI ui;

private:
	Grid grid;

public:
	std::array<int, 81> digits;
	std::vector<int> locked_cell_idx;

	std::optional<uint> clicked_cell = 82;
};