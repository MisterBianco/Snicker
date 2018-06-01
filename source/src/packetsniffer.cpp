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

#include <unistd.h>
#include <iostream>

#include "../headers/packetsniffer.h"
#include <tins/tins.h>

using namespace Tins;

// Notes: Make this class able to sniff from a file if given.
//      Do this using multiple constructors of different types.

typedef Dot11::address_type address_type;

Packet_Sniffer::Packet_Sniffer(const char* ifname) {
    SnifferConfiguration config;

    config.set_immediate_mode(true);
    config.set_promisc_mode(true);
    config.set_rfmon(true);

    Sniffer sniffer(ifname, config);
    sniffer.sniff_loop(make_sniffer_handler(this, &Packet_Sniffer::callback));
    std::cout << "Final: " << count << std::endl;
}

Packet_Sniffer::Packet_Sniffer(const char* filename, const bool filereader) {
    FileSniffer fsniffer_(filename);
    fsniffer_.sniff_loop(make_sniffer_handler(this, &Packet_Sniffer::callback));
    std::cout << "Final: " << count << std::endl;
}

Packet_Sniffer::~Packet_Sniffer() {}

bool Packet_Sniffer::callback(PDU& pdu) {
    // Remove counter after resolve missing packet issue
    ++count;

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
        default:
            std::cout << "BAD PACKET" << std::endl;
            break;
    }
    std::cout << count << std::endl;
    return true;
}

void Packet_Sniffer::management_handler(const Dot11& pdu) {
    const uint8_t& dot11_subtype = pdu.subtype();

    const Dot11ManagementFrame& mgmt_frame = pdu.rfind_pdu<Dot11ManagementFrame>();

    //const address_type addr2 = mgmt_frame.addr2();
    //const address_type addr3 = mgmt_frame.addr3();

    switch(dot11_subtype) {
        case 0:                 // Assoc request
            break;
        case 1:                 // Assoc Response
            break;
        case 2:                 // Reassoc request
            break;
        case 3:                 // Reassoc Response
            break;
        case 4:                 // Probe Request
            break;
        case 5:                 // Probe Response
            break;
        case 8:                 // Beacon
            break;
        case 9:                 // ATIM
            break;
        case 10:                // Disassociation
            break;
        case 11:                // Auth
            break;
        case 12:                // Deauthentication
            break;
        default:
            break;
    }
    //std::cout << "mgmt | " << (uint)dot11_subtype << " | Packet: " << count << std::endl;
}

void Packet_Sniffer::control_handler(const Dot11& pdu) {
    const uint8_t& dot11_subtype = pdu.subtype();

    const Dot11Control& cntrl_frame = pdu.rfind_pdu<Dot11Control>();

    //const address_type addr1 = cntrl_frame.addr1();
    //std::cout << "ctrl | " << (uint)dot11_subtype << "  | Packet: " << count << std::endl;
}

void Packet_Sniffer::data_handler(const Dot11& pdu) {
    const uint8_t& dot11_subtype = pdu.subtype();

    const Dot11Data& data_frame = pdu.rfind_pdu<Dot11Data>();

    //const address_type addr2 = data_frame.addr2();
    //const address_type addr3 = data_frame.addr3();
    //std::cout << "data | " << (uint)dot11_subtype << "  | Packet: " << count << std::endl;
}
