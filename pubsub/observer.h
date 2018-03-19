
#ifndef RPSGUI_OBSERVER_H
#define RPSGUI_OBSERVER_H

#include<string.h>
#include <iostream>
class Subject;

using namespace std;

class Observer {
public:
    virtual void update (int player, int message_code, string message) = 0;
};
#endif //RPSGUI_OBSERVER_H
