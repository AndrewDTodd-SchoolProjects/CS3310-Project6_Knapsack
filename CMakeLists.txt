# CMakeList.txt : CMake project for Project2_InversionsCount, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Project4_Koraraju")

if (UNIX AND NOT APPLE)
	add_definitions(-D_LINUX_BUILD)
elseif (WIN32)
	add_definitions(-D_WINDOWS_BUILD)
endif()

#set minimum c++ version to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's QuickSort executable
add_executable (Knapsack "KnapsackMain.cpp" "KnapsackData.h" "KnapsackData.cpp" "KnapsackSolution.h" "KnapsackSolution.cpp" "KnapsackReconstruction.h" "KnapsackReconstruction.cpp")
add_executable (BranchBoundKnapsack "KnapsackData.h" "KnapsackData.cpp" "KnapsackBranchAndBound.cpp" "KnapsackBranchAndBound.h" "BranchAndBoundMain.cpp")

# TODO: Add tests and install targets if needed.
