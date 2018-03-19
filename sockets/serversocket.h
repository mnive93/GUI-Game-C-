

#ifndef RPSGUI_SERVERSOCKET_H
#define RPSGUI_SERVERSOCKET_H
#include <stdio.h>
#include "../ui/gtkui.h"
#include "../pubsub/subject.h"

class ServerSocket : public Subject {
public:
     void create_server_connection();
};
#endif //RPSGUI_SERVERSOCKET_H
