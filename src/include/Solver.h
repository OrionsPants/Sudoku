#pragma once

#include "Grid.h"

class Solver
{
public:
	bool Solve(std::array<int, 81>& grid);

	bool CanFindSolution(std::array<int, 81> grid);

private:
	bool FindUnassignedLocation(const std::array<int, 81>& grid, int& idx);

	bool IsSafe(std::array<int, 81>& grid, const int idx, const int val);

	bool Backtrack(std::array<int, 81>& grid);

	bool CheckArray(const std::array<int, 9>& arr);

	std::array<int, 9> GetRow(const std::array<int, 81>& grid, const uint8 row) const;

	std::array<int, 9> GetCol(const std::array<int, 81>& grid, const uint8 col) const;

	std::array<int, 9> GetBox(const std::array<int, 81>& grid, const uint8 box) const;

	bool IsBoardValid(const std::array<int, 81>& grid);
};