#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/wireless.h>

int is_wface(const std::string& ifname, const int& sock) {
    struct iwreq pifinfo;

    memset(&pifinfo, 0, sizeof(pifinfo));
    strncpy(pifinfo.ifr_name, ifname.c_str(), IFNAMSIZ);

    if (ioctl(sock, SIOCGIWNAME, &pifinfo) != -1) return 1;
    return 0;
}

int is_mon_mode(const std::string& ifname, const int& sock) {
    struct iwreq pifinfo;

    memset(&pifinfo, 0, sizeof(pifinfo));
    strncpy(pifinfo.ifr_name, ifname.c_str(), IFNAMSIZ);
    pifinfo.ifr_name[IFNAMSIZ - 1] = 0;

    ioctl(sock, SIOCGIWMODE, &pifinfo);
    return pifinfo.u.mode == 6;
}

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
