#ifndef KNAPSACK_BRANCH_BOUND_H
#define KNAPSACK_BRANCH_BOUND_H

#include <cstdint>
#include <vector>

#include "KnapsackData.h"

struct Node;

class KnapsackBranchAndBound
{
private:
	const KnapsackData* knapsackData = nullptr;
	std::vector<ItemData> best_taken;
	uint32_t best_value;

	//uint32_t UpperBound(const Node& node);

	uint32_t Bound(const Node* node);

public:
	KnapsackBranchAndBound(const KnapsackData* const& data);

	std::pair<const uint32_t&, const std::vector<ItemData>&> Solve();
};
#endif //!KNAPSACK_BRANCH_BOUND_H