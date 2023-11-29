#include <iostream>
#include <cstring>

#include "KnapsackData.h"
#include "KnapsackBranchAndBound.h"

int main(int argc, char* argv[])
{
	KnapsackData* data = nullptr;
	char* _filePath = nullptr;
	bool _filePathAllocated = false;
	bool debugInfo = false;
	//uint32_t subPoolStart = std::numeric_limits<uint32_t>::max();
	//uint32_t subPoolEnd = std::numeric_limits<uint32_t>::max();

	if (argc < 2)
	{
		std::string filePath;
		std::cout << "Enter a path to a file containing the knapsack problem data info\n >>> ";
		getline(std::cin, filePath);

		_filePath = new char[filePath.size() + 1];
		std::strcpy(_filePath, filePath.c_str());
		_filePathAllocated = true;
	}
	else
	{
		std::string secondArg = argv[1];
		if (secondArg == "-d")
		{
			debugInfo = true;

			_filePath = argv[2];
		}
		else
		{
			_filePath = argv[1];
		}
	}

	std::chrono::milliseconds total = std::chrono::milliseconds();
	std::chrono::_V2::system_clock::time_point startTime;
	std::chrono::_V2::system_clock::time_point endTime;
	std::chrono::milliseconds duration;
	try
	{
		if (debugInfo)
		{
			startTime = std::chrono::high_resolution_clock::now();
		}
		data = KnapsackDataFromFile(std::filesystem::path(_filePath));
		if (debugInfo)
		{
			endTime = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

			std::cout << "Knapsack data loading from file took ~" << duration.count() << " milliseconds" << std::endl;
			std::cout << *data;
		}
	}
	catch (const std::invalid_argument& argEx)
	{
		std::cerr << "Error: " << argEx.what() << std::endl;
		if (_filePathAllocated)
			delete[] _filePath;

		return 1;
	}
	catch (const std::runtime_error& rntEx)
	{
		std::cerr << "Error: " << rntEx.what() << std::endl;
		if (_filePathAllocated)
			delete[] _filePath;

		return 1;
	}

	KnapsackBranchAndBound branchBound(data);
	if (debugInfo)
	{
		startTime = std::chrono::high_resolution_clock::now();
	}
	auto solution = branchBound.Solve();
	if (debugInfo)
	{
		endTime = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

		std::cout << "Calculating optimal solution took ~" << duration.count() << " milliseconds" << std::endl;
	}

	std::cout << "Optimal knapsack score: " << solution.first << std::endl;

	std::cout << "\nOptimal solution knapsack items:\n[ (" << solution.second[0] << " )";
	for (size_t item = 1; item < solution.second.size(); item++)
	{
		std::cout << " | ( " << solution.second[item] << " )";
	}
	std::cout << " ]" << std::endl;

	if(_filePathAllocated)
		delete[] _filePath;

	delete[] data->_itemPool;
	delete data;

	return 0;
}
