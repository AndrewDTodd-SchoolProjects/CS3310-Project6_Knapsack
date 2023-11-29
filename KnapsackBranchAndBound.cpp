#include "KnapsackBranchAndBound.h"

#include <iostream>
#include <algorithm>
#include <queue>

struct Node
{
	int64_t level;
	uint32_t profit, bound;
	uint32_t weight;
	std::vector<uint32_t> items;
};

struct compare
{
	bool operator()(Node* a, Node* b)
	{
		return a->bound < b->bound;
	}
};

static bool CompareItems(const ItemData& a, const ItemData& b)
{
	double aRatio = static_cast<double>(a._itemValue) / a._itemWeight;
	double bRatio = static_cast<double>(b._itemValue) / b._itemWeight;

	return aRatio > bRatio;
}

KnapsackBranchAndBound::KnapsackBranchAndBound(const KnapsackData* const& data): knapsackData(data), best_value(0)
{}

//uint32_t KnapsackBranchAndBound::UpperBound(const Node& node)
//{
//	if (node.weight >= knapsackData->_knapsackCapacity)
//		return 0;
//
//	uint32_t profit_bound = node.profit;
//	uint32_t j = node.level + 1;
//	uint32_t total
//}

uint32_t KnapsackBranchAndBound::Bound(const Node* node)
{
	if (node->weight >= knapsackData->_knapsackCapacity)
	{
		return 0;
	}

	uint32_t profit_bound = node->profit;
	uint32_t j = node->level + 1;
	uint32_t totalWeight = node->weight;

	while ((j < knapsackData->_numItems) && (totalWeight + knapsackData->_itemPool[j]._itemWeight <= knapsackData->_knapsackCapacity))
	{
		totalWeight += knapsackData->_itemPool[j]._itemWeight;
		profit_bound += knapsackData->_itemPool[j]._itemValue;
		j++;
	}

	if (j < knapsackData->_numItems)
	{
		profit_bound += (knapsackData->_knapsackCapacity - totalWeight) * knapsackData->_itemPool[j]._itemValue / knapsackData->_itemPool[j]._itemWeight;
	}

	return profit_bound;
}

std::pair<const uint32_t&, const std::vector<ItemData>&> KnapsackBranchAndBound::Solve()
{
	std::sort(knapsackData->_itemPool, knapsackData->_itemPool + knapsackData->_numItems, CompareItems);

	std::priority_queue<Node*, std::vector<Node*>, compare> Q;
	Node* u = new Node();
	Node* v = new Node();
	u->level = -1;
	u->profit = u->weight = 0;
	Q.push(u);
	uint32_t maxProfit = 0;

	//std::vector<uint32_t> itemsIncluded(knapsackData->_numItems, 0);
	std::vector<uint32_t> bestItems;

	while (!Q.empty())
	{
		u = Q.top();
		Q.pop();

		if (u->level == knapsackData->_numItems - 1)
			continue;

		v->level = u->level + 1;
		v->weight = u->weight + knapsackData->_itemPool[v->level]._itemWeight;
		v->profit = u->profit + knapsackData->_itemPool[v->level]._itemValue;
		v->items = u->items;
		v->items.push_back(v->level);
		if (v->weight <= knapsackData->_knapsackCapacity && v->profit > maxProfit)
		{
			maxProfit = v->profit;
			bestItems = v->items;
		}

		v->bound = Bound(v);

		if (v->bound > maxProfit)
			Q.push(new Node(*v));

		v->weight = u->weight;
		v->profit = u->profit;
		v->items = u->items;
		v->bound = Bound(v);

		if (v->bound > maxProfit)
			Q.push(new Node(*v));
	}

	for (const uint32_t& level : bestItems)
	{
		best_taken.push_back(knapsackData->_itemPool[level]);
	}

	best_value = maxProfit;

	return { best_value, best_taken };
}