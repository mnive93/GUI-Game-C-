#include "gtkui.h"
#include "../sockets/clientsocket.h"
#include "../sockets/serversocket.h"
#include "../protocol/gameprotocol.h"
#include "../database/db.h"
#include <iostream>
#include <time.h>
using namespace std;
using namespace Gtk;

/**
 * UI framework that is used to create the GUI is GTK+.
 * Bunch of widgets necessary to show is added in to vertical orientation box layout.
 * Respective status from the players are then notified using a n Observer pattern.
 *
 * */

string ip;
 GtkUI::GtkUI(){

    set_border_width(10);
    set_size_request(400, 400);
     set_title("GUI Game");
    // vBoxMain
    add(vBoxMain);
    vBoxMain.show();



     start_game.set_label("Start Game");
     start_game.set_size_request(50, 20);
     start_game.signal_clicked().connect
             (
                     sigc::mem_fun
                             (
                                     *this,
                                     &GtkUI::startGame
                             )
             );
     vBoxMain.add(start_game);
     start_game.show();


     player1_label.set_text("Player 1");
    player1.add(player1_label);
    player1_label.show();

    status_player1.set_text("Waiting");
    player1.add(status_player1);
    status_player1.show();

    score_player1.set_text("Score : 0");
    player1.add(score_player1);
    score_player1.show();


    player2_label.set_text("Player 2");
    player2.add(player2_label);
    player2_label.show();

    status_player2.set_text("Waiting");
    player2.add(status_player2);
    status_player2.show();

    score_player2.set_text("Score : 0");
    player2.add(score_player2);
    score_player2.show();

    hBoxplayers.add(player1);
    player1.show();

    round_label.set_text("Round : 0");
    hBoxplayers.add(round_label);
    round_label.show();

    hBoxplayers.add(player2);
    player2.show();



    vBoxMain.add(hBoxplayers);
    hBoxplayers.show();




 }
/**
 * Once the button start game is called,
 * Two processes are spawned for two players. Each process listening to a different port and listening to Network IP in Internet domain.
 */
void GtkUI :: startGame() {
    Glib::Thread::create(sigc::mem_fun(*this, &GtkUI::startClient), true);
    Glib::Thread::create(sigc::mem_fun(*this, &GtkUI::startServer), true);
    }

void GtkUI :: startClient() {
                ClientSocket clientSocket;
            clientSocket.subscribe(this);
            clientSocket.create_client_connection();

}

void GtkUI :: startServer() {
    ServerSocket serverSocket;
     serverSocket.subscribe(this);
    serverSocket.create_server_connection();

}


/**
 * Based on type of the message code, the message is parsed for respective players.
 * @param player
 * @param message_code
 * @param message
 */

void GtkUI ::update(int player, int message_code, string message) {

        switch(message_code) {
            case GameProtocol :: STATUS_CODE:{
                if(player == GameProtocol :: PLAYER_1)
                    update_player1_status(message);
                else
                    update_player2_status(message);
                break;
            }
            case GameProtocol :: SCORE_CODE : {
                if(player == GameProtocol :: PLAYER_1)
                    update_score_player1(message);
                else
                    update_score_player2(message);
                break;
            }
            case GameProtocol :: ROUND_CODE : {
                round_label.set_text(message);
            }

        }

}

void GtkUI ::update_player1_status(string status) {
    status_player1.set_text(status);
}

void GtkUI ::update_player2_status(string status) {
    status_player2.set_text(status);
}

void GtkUI ::update_score_player1(string score) {
    score_player1.set_text(score);
}

void GtkUI :: update_score_player2(string score) {
    score_player2.set_text(score);
}