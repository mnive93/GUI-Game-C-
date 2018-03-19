
#include "serversocket.h"

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include "../protocol/packetprotocol.h"
#include "../protocol/gameprotocol.h"
#include "../ui/gtkui.h"

using namespace std;

void ServerSocket :: create_server_connection(){
    int server, client; // socket file descriptors
    int portNum = 3090; // port number
    int bufSize = 1024; // buffer size
    char buffer[bufSize]; // buffer to transmit
    string game_msg;
    bool isExit = false; // var fo continue infinitly
    string game_id;

    struct sockaddr_in server_addr;
    socklen_t size;

    cout << "\n- Starting server..." << endl;



    server = socket(AF_INET, SOCK_STREAM, 0);

    if (server < 0) {
        cout << "Error establishing socket ..." << endl;
        exit(-1);
    }

    cout << "- Socket server has been created..." << endl;



    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);


    int yes = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        //exit(1);
    }


    if ((::bind(server, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0)) {
        cout
                << "- Error binding connection, the socket has already been established..."
                << endl;
    }



    size = sizeof(server_addr);
    cout << "- Looking for clients..." << endl;
    listen(server, 1);

    /* ------------------- ACCEPT CALL ------------------ */

    client = accept(server, (struct sockaddr *) &server_addr, &size);
    int weights[3] = {1,1,1};
    int score = 0;
    int temp_score, other_score = 0;
    string random_choice, message;


    if (client < 0)
        cout << "- Error on accepting..." << endl;

    /**
     * Player 1 game protocol
     * Once it receives a ready message from player 2, player 1 informs Player 2 that it is ready for the game.
     * After it receives the random choice generated by Player 2, it generates its choice and increments the score based on the choice.
     * Player 2 then requests Player 1's score card by sending it's score card. It compares the score and see if the scores are equal.
     * After that it acknowledges the score card and the next round begins
     */
    GameProtocol protocol, return_protocol;
    while(client > 0){
        // loop to recive messages from client
        do {

            recv(client, buffer, bufSize, 0);

            game_msg = buffer;
            protocol = PacketProtocol :: unzip(game_msg);

            switch (protocol.gamecode) {
                case GameProtocol:: HELLO_MSG :{
                    notify(GameProtocol::PLAYER_2, GameProtocol :: STATUS_CODE, "Connected");
                    game_id = protocol.message;
                    return_protocol.gamecode = GameProtocol :: HELLO_MSG;
                    return_protocol.message = "Hello Player C";
                    message = PacketProtocol :: zip_packet(return_protocol);
                    strcpy(buffer, message.c_str());
                    send(client, buffer, bufSize, 0);

                    break;
                }
                case GameProtocol :: GAME_MSG:{

                    string random_choice = GameProtocol :: get_weighted_random_choice(weights);
                    notify(GameProtocol :: PLAYER_1, GameProtocol :: STATUS_CODE, "Choice : " + random_choice);
                    temp_score = GameProtocol :: check_winner(random_choice, protocol.message);
                    weights[GameProtocol :: get_index_choice_selected(random_choice) ] += temp_score;
                    score += temp_score;
                    if(random_choice != protocol.message)
                        other_score += temp_score == 0 ? 1 : 0;

                    notify(GameProtocol :: PLAYER_1, GameProtocol :: SCORE_CODE, "Score : " + to_string(score));
                    return_protocol.gamecode = GameProtocol :: GAME_MSG;
                    return_protocol.message = random_choice;
                    message = PacketProtocol :: zip_packet(return_protocol);
                    strcpy(buffer, message.c_str());
                    send(client, buffer, bufSize, 0);
                    break;
                }
                case GameProtocol :: REQ_SCORECARD: {
                    message = to_string(score) + ":" + to_string(other_score);
                    if(protocol.message == message){
                        return_protocol.gamecode = GameProtocol :: ACK_SCORECARD;
                        return_protocol.message = "Score card matches!";
                        message = PacketProtocol :: zip_packet(return_protocol);
                        strcpy(buffer, message.c_str());
                        send(client, buffer, bufSize, 0);
                    }
                    break;
                }
                case GameProtocol :: GOODBYE : {

                    isExit = true;
                    break;
                }


            }

        } while (!isExit);
        MySQLDB ::instance() ->insert_data(game_id, "player1", weights[0], weights[1], weights[2]);
        close(server);

    }

}