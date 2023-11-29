#include "KnapsackSolution.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <cmath>

KnapsackSolution* CalculateOptimalKnapsack(KnapsackData* knapsackData,
	uint32_t& subPoolStart,
	uint32_t& subPoolEnd)
{
	if (subPoolStart == std::numeric_limits<uint32_t>::max())
	{
		subPoolStart = 0;
	}
	else
	{
		if (subPoolStart >= knapsackData->_numItems)
			throw std::invalid_argument("The sub pool start index has to be be within the bounds of the item pool. Start index entered: " + std::to_string(subPoolStart) + 
				". Item pool length: " + std::to_string(knapsackData->_numItems));
	}

	if (subPoolEnd == std::numeric_limits<uint32_t>::max())
	{
		subPoolEnd = knapsackData->_numItems;
	}
	else
	{
		if (subPoolEnd > knapsackData->_numItems)
			throw std::invalid_argument("The sub pool end index has to be within the bounds of the item pool. End index entered: " + std::to_string(subPoolEnd) +
				". Item pool length: " + std::to_string(knapsackData->_numItems));
	}

	KnapsackSolution* solution = new KnapsackSolution;

	uint32_t subPoolItemCount = subPoolEnd - subPoolStart;

	solution->_subproblemMatrix = new uint32_t*[subPoolItemCount + 1];
	for (uint32_t row = 0; row < subPoolItemCount + 1; row++)
	{
		solution->_subproblemMatrix[row] = new uint32_t[knapsackData->_knapsackCapacity + 1];
	}

	//base case for capacity of 0
	for (uint32_t column = 0; column < knapsackData->_knapsackCapacity + 1; column++)
	{
		solution->_subproblemMatrix[0][column] = 0;
	}

	//Tabulate all the subproblems. Fill the matrix
	for (uint32_t itemNum = 1; itemNum < subPoolItemCount + 1; itemNum++)
	{
		uint32_t itemSize = knapsackData->_itemPool[itemNum - 1 + subPoolStart]._itemWeight;

		for (uint32_t capacity = 0; capacity < knapsackData->_knapsackCapacity + 1; capacity++)
		{
			if (itemSize > capacity)
			{
				solution->_subproblemMatrix[itemNum][capacity] = solution->_subproblemMatrix[itemNum - 1][capacity];
			}
			else
			{
				solution->_subproblemMatrix[itemNum][capacity] =
					std::max(
						{
							solution->_subproblemMatrix[itemNum - 1][capacity],
							solution->_subproblemMatrix[itemNum - 1][capacity - itemSize] + knapsackData->_itemPool[itemNum - 1 + subPoolStart]._itemValue
						});
			}
		}
	}

	solution->_optimalValue = solution->_subproblemMatrix[subPoolItemCount][knapsackData->_knapsackCapacity];
	solution->_rows = subPoolItemCount + 1;
	solution->_columns = knapsackData->_knapsackCapacity + 1;
	return solution;
}

std::ostream& operator<<(std::ostream& os, const KnapsackSolution& solution)
{
	os << "\nSolution optimal value: " << solution._optimalValue << '\n' << 
		"Subproblem matrix rows: " << solution._rows << '\n' << 
		"Subproblem matrix columns: " << solution._columns << '\n' << 
		"\n\n" << 
		"Solution subproblem matrix\n    ";

	for (uint32_t column = 0; column < solution._columns; column++)
	{
		size_t columnNumSpaces = 7 - std::to_string(column).length();

		os << std::setw(std::ceil(columnNumSpaces / 2.0)) << "" << column << std::setw(columnNumSpaces / 2) << "" << "   ";
	}

	os << "\n   ";

	for (uint32_t column = 0; column < solution._columns - 1; column++)
	{
		os << "__________";
	}

	os << "_________\n";

	for (uint32_t row = 0; row < solution._rows; row++)
	{
		os << row << " [ ";
		for (uint32_t column = 0; column < solution._columns; column++)
		{
			size_t numSpaces = 7 - std::to_string(solution._subproblemMatrix[row][column]).length();

			if (column > 0)
				os << " | ";

			os << std::setw(std::ceil(numSpaces / 2.0)) << "" << solution._subproblemMatrix[row][column] << std::setw(numSpaces / 2) << "";
		}
		os << " ]\n";
	}

	os << "   ";
	for (uint32_t column = 0; column < solution._columns - 1; column++)
	{
		os << "__________";
	}

	os << "_________\n\n";

	return os;
}