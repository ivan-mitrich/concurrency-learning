#ifndef FILE_HANLDE_H
#define FILE_HANLDE_H

#include <fstream>

class FileHandle {

public:
    FileHandle(const std::string& file_name);

    std::fstream& get() { return file; }

    ~FileHandle();

private:
    std::fstream file;
};

#endif
