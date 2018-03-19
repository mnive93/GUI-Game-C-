

#include "packetprotocol.h"

#include "gameprotocol.h"
#include <vector>
#include <string.h>
#include <fstream>

char *token;
char seps[] = ",";
vector <string> split;

/**
 * All the parameters that is to be sent the other player is sent a comma separated string.
 * this method unzips the packet string and allocates to the Game protocol object to do some processing.
 * @param buffer
 * @return
 */
GameProtocol PacketProtocol :: unzip(string buffer){
    GameProtocol protocol;
    split = split_comma_string(buffer);
    protocol.gamecode = stoi(split[0]);
    protocol.message = split[1];
    return protocol;
}

vector<string> PacketProtocol:: split_comma_string(string buffer) {
    split.clear();
    token = strtok( &buffer[0], seps );
    while( token != NULL )
    {

        split.push_back(string(token));
        token = strtok( NULL, seps );

    }
    return split;
}
/**
 * The packet to be sent to the other player is zipped as a comma separated string.
 * This includes Game code and message.
 * Game code is used to identify what is the type of mesasge.
 * Message corresponding to the game code is also sent, so that the protocol in each player will do the processing.
 * @param protocol
 * @return
 */
string PacketProtocol:: zip_packet(GameProtocol protocol){
    string packet = to_string(protocol.gamecode) + "," + protocol.message;
    return packet;
}