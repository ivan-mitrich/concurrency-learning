#include "FileHandle.h"

FileHandle::FileHandle(const std::string& filename) 
{
    file.open(filename);
}

FileHandle::~FileHandle() 
{
    if(file.is_open())
        file.close();
}

