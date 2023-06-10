#pragma once

#ifndef __FILESYSTEM__
#include <filesystem>
#endif

#ifndef __IOSTREAM__
#include <iostream>
#endif

#ifndef __SYS_STAT_H__
#include <sys/stat.h>
#endif

#ifdef __APPLE__
#include <sstream>
#endif


#ifndef KMP
#define KMP 0
#endif

#ifndef STRSTR
#define STRSTR 1
#endif

namespace fs = std::filesystem;
struct FileInfo {
    std::string name;
    uintmax_t size;
    bool is_directory;
    std::time_t modified_time;
    struct stat st;
};

int getSize(fs::path path);

template <typename T> void printInfo(T *info_array, int size);
template <typename T> void printAInfo(T *info_array);

int printSortedArr(char method, char standard);

int printSearchedInDir(fs::path const &dirpath, std::string pattern,
                       int method);

FileInfo *getInfoArray();
FileInfo *getInfo(fs::path filepath);

void searchFile(const fs::path &p, const std::string &target, int method,
                int algorithm);

template <typename T> void printInfo(T *info_array, int size) {
    const int fieldWidth = 27;

    for (int i = 0; i < size; i++) {
        std::ostringstream oss;

        oss << "Name: " << std::left << std::setw(fieldWidth)
            << info_array[i].name << "Size: " << std::left
            << std::setw(fieldWidth) << info_array[i].size
            << "Modified time: " << std::left
            << std::put_time(std::localtime(&(info_array[i].modified_time)),
                             "%c")
            << "         Type: " << std::left << std::setw(fieldWidth)
            << (info_array[i].is_directory ? "directory" : "file");

        std::cout << oss.str() << std::endl << std::endl;
    }
    delete[] info_array;
}

template <typename T> void printAInfo(T *info_array) {
    const int fieldWidth = 27;

 
    std::ostringstream oss;

    oss << "Name: " << std::left << std::setw(fieldWidth)
        << info_array->name << "Size: " << std::left
        << std::setw(fieldWidth) << info_array->size
        << "Modified time: " << std::left
        << std::put_time(std::localtime(&(info_array->modified_time)),
                            "%c")
        << "         Type: " << std::left << std::setw(fieldWidth)
        << (info_array->is_directory ? "directory" : "file");

    std::cout << oss.str() << std::endl << std::endl;
    delete info_array;
}
