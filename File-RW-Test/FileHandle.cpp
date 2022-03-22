#include "FileHandle.h"
#include <fstream>

FileHandle::FileHandle(const std::string& new_filename) : filename(new_filename)
{ 

}

void FileHandle::print_data_to_file(const std::vector<double>& data)
{
    std::ofstream file;
    file.open(filename);
    
    for (const auto& item : data)
    {
        file << item << "\n";
    }
    
    file.close();
}

std::vector<double> FileHandle::get_data_from_file()
{
    std::ifstream file;  
    file.open(filename);
    
    std::vector<double> result;
    double read_value;
    bool readable = true;
    while (file >> read_value)
    {
        result.push_back(read_value);
    }
    
    file.close();
    
    return result;
}

void FileHandle::print_data_to_file_mutex(const std::vector<double>& data)
{
    std::lock_guard<std::mutex> lock(mutex);
    print_data_to_file(data);
}

std::vector<double> FileHandle::get_data_from_file_mutex()
{
    std::lock_guard<std::mutex> lock(mutex);
    return get_data_from_file();
}

FileHandle::~FileHandle() 
{

}

