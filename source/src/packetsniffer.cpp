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
    const Dot11& dot11_header = pdu.rfind_pdu<Dot11>();
    const uint8_t dot11_type = dot11_header.type();

    switch(dot11_type) {
        case 0:
            management_handler(dot11_header);
            break;
        case 1:
            control_handler(dot11_header);
            break;
        case 2:
            data_handler(dot11_header);
            break;
    }
    return true;
}

void Packet_Sniffer::management_handler(const Dot11& pdu) {
    std::cout << "0 | Packet: " << ++count << std::endl;
}

void Packet_Sniffer::control_handler(const Dot11& pdu) {
    std::cout << "1 | packet: " << ++count << std::endl;
}

void Packet_Sniffer::data_handler(const Dot11& pdu) {
    std::cout << "2 | packet: " << ++count << std::endl;
}
