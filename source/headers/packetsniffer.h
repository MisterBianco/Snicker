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

#ifndef PACKET_SNIFFER_H
#define PACKET_SNIFFER_H

#include <tins/tins.h>

using namespace Tins;

class Packet_Sniffer {
    public:

        // constructor with an interface
        Packet_Sniffer(const char* ifname);

        // constructor without interface instead with file
        Packet_Sniffer(const char* filename, const bool filereader);

        // Destructor
        ~Packet_Sniffer();

        int count = 0;

    protected:

        // Callback on every packet recieved
        bool callback(PDU& pdu);

        // Packet types 0..2
        void management_handler(const Dot11& pdu);
        void control_handler(const Dot11& pdu);
        void data_handler(const Dot11& pdu);
};

#endif
