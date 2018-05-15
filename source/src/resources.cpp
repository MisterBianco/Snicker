#include "../headers/resources.h"
#include <iostream>
#include <unistd.h>

int __uid() {
    return setuid(0);
}

void sighandler(const int signum) {
    std::cout << "\r[" << signum << "] Exiting..." << std::endl;
    exit(0);
}

void __exit(const char* msg, const short code) {
    std::cout << msg << std::endl;
    exit(code);
}
