#include <iostream>

#include "../headers/packetsniffer.h"
#include <tins/tins.h>

using namespace Tins;

void Packet_Sniffer::config(const char* ifname) {
    SnifferConfiguration config;

    config.set_immediate_mode(true);
    config.set_promisc_mode(true);
    config.set_rfmon(true);

    Sniffer sniffer(ifname, config);
    sniffer.sniff_loop(make_sniffer_handler(this, &Packet_Sniffer::callback));
}

bool Packet_Sniffer::callback(PDU& pdu) {
    std::cout << pdu.pdu_type() << " packet: " << ++count << std::endl;
    return true;
}
