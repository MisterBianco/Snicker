/*
* Copyright (c) 2018, Jarad Dingman
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright
*   notice, this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above
*   copyright notice, this list of conditions and the following disclaimer
*   in the documentation and/or other materials provided with the
*   distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "../headers/resources.h"
#include <iostream>
#include <unistd.h>

std::unordered_map<std::string, std::vector<int>> frequency_maps = {
    {"2", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}},
    {"5", {36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108, 112, 116, 132, 136, 140, 149, 153, 157, 161, 165}}
};

/*
 *  __uid
 *          Function to get the uid of the program
 */
int __uid() {
    return setuid(0);
}

/*
 *  valid_channel
 *          Function to check if supplied channel is valid
 *
 * @freq - the frequency range to check against
 * @chan - the channel to check
 */
int valid_channel(const std::string& freq, const int chan) {

    return 0;
}

/*
 *  sighandler
 *          Function to kill itself on sigint
 */
void sighandler(const int signum) {
    std::cout << "\r[" << signum << "] Exiting..." << std::endl;
    exit(0);
}

/*
 *  __exit
 *          My personal exit wrapper
 *
 * @msg - the msg to pring out on Exiting
 * @code - the status code for exit accessible using 'echo $?'
 */
void __exit(const char* msg, const short code) {
    std::cout << msg << std::endl;
    exit(code);
}
