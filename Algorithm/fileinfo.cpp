#include <filesystem>
#include <sys/stat.h>
#include <ctime>
#include <string>
#include <iostream>
#include "sort.hpp"

namespace fs = std::filesystem;

struct FileInfo {
    std::string name;
    //std::string path;
    uintmax_t size;
    bool is_directory;
    std::time_t modified_time;
};

template <typename T>
void printInfo(T *info_array, int size) {
    const int fieldWidth = 27;

    for (int i = 0; i < size; i++) {
        std::ostringstream oss;

        oss << "Name: " << std::left << std::setw(fieldWidth) << info_array[i].name
            << "Size: " << std::left << std::setw(fieldWidth) << info_array[i].size
            << "Modified time: " << std::left << std::put_time(std::localtime(&(info_array[i].modified_time)), "%c")
            << "         Type: " << std::left << std::setw(fieldWidth) << (info_array[i].is_directory ? "directory" : "file");

        std::cout << oss.str() << std::endl << std::endl;
    }
}




int getSize(){
    int file_count = 0;
    for (auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() || entry.is_directory()) {
            file_count++;
        }
    }
    return file_count;
}
FileInfo* getInfo() {
    int file_count = getSize();

    FileInfo *info_array = new FileInfo[file_count];
    int i = 0;

    for (auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() || entry.is_directory()) {
            struct stat st;
            info_array[i].name = entry.path().filename().string();
            //info_array[i].path = entry.path().string();
            info_array[i].size = entry.is_directory() ? 0 : entry.file_size();
            if(stat(&(info_array[i].name)[0],&st) != 0){
                 std::cout << "Failed to get file status" << std::endl;
            }
            info_array[i].modified_time = st.st_mtime;
            info_array[i].is_directory = entry.is_directory();
            i++;
        }
    } 
    return info_array;
}


// FileInfo* sortInfo(char standard, char method){
//     FileInfo* arr = getInfo();
//     int size = getSize();
    


// }

int printSortedArr(char method, char standard){
    FileInfo* arr = getInfo();
    int size = getSize();

        switch(method){
        case 'q':
            switch(standard){
                case 't' : quick_sort(arr, 0, size-1,&FileInfo::modified_time ,comp<int>);
                    break;
                case 's' : quick_sort(arr, 0, size-1,&FileInfo::size ,comp<int>);
                    break;
                case 'n' : quick_sort(arr, 0, size-1,&FileInfo::name ,comp<string>);
                    break;
                //case 'p' : quick_sort(arr, 0, size-1,&FileInfo::path ,comp<string>);
                }
            break;

        case 'm':
            switch(standard){
                case 't' : merge_sort(arr, 0, size-1,&FileInfo::modified_time ,comp<int>);
                    break;
                case 's' : merge_sort(arr, 0, size-1,&FileInfo::size ,comp<int>);
                    break;
                case 'n' : merge_sort(arr, 0, size-1,&FileInfo::name ,comp<string>);
                    break;
                //case 'p' : merge_sort(arr, 0, size-1,&FileInfo::path ,comp<string>);
            } 
            break;

        case 'h':
            switch(standard){
                case 't' : heap_sort(arr, size, &FileInfo::modified_time ,comp<int>);
                    break;
                case 's' : heap_sort(arr, size, &FileInfo::size ,comp<int>);
                    break;
                case 'n' : heap_sort(arr, size, &FileInfo::name ,comp<string>);
                    break;
                //case 'p' : heap_sort(arr, size, &FileInfo::path ,comp<string>);

            } 
            break;
        default:
            return -1;
            }

    printInfo(arr, size);
    delete[] arr; //할당 해제
    return 0;
}
