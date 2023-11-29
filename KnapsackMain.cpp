#include <iostream>
#include <cstring>

#include "KnapsackData.h"
#include "KnapsackSolution.h"
#include "KnapsackReconstruction.h"

int main(int argc, char* argv[])
{
	KnapsackData* data = nullptr;
	KnapsackSolution* solution = nullptr;
	std::vector<ItemData>* solutionItems = nullptr;
	char* _filePath = nullptr;
	bool _filePathAllocated = false;
	bool debugInfo = false;
	uint32_t subPoolStart = std::numeric_limits<uint32_t>::max();
	uint32_t subPoolEnd = std::numeric_limits<uint32_t>::max();

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

			if (argc == 4)
			{
				std::string arg3 = argv[4];
				try
				{
					subPoolStart = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to starting with the first item of the item pool" << std::endl;
					subPoolStart = std::numeric_limits<uint32_t>::max();
				}
			}
			else if (argc == 5)
			{
				std::string arg3 = argv[4];
				try
				{
					subPoolStart = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to starting with the first item of the item pool" << std::endl;
					subPoolStart = std::numeric_limits<uint32_t>::max();
				}

				std::string arg4 = argv[5];
				try
				{
					subPoolEnd = static_cast<uint32_t>(std::stoi(arg4));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to ending with last item of the item pool" << std::endl;
					subPoolEnd = std::numeric_limits<uint32_t>::max();
				}
			}
			else if (argc > 5)
			{
				std::cout << "More argument entered than needed. Ignoring excess..." << std::endl;

				std::string arg3 = argv[4];
				try
				{
					subPoolStart = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to starting with the first item of the item pool" << std::endl;
					subPoolStart = std::numeric_limits<uint32_t>::max();
				}

				std::string arg4 = argv[5];
				try
				{
					subPoolEnd = static_cast<uint32_t>(std::stoi(arg4));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to ending with the last item of the item pool" << std::endl;
					subPoolEnd = std::numeric_limits<uint32_t>::max();
				}
			}
		}
		else
		{
			_filePath = argv[1];

			if (argc == 3)
			{
				std::string arg2 = argv[3];
				try
				{
					subPoolStart = static_cast<uint32_t>(std::stoi(arg2));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to starting with the first item of the item pool" << std::endl;
					subPoolStart = std::numeric_limits<uint32_t>::max();
				}
			}
			else if (argc == 4)
			{
				std::string arg2 = argv[3];
				try
				{
					subPoolStart = static_cast<uint32_t>(std::stoi(arg2));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to starting with the first item of the item pool" << std::endl;
					subPoolStart = std::numeric_limits<uint32_t>::max();
				}

				std::string arg3 = argv[4];
				try
				{
					subPoolEnd = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to ending with the last item of the item pool" << std::endl;
					subPoolEnd = std::numeric_limits<uint32_t>::max();
				}
			}
			else if (argc > 4)
			{
				std::cout << "More argument entered than needed. Ignoring excess..." << std::endl;

				std::string arg2 = argv[3];
				try
				{
					subPoolStart = static_cast<uint32_t>(std::stoi(arg2));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to starting with the first item of the item pool" << std::endl;
					subPoolStart = std::numeric_limits<uint32_t>::max();
				}

				std::string arg3 = argv[4];
				try
				{
					subPoolEnd = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to ending with the last item of the item pool" << std::endl;
					subPoolEnd = std::numeric_limits<uint32_t>::max();
				}
			}
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

	if (debugInfo)
	{
		startTime = std::chrono::high_resolution_clock::now();
	}
	solution = CalculateOptimalKnapsack(data, subPoolStart, subPoolEnd);
	if (debugInfo)
	{
		endTime = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

		std::cout << "Calculating optimal solution took ~" << duration.count() << " milliseconds" << std::endl;
		std::cout << *solution;
	}

	std::cout << "Optimal knapsack score: " << solution->_optimalValue << std::endl;

	solutionItems = ReconstructKnapsack(data, solution, subPoolStart, subPoolEnd);

	std::cout << "\nOptimal solution knapsack items:\n[ (" << (*solutionItems)[0] << " )";
	for (size_t item = 1; item < solutionItems->size(); item++)
	{
		std::cout << " | ( " << (*solutionItems)[item] << " )";
	}
	std::cout << " ]" << std::endl;

	if(_filePathAllocated)
		delete[] _filePath;

	for (uint32_t row = 0; row < solution->_rows; row++)
	{
		delete[] solution->_subproblemMatrix[row];
	}
	delete[] solution->_subproblemMatrix;
	delete solution;

	delete[] data->_itemPool;
	delete data;

	delete solutionItems;

	return 0;
}
