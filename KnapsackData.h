#ifndef KNAPSACK_DATA_H
#define KNAPSACK_DATA_H

#include <cstdint>
#include <filesystem>
#include <iostream>

struct ItemData
{
	uint32_t _itemValue;
	uint32_t _itemWeight;

	friend std::ostream& operator<<(std::ostream& os, const ItemData& item);
};

struct KnapsackData
{
	uint32_t _knapsackCapacity;
	uint16_t _numItems;

	ItemData* _itemPool = nullptr;

	friend std::ostream& operator<<(std::ostream& os, const KnapsackData& data);
};

KnapsackData* KnapsackDataFromFile(const std::filesystem::path& path);

#endif // !KNAPSACK_DATA_H
