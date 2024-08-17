#include "Solver.h"

#include <algorithm>
#include <unordered_map>

bool Solver::Solve(std::array<int, 81>& grid)
{
	if(Backtrack(grid))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Solver::CanFindSolution(std::array<int, 81> grid)
{
	return Solve(grid);
}

bool Solver::FindUnassignedLocation(const std::array<int, 81>& grid, int& idx)
{
	for(int i = 0; i < 81; i++)
	{
		if(grid[i] == 0)
		{
			idx = i;
			return true;
		}
	}
	return false;
}

bool Solver::IsSafe(std::array<int, 81>& grid, const int idx, const int val)
{
	int original_value = grid[idx];
	grid[idx] = val;
	bool res = IsBoardValid(grid);
	grid[idx] = original_value;
	return res;
}

bool Solver::Backtrack(std::array<int, 81>& grid)
{
	int idx = 0;
	if(!FindUnassignedLocation(grid, idx))
	{
		return true;
	}

	for(int i = 1; i <= 9; i++)
	{
		if(IsSafe(grid, idx, i))
		{
			grid[idx] = i;

			if(Backtrack(grid))
				return true;

			grid[idx] = 0;
		}
	}
	return false;
}

bool Solver::CheckArray(const std::array<int, 9>& arr)
{
	std::unordered_map<int, int> map;
	for(int t = 0; t < 9; t++)
	{
		map[arr[t]]++;
	}

	for(const auto& val : map)
	{
		if(val.second > 1 && val.first != 0)
			return false;
	}
	return true;
}

std::array<int, 9> Solver::GetRow(const std::array<int, 81>& grid, const uint8 row) const
{
	std::array<int, 9> result;
	for(int x = 0; x < 9; x++)
	{
		result[x] = grid[x + row * 9];
	}
	return result;
}

std::array<int, 9> Solver::GetCol(const std::array<int, 81>& grid, const uint8 col) const
{
	std::array<int, 9> result;
	for(int y = 0; y < 9; y++)
	{
		result[y] = grid[y * 9 + col];
	}
	return result;
}

std::array<int, 9> Solver::GetBox(const std::array<int, 81>& grid, const uint8 box) const
{
	std::array<int, 9> result = {0};
	int idx = 0;
	const int start_x = (box % 3) * 3;
	const int start_y = static_cast<int>(std::floor(box / 3)) * 3;
	for(int y = start_y; y < (start_y + 3); y++)
	{
		for(int x = start_x; x < (start_x + 3); x++)
		{
			result[idx] = grid[x + y * 9];
			idx++;
		}
	}
	return result;
}

bool Solver::IsBoardValid(const std::array<int, 81>& grid)
{
	for(uint8 i = 0; i < 9; i++)
	{
		std::array<int, 9> col = GetCol(grid, i);
		std::array<int, 9> row = GetRow(grid, i);
		std::array<int, 9> box = GetBox(grid, i);

		if(!CheckArray(col))
			return false;
		if(!CheckArray(row))
			return false;
		if(!CheckArray(box))
			return false;
	}
	return true;
}