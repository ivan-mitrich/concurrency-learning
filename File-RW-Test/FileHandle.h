#ifndef FILE_HANLDE_H
#define FILE_HANLDE_H

#include <string>

class FileHandle {

public:
    FileHandle(const std::string& new_filename);
    ~FileHandle();

private:
    std::string filename;
};

#endif
