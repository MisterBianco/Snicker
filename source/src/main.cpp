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

#include <string>
#include <thread>
#include <iostream>
#include <signal.h>
#include <sys/socket.h>

// My header files
#include "../headers/resources.h"
#include "../headers/packetsniffer.h"
#include "../headers/interfacehelper.h"

/*
 * usage
 *      Used to print the intended usage of the program and its args
 */
void usage() {
    std::cout << "\r\n    Snicker 1.0" <<std::endl;
    std::cout << "      Jarad Dingman, MisterBianco" <<std::endl;
    std::cout <<std::endl;
    std::cout << " [Usage]: sudo snicker -i [wireless card] -c [channel]" <<std::endl;

    std::cout << "" <<std::endl;
    std::cout << "    @ -i: Wireless interface" <<std::endl;
    std::cout << "    @ -f: Frequency [2, 5, a]" <<std::endl;
    std::cout << "    @ -c: Channel" <<std::endl;
    std::cout << "    @ -t: Target Mac address" <<std::endl;
    std::cout << "" <<std::endl;
    std::cout << "" <<std::endl;

    __exit("", 1);
}

/*
 *  main
 *       Used as the entry point of the program
 *
 *  @argc - an int of all sys args
 *  @argv - an array of sys args
 */
int main(const int argc, const char* argv[]) {

    /*
        Only open and initialize the socket if a wireless interface is passed.

     */

    if (argc < 2) {
        usage();
        __exit("[-] Usage: ./run [interface]", 1);
    }

    // Function Variables
    std::string iface;
    std::string freq;
    std::string chan;
    std::string trgt;

    std::string filename;

    // Sys arg parsing
    for (int i = 0; i < argc; i++) {

        if (strcmp(argv[i], "-i") == 0) {
            iface = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "-f") == 0) {
            freq = argv[ i+1 ];
            i++;
        } else if (strcmp(argv[i], "-c") == 0) {
            chan = argv[ i+1 ];
            i++;
        } else if (strcmp(argv[i], "-o") == 0) {
            filename = argv[ i+1 ];
            i++;
        }
    }

    // If filename then we are reading from a file
    if (!filename.empty()) {

        Packet_Sniffer* sniffer = new Packet_Sniffer(filename.c_str(), true);

    // Else check for an interface
    } else if (!iface.empty()) {

        if (__uid()) __exit("[-] User not root", 1);

        // Persistent socket.
        int sock = -1;

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            __exit("[-] Can't open Socket", 1);
        }

        if (!is_wface(iface, sock)) {
            __exit("[-] Please select a wireless interface", 1);
        }

        if (!is_mon_mode(iface, sock)) {
            __exit("[-] Interface is not in monitor mode", 1);
        }

        // Set a signal handler for CTRL+C event
        signal(SIGINT, sighandler);

        // If channel is set then dont create the channel hopping thread.
        std::thread channel_hopper(hopper, iface, sock);

        Packet_Sniffer* sniffer = new Packet_Sniffer(iface.c_str());

        // Channel join MUST be here. Not sure why.
        channel_hopper.join();

    } else { usage(); }

    return 0;
}
