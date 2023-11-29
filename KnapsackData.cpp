#include "KnapsackData.h"

#include <stdexcept>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

KnapsackData* KnapsackDataFromFile(const std::filesystem::path& path)
{
	if (!std::filesystem::exists(path))
		throw std::invalid_argument("Provided path doesnt exist \"" + path.string() + "\"");

	std::ifstream _stream(path);

	if (!_stream.is_open())
		throw std::runtime_error("Was unable to open file at \"" + path.string() + "\"");

	KnapsackData* _data = new KnapsackData;

	try
	{
		if (!(_stream >> _data->_knapsackCapacity >> _data->_numItems))
			throw std::runtime_error("Error reading knapsack information from file.\nEnsure the file is properly formatted with knapsack capacity followed by number of items as the first two entries of the file, followed by the item information");

		_data->_itemPool = new ItemData[_data->_numItems];

		for (uint32_t itemNum = 0; itemNum < _data->_numItems; itemNum++)
		{
			_stream >> _data->_itemPool[itemNum]._itemValue >> _data->_itemPool[itemNum]._itemWeight;
		}
	}
	catch (const std::exception& ex)
	{
		if (_data->_itemPool != nullptr)
			delete[] _data->_itemPool;

		delete _data;
		throw ex;
	}

	return _data;
}

std::ostream& operator<<(std::ostream& os, const ItemData& item)
{
	size_t valueSpaces = 7 - std::to_string(item._itemValue).length();
	size_t weightSpaces = 7 - std::to_string(item._itemWeight).length();

	os << std::setw(std::ceil(valueSpaces / 2.0)) << "" << item._itemValue << std::setw(valueSpaces / 2) << "" << 
		" | " << std::setw(std::ceil(weightSpaces / 2.0)) << "" << item._itemWeight << std::setw(weightSpaces / 2) << "";

	return os;
}

std::ostream& operator<<(std::ostream& os, const KnapsackData& data)
{
	std::string item = "Item";
	std::string value = "Value";
	std::string size = "Size";

	size_t itemSpaces = 7 - item.length();
	size_t valueSpaces = 7 - value.length();
	size_t sizeSpaces = 7 - size.length();

	os << "\nKnapsack capacity: " << data._knapsackCapacity << '\n' <<
		"Num of items read in: " << data._numItems <<
		"\n\n _____________________________ \n" << 
		"[ " << std::setw(std::ceil(itemSpaces / 2.0)) << "" << item << std::setw(itemSpaces / 2) << "" << 
		" | " << std::setw(std::ceil(valueSpaces / 2.0)) << "" << value << std::setw(valueSpaces / 2) << "" << 
		" | " << std::setw(std::ceil(sizeSpaces / 2.0)) << "" << size << std::setw(sizeSpaces / 2) << "" << " ]\n" << 
		" _____________________________ \n";

	for (uint64_t itemNum = 0; itemNum < data._numItems; itemNum++)
	{
		size_t itemNumSpaces = 7 - std::to_string(itemNum + 1).length();
		os << "[ " << std::setw(std::ceil(itemNumSpaces / 2.0)) << "" << itemNum + 1 << std::setw(itemNumSpaces / 2) << "" << 
			" | " << data._itemPool[itemNum] << " ]\n";
	}

	os << " _____________________________ \n\n";

	return os;
}