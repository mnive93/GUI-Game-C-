#include <iostream>
#include <unistd.h>
#include "sockets/clientsocket.h"
#include "sockets/serversocket.h"
#include "ui/gtkui.h"
#include "protocol/gameprotocol.h"

using namespace std;

int main(int argc, char **argv)
{

    if (Glib::thread_supported())
        Glib::thread_init();
    else
    {
        cerr << "Threads aren't supported!" << endl;
        exit(1);
    }


    Main kit(argc, argv);
    GtkUI gtkUI;
    Main::run(gtkUI);

    return 0;
}

