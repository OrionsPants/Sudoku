#include "GridManager.h"

GridManager::GridManager()
{
	grid = Grid(9, 9);
	sf::Font font;
	if(!font.loadFromFile("./resources/fonts/futura.ttf"))
	{
		throw std::runtime_error("Failed to load font");
	}
	ui = GridUI({0.0f, 0.0f}, {50.0f, 50.0f}, 3.0f, 1.0f, font);
	ui.Update(grid);
	m_solver.Solve(grid.solution);
}

GridUI& GridManager::GetUI()
{
	return ui;
}

void GridManager::SetGridCenterPosition(const sf::Vector2f& position)
{
	ui.SetGridCenter(position);
	ui.Update(grid);
}

void GridManager::UnclickCell()
{
	clicked_cell.reset();
}

void GridManager::ClickCell(const uint cell_idx)
{
	ui.ResetHighlighting();
	if(clicked_cell.has_value() && clicked_cell.value() == cell_idx)
	{
		UnclickCell();
	}
	else
	{
		clicked_cell = cell_idx;
		ui.HighlightCellAndCross(cell_idx);
	}
}

bool GridManager::GetCellIdxFromPosition(const sf::Vector2i& position, uint& index)
{
	for(uint i = 0; i < ui.cells.size(); i++)
	{
		const auto& bounds = ui.cells[i].getGlobalBounds();
		if(position.x > bounds.left && position.x < (bounds.left + bounds.width) &&
		   position.y > bounds.top && position.y < (bounds.top + bounds.height))
		{
			index = i;
			return true;
		}
	}
	return false;
}

bool GridManager::ClickAtPosition(const sf::Vector2i& position)
{
	uint index;
	if(GetCellIdxFromPosition(position, index))
	{
		ClickCell(index);

		return true;
	}
	return false;
}

bool GridManager::SetCellDigit(const uint value)
{
	if(!clicked_cell.has_value() || !IsValidInput(value))
		return false;

	grid.SetDigit(clicked_cell.value(), value);
	ui.SetCellText(clicked_cell.value(), value);
	if(CheckGridState() == GridState::Solved)
		exit(0);

	return false;
}

bool GridManager::IsValidInput(const uint input_value)
{
	return (input_value > 0 && input_value <= 9);
}

bool GridManager::EraseCellDigit()
{
	if(!clicked_cell.has_value())
		return false;
	if(grid.DeleteDigit(clicked_cell.value()))
		ui.SetCellText(clicked_cell.value(), 0);

	ui.ResetHighlighting();
	CheckGridState();

	return true;
}

bool GridManager::FillWithSolution()
{
	grid.current_digits = grid.solution;
	ui.Update(grid);
	return false;
}

GridState GridManager::CheckGridState()
{
	if(grid.current_digits == grid.solution)
	{
		return GridState::Solved;
	}

	if(!m_solver.CanFindSolution(grid.current_digits))
	{
		ui.ErrorState();
		return GridState::Error;
	}
	else
	{
		ui.NormalState();
		ui.HighlightCellAndCross(clicked_cell.value());
		return GridState::Solveable;
	}
}
