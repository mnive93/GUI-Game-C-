
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include "../protocol/gameprotocol.h"
#include "../protocol/packetprotocol.h"
#include "clientsocket.h"
#include "../ui/gtkui.h"
#include <time.h>

void ClientSocket:: create_client_connection() {

    /* -------------- INITIALIZING VARIABLES -------------- */
    int client; // socket file descriptors
    int portNum = 3090; // port number (same that server)
    int bufsize = 1024; // buffer size
    char buffer[bufsize]; // buffer to transmit
    char ip[] = "192.168.10.15"; // Server IP

    bool isExit = false; // var fo continue infinitly
    string game_id = GameProtocol :: generate_current_game_id();
    struct sockaddr_in server_addr;


    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0) {
        cout << "\n-Error establishing socket..." << endl;
        exit(-1);
    }



    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    while (connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr))
           < 0)
        cout << "-Connection failed " << endl;


    // send to the server
    GameProtocol protocol,return_protocol;
    return_protocol.gamecode = GameProtocol :: HELLO_MSG;
    return_protocol.message = game_id;
    string message = PacketProtocol :: zip_packet(return_protocol);
    strcpy(buffer, message.c_str());
    send(client, buffer, bufsize, 0);

    int weights[3] = {1,1,1};
    int score = 0;
    int round = 1;
    int temp_score, other_score = 0;
    string random_choice;
    /**
     * Protocol for player 2.
     * Player 2 initiates the game by sending the initial random choice generated using a biased
     * random generator algorithm.
     * Once the other player generates it's choice, player reads and processes the choice generated.
     * After Player 2 has generated the score card, it requests the score card from player 1.
     * The score card is then acknowledged by Player 2 then the next round begins.
     */
    do {

        recv(client, buffer, bufsize, 0);
        message = buffer;
        protocol = PacketProtocol :: unzip(message);

        switch (protocol.gamecode) {
            case GameProtocol:: HELLO_MSG : {
                notify(GameProtocol :: PLAYER_1, GameProtocol:: STATUS_CODE, "Connected");
                return_protocol.gamecode = GameProtocol :: GAME_MSG;
                random_choice = GameProtocol :: get_weighted_random_choice(weights);
                notify(GameProtocol :: PLAYER_2, GameProtocol:: STATUS_CODE, "Choice : " + random_choice);
                return_protocol.message =random_choice;
                message = PacketProtocol :: zip_packet(return_protocol);
                strcpy(buffer, message.c_str());
                sleep(3);
                send(client, buffer, bufsize, 0);
                notify(GameProtocol :: PLAYER_2, GameProtocol :: ROUND_CODE, "Round :" + to_string(round));
                break;
            }
            case GameProtocol:: GAME_MSG: {
                temp_score = GameProtocol :: check_winner(random_choice, protocol.message);
                weights[GameProtocol :: get_index_choice_selected(random_choice)] += temp_score;
                score += temp_score;
                notify(GameProtocol :: PLAYER_2, GameProtocol :: SCORE_CODE, "Score : " + to_string(score));
                if(random_choice != protocol.message)
                    other_score += temp_score == 0 ? 1 : 0;


                return_protocol.gamecode = GameProtocol :: REQ_SCORECARD;
                return_protocol.message = to_string(other_score) + ":" + to_string(score);
                message = PacketProtocol :: zip_packet(return_protocol);
                strcpy(buffer, message.c_str());
                send(client, buffer, bufsize, 0);
                break;
            }

            case GameProtocol :: ACK_SCORECARD:

                random_choice = GameProtocol :: get_weighted_random_choice(weights);
                notify(GameProtocol :: PLAYER_2, GameProtocol:: STATUS_CODE, "Choice: " + random_choice);
                return_protocol.gamecode = GameProtocol :: GAME_MSG;
                return_protocol.message = random_choice;
                message = PacketProtocol :: zip_packet(return_protocol);
                if(score >= 100 || other_score >= 100) {
                    if(score >= 100)
                        notify(0, GameProtocol :: ROUND_CODE, "Player 2 is the winner");
                    else
                        notify(0, GameProtocol :: ROUND_CODE, "Player 1 is the winner");
                    MySQLDB ::instance() ->insert_data(game_id, "player2", weights[0], weights[1], weights[2]);

                    return_protocol.gamecode = GameProtocol :: GOODBYE;
                    return_protocol.message = "Goodbye";
                    message = PacketProtocol :: zip_packet(return_protocol);
                    strcpy(buffer, message.c_str());
                    send(client, buffer, bufsize, 0);
                    sleep(1);
                    isExit = true;
                    break;
                }
                sleep(3);
                round += 1;
                notify(GameProtocol :: PLAYER_2, GameProtocol :: ROUND_CODE, "Round :" + to_string(round));
                strcpy(buffer, message.c_str());
                send(client, buffer, bufsize, 0);

                break;

        }

    } while (!isExit);

    cout << "\nConnection terminated.\n";
    close(client);
    MySQLDB::instance()->close();
    sleep(5);
    exit(0);


}