#ifndef KNAPSACK_SOLUTION_H
#define KNAPSACK_SOLUTION_H

#include <cstdint>

#include "KnapsackData.h"

struct KnapsackSolution
{
	uint32_t _optimalValue;
	uint32_t _rows;
	uint32_t _columns;
	uint32_t** _subproblemMatrix = nullptr;

	friend std::ostream& operator<<(std::ostream& os, const KnapsackSolution& solution);
};

KnapsackSolution* CalculateOptimalKnapsack(KnapsackData* knapsackData,
	uint32_t& subPoolStart,
	uint32_t& subPoolEnd);

#endif //!KNAPSACK_SOLUTION_H