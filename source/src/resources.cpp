#include "../headers/resources.h"
#include <iostream>
#include <unistd.h>

std::unordered_map<std::string, std::vector<int>> frequency_maps = {
    {"2", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}},
    {"5", {36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 132, 136, 140, 149, 153, 157, 161, 165}}
};

int __uid() {
    return setuid(0);
}

int valid_channel(const std::string& freq, const int chan) {
    
    return 0;
}

void sighandler(const int signum) {
    std::cout << "\r[" << signum << "] Exiting..." << std::endl;
    exit(0);
}

void __exit(const char* msg, const short code) {
    std::cout << msg << std::endl;
    exit(code);
}
