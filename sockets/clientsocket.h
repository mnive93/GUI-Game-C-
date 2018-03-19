

#ifndef RPSGUI_CLIENTSOCKET_H
#define RPSGUI_CLIENTSOCKET_H
#include <stdio.h>
#include "../ui/gtkui.h"
#include "../pubsub/subject.h"


class ClientSocket: public Subject {
public:
      void create_client_connection();
};
#endif //RPSGUI_CLIENTSOCKET_H
