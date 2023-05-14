#include "Headers/file_handler.h"


bool ReadDataFromFile(std::string fileName, int& arrSize, int*& resArr)
{
    std::ifstream file = std::ifstream(fileName);

    if(file.is_open() == false)
    {
        std::cout << "File error - OPEN" << std::endl;
        file.close();
        return false;
    }

    file >> arrSize;
    if (file.fail()){
        std::cout << "File error - READ SIZE" << std::endl;
        file.close();
        return false;
    }
    
    if(arrSize < 0)
    {
        std::cout << "File error - READ SIZE IS LESSER THAN ZERO" << std::endl;
        return false;
    }

    resArr = new int[arrSize];
    int val;
    for (int i = 0; i < arrSize; i++)
    {
        file >> val;
        if (file.fail())
        {
            std::cout << "File error - READ DATA" << std::endl;
            file.close();
            delete[] resArr;
            return false;
        }
        else
            resArr[i] = val;
    }
    file.close();
    return true;
}


bool WriteDataToCsv(std::string filePath, std::string** values, int sizeDim1, int sizeDim2)
{
    std::fstream fout;
  
    try
    {
        fout.open(filePath, std::ios::out | std::ios::app);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        fout.close();
        return false;
    }
    
    for (int i = 0; i < sizeDim1; i++)
    {
        for (int j = 0; j < sizeDim2; j++)
        {
            std::string holder = (j != sizeDim2 - 1)? values[i][j] + ", " : values[i][j];
            fout << holder;
        }
        fout << "\n";
        fout.close();
    }
    return true;
}

bool WriteDataToCsv(std::string filePath, std::string* values, int size)
{
    std::fstream fout;
  
    try
    {
        fout.open(filePath, std::ios::out | std::ios::app);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        fout.close();
        return false;
    }
    
    for (int i = 0; i < size; i++)
    {
        std::string temp = (i != size - 1)? values[i] + ", " : values[i];
        fout << temp;
    }
    fout <<"\n";
    fout.close();
    return true;
}

bool RemoveFile(std::string filePath)
{
    int status = remove(filePath.c_str());
    return (status == 0)? true : false;
}
