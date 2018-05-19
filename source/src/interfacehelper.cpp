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

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <linux/wireless.h>

/*
 *  is_wface
 *          Function to test if supplied name is a wireless card name
 *
 * @ifname - the name of the card
 * @sock   - the persistent socket that ioctl will use
 */
int is_wface(const std::string& ifname, const int& sock) {
    struct iwreq pifinfo;

    memset(&pifinfo, 0, sizeof(pifinfo));
    strncpy(pifinfo.ifr_name, ifname.c_str(), IFNAMSIZ);

    if (ioctl(sock, SIOCGIWNAME, &pifinfo) != -1) return 1;
    return 0;
}

/*
 *  is_mon_mode
 *          Function to test if supplied name of wireless card is in monitor mode
 *
 * @ifname - the name of the card
 * @sock   - the persistent socket that ioctl will use
 */
int is_mon_mode(const std::string& ifname, const int& sock) {
    struct iwreq pifinfo;

    memset(&pifinfo, 0, sizeof(pifinfo));
    strncpy(pifinfo.ifr_name, ifname.c_str(), IFNAMSIZ);
    pifinfo.ifr_name[IFNAMSIZ - 1] = 0;

    ioctl(sock, SIOCGIWMODE, &pifinfo);
    return pifinfo.u.mode == 6;
}

/*
 *  set_channel
 *          Function to set the channel of a wireless card
 *
 * @ifname - the name of the card
 * @sock   - the persistent socket that ioctl will use
 * @channel - the channel to set the card on.
 */
int set_channel(const std::string& ifname, const int& sock, const int8_t& channel) {
    struct iwreq wrq;

    memset(&wrq, 0, sizeof(wrq));
    strncpy(wrq.ifr_name, ifname.c_str(), IFNAMSIZ);
    wrq.u.freq.m = channel;

    wrq.ifr_name[IFNAMSIZ - 1] = 0;
    if (ioctl(sock, SIOCSIWFREQ, &wrq) < 0) {
        std::cout << "Failed to change channel" << std::endl;
    } else {
        std::cout << "Channel set to: " << (unsigned)channel << std::endl;
    }
    return 0;
}

/*
 *  hopper
 *          daemon thread to handle the channel hopping of the wireless card
 *
 * @ifname - the name of the card
 * @sock   - the persistent socket that ioctl will use
 */
void hopper(const std::string& ifname, const int& sock) {
    unsigned int seed = time(NULL);
    double sleep_timer = 1;
    uint8_t tg_channels[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; // Make this global

    while (true) {
        uint8_t ch = rand_r(&seed) % 11 + 1;
        set_channel(ifname, sock, tg_channels[ch]);

        if (sleep_timer < 2) sleep_timer += .05;

        sleep(sleep_timer);
    }
    return;
}
