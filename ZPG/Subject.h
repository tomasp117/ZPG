#pragma once

// PRO0366 Tomáš Prorok 


#include <vector>
#include "Observer.h"

class Observer;

class Subject {
public:

    virtual void addObserver(Observer* observer);

    virtual void removeObserver(Observer* observer);

    virtual void notifyObservers();

private:
    std::vector<Observer*> observers;
};

