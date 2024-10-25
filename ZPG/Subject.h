#pragma once
#include <vector>
#include "Observer.h"

class Observer;

class Subject {
public:

    virtual void addObserver(Observer* observer);

    virtual void notifyObservers();

private:
    std::vector<Observer*> observers;
};

