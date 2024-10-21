#pragma once
#include <vector>
#include "Observer.h"

class Observer;

class Subject {
public:

    void addObserver(Observer* observer);

    void notifyObservers();

private:
    std::vector<Observer*> observers;
};

