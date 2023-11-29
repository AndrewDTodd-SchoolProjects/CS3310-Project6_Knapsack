#include "KnapsackReconstruction.h"

#include <algorithm>

std::vector<ItemData>* ReconstructKnapsack(const KnapsackData* knapsackData, const KnapsackSolution* knapsackSolution,
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


	std::vector<ItemData>* solutionItems = new std::vector<ItemData>;

	uint32_t remainingCapacity = knapsackData->_knapsackCapacity;

	for (uint32_t item = subPoolEnd; item > 0; item--)
	{
		uint32_t itemSize = knapsackData->_itemPool[item - 1]._itemWeight;
		if (itemSize <= remainingCapacity &&
			(knapsackSolution->_subproblemMatrix[item - 1][remainingCapacity - itemSize] + knapsackData->_itemPool[item - 1]._itemValue) >=
			(knapsackSolution->_subproblemMatrix[item - 1][remainingCapacity]))
		{
			solutionItems->push_back(knapsackData->_itemPool[item - 1]);
			remainingCapacity -= itemSize;
		}
	}

	return solutionItems;
}