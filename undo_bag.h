#ifndef UNDO_BAG_H
#define UNDO_BAG_H


#include <stdio.h>
#pragma once
#include "domain.h"
#include "repository.h"
#include "controller.h"


    /*
     public:
     Generic class for an undo action.
     For each type of action (add, delete, update), a new class will be created,
     inheriting from this UndoAction.
     */
class UndoBag
{
public:
    virtual void executeUndoBag() = 0;
    // virtual destructor!
    virtual ~UndoBag() {}
};

class UndoAddBag: public UndoBag
{
private:
    Coat addedCoat;
    Controller& ctrl;

public:
    UndoAddBag(Controller& _ctrl, const Coat& s): ctrl{ _ctrl }, addedCoat { s } {}
    virtual void executeUndoBag() override
    {
        this->ctrl.removeFromBasket(addedCoat.getSize(), addedCoat.getColour());
    }
};

#endif // UNDO_BAG_H
