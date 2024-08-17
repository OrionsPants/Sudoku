#pragma once

#include "Grid.h"

class Solver
{
public:
	bool Solve(std::array<uint, 81>& grid);

	bool CanFindSolution(std::array<uint, 81> grid);

private:
	bool FindUnassignedLocation(const std::array<uint, 81>& grid, uint& idx);

	bool IsSafe(std::array<uint, 81>& grid, const uint idx, const uint val);

	bool Backtrack(std::array<uint, 81>& grid);

	bool CheckArray(const std::array<uint, 9>& arr);

	std::array<uint, 9> GetRow(const std::array<uint, 81>& grid, const uint8 row) const;

	std::array<uint, 9> GetCol(const std::array<uint, 81>& grid, const uint8 col) const;

	std::array<uint, 9> GetBox(const std::array<uint, 81>& grid, const uint8 box) const;

	bool IsBoardValid(const std::array<uint, 81>& grid);
};