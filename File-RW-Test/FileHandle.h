#ifndef FILE_HANLDE_H
#define FILE_HANLDE_H

#include <mutex>
#include <vector>

class FileHandle {

public:
    FileHandle(const std::string& new_filename);

    void print_data_to_file(const std::vector<double>& data);
    std::vector<double> get_data_from_file();

    void print_data_to_file_mutex(const std::vector<double>& data);
    std::vector<double> get_data_from_file_mutex();

    ~FileHandle();

private:
    std::string filename;
    std::mutex mutex;
};

#endif
