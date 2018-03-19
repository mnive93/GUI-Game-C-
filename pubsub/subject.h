

#ifndef RPSGUI_SUBJECT_H
#define RPSGUI_SUBJECT_H
#include <set>
#include <iostream>
#include <string.h>

using namespace std;
class Observer;

class Subject {
public:
    void subscribe( Observer* );
    void unsubscribe( Observer* );

protected:
    void notify(int player, int message_code, string message);

private:
    typedef std::set< Observer* > Observers;
    Observers observers_;
}; // Subject



#endif //RPSGUI_SUBJECT_H
