

#include "subject.h"


#include <set>
#include "subject.h"
#include "observer.h"


/**
 * Class to implement the Observer pattern. Many subjects subscribes to one particular observer.
 * It then uses the Observer pattern to notify the change to list of observer it has subscribed to.
 * @param newView
 */
void Subject::subscribe (Observer *newView) {
    observers_.insert(newView);
}


void Subject::unsubscribe (Observer *formerView) {
    observers_.erase(formerView);
}


void Subject::notify(int player, int message_code, string message) {
    Observers::iterator i;
    for (i = observers_.begin(); i != observers_.end(); ++i)
        (*i)->update(player, message_code, message);
}