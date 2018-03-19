

#ifndef RPSGUI_PACKETPROTOCOL_H
#define RPSGUI_PACKETPROTOCOL_H

#include <stdio.h>

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "gameprotocol.h"

using namespace std;

class PacketProtocol{

public:
    static GameProtocol unzip(string buffer);
    static string zip_packet(GameProtocol protocol);
    static vector<string> split_comma_string(string buffer);

};
#endif //RPSGUI_PACKETPROTOCOL_H
