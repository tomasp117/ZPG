#include "Subject.h"

void Subject::addObserver(Observer* observer)
{
    observers.push_back(observer);
}

void Subject::notifyObservers() {
    for (Observer* observer : observers) {
        observer->update();
    }
}
