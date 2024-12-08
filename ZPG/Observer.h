#pragma once

// PRO0366 Tom� Prorok 


#include "Subject.h"

class Subject;

class Observer
{
public:
    virtual void update(Subject* subject) = 0;
};