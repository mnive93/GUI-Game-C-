
#include "gameprotocol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <ctime>
#include <random>

using namespace std;

string options[333] = {"rock", "paper", "scissors"};

int arr[3] = {0,1,2};

/**
 * Function to check the winner. It accepts two arguments which compares both the players choice and computers the winner of this round based on the game's rules.
 * @param player_choice1
 * @param player_choice2
 * @return
 */
int GameProtocol:: check_winner(string player_choice1, string player_choice2) {
    if(player_choice1 == player_choice2) {
        return 0;
    } else if (player_choice1 == "rock" && player_choice2 == "scissors") {
        return 1;

    } else if (player_choice1 == "paper" && player_choice2 == "rock") {
        return 1;

    }  else if (player_choice1 == "scissors" && player_choice2 == "paper") {
        return 1;

    } else {
        return 0;
    }
    return 0;
}


/**
 * It takes the sum of all wins in Rock, Paper, Scissors category.
 * It then generates the probability of each winning.
 * Using the probability range generated, a random number is generated.
 * The random number is then checked under which range it falls.
 * Then the category corresponding to the range is selected. as the biased random choice.
 * @param freq
 * @return
 */

int GameProtocol :: generate_random_weight(int freq[]) {

    int sum_weights = 0;
    int n = sizeof(freq)/ sizeof(freq[0]) + 1;
    int range[n];
    int i;
    for(i =0; i< n; i++){
        sum_weights += freq[i];
    }

    for(i = 0; i < n; i++){
        range[i] = int((float(freq[i]) / float(sum_weights)) * 100);
        if(i > 0)
            range[i] += range[i -1];
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, range[n - 1]);
    int random_range = dis(gen);
    for(i = 0; i < n; i ++){
        if(random_range < range[i])
            return i;

    }
    return 0;


}

string GameProtocol:: get_weighted_random_choice(int weights[]) {

    string random_choice = options[generate_random_weight(weights)];
    return random_choice;
}

int GameProtocol:: get_index_choice_selected(string choice) {
    if(choice == "rock")
        return 0;
    else if(choice == "paper")
        return 1;
    else if(choice == "scissors")
        return 2;
    return 0;

}

string GameProtocol::generate_current_game_id() {
    time_t seconds;
    time(&seconds);
    stringstream ss;
    ss << seconds;
    string ts = ss.str();
    return ts;
}
