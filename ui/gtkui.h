

#ifndef RPSGUI_GTKUI_H
#define RPSGUI_GTKUI_H
#include <gtkmm.h>
#include <string.h>
#include "../pubsub/observer.h"
#include "../database/db.h"

using namespace Gtk;
using namespace std;
class GtkUI : public Window, public Observer {
private:

    VBox vBoxMain;
    HBox hBoxplayers;
    VBox player1;
    VBox player2;
    Label player1_label;
    Label player2_label;
    Label round_label;
    Label status_player1;
    Label status_player2;
    Label score_player1;
    Label score_player2;
    Button start_game;

public:
    GtkUI();
    void update_player1_status(string status);
    void update_player2_status(string status);
    void update_score_player1(string score);
    void update_score_player2(string score);
    void startGame();
    void startClient();

    void startServer();
    virtual void update(int player, int message_code, string message);

};




#endif //RPSGUI_GTKUI_H
