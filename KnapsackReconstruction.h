#ifndef KNAPSACK_RECONSTRUCTION_H
#define KNAPSACK_RECONSTRUCTION_H

#include <vector>

#include "KnapsackData.h"
#include "KnapsackSolution.h"

std::vector<ItemData>* ReconstructKnapsack(const KnapsackData* knapsackData, const KnapsackSolution* knapsackSolution,
	uint32_t& subPoolStart,
	uint32_t& subPoolEnd);

#endif // !KNAPSACK_RECONSTRUCTION_H
