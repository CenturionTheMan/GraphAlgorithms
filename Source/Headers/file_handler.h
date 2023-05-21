#pragma once
#include <string>
#include <fstream>
#include <iostream>

/// @brief Function will load data from file. First number will be treated as amount of numbers and each next will be number in result array
/// @param fileName File to get data from
/// @param arrSize First number in file
/// @param resArr Array with numbers
/// @return true if success, false otherwise
bool ReadDataFromFile(std::string fileName, int& arrSize, int*& resArr);

/// @brief Function will write data to csv file
/// @param filePath Path for file
/// @param values double dimension array with values to write - first dim lines, second columns
/// @param sizeDim1 amount of lines
/// @param sizeDim2 amount of columns
/// @return true if success, false otherwise
bool WriteDataToCsv(std::string filePath, std::string** values, int sizeDim1, int sizeDim2);

/// @brief Function will write data to csv file
/// @param filePath Path for file
/// @param values single dimension array with values to write (one row)
/// @param size amount of columns
/// @return true if success, false otherwise
bool WriteDataToCsv(std::string filePath, std::string* values, int size);



/// @brief Function will remove file with given path
/// @param filePath path for file to remove
/// @return true if success, false otherwise
bool RemoveFile(std::string filePath);