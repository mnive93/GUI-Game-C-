//
// Created by shekhar on 11/3/18.
//

#ifndef RPSGUI_GAMEPROTOCOL_H
#define RPSGUI_GAMEPROTOCOL_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class GameProtocol{

public:
    const static int HELLO_MSG = 1;
    const static int GAME_MSG = 2;
    const static int REQ_SCORECARD = 3;
    const static int ACK_SCORECARD = 4;
    const static int GOODBYE = 5;

    const static int PLAYER_1 = 1;
    const static int PLAYER_2 = 2;
    const static int STATUS_CODE = 3;
    const static int SCORE_CODE = 4;
    const static int ROUND_CODE = 5;



    int gamecode;
    string message;


public:
    static int check_winner(string player_choice1, string player_choice2);
    static int generate_random_weight( int weights[]);
    static int findCeil(int arr[], int r, int l, int h);
    static string get_weighted_random_choice(int weights[]);
    static int get_index_choice_selected(string choice);
    static string generate_current_game_id();
};
#endif //RPSGUI_GAMEPROTOCOL_H
