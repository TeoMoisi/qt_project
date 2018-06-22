#ifndef UNDO_H
#define UNDO_H

#include <stdio.h>
#pragma once
#include "domain.h"
#include "repository.h"
#include "filebasket.h"
    /*
     public:
     Generic class for an undo action.
     For each type of action (add, delete, update), a new class will be created,
     inheriting from this UndoAction.
     */
class UndoAction
{
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
    // virtual destructor!
    virtual ~UndoAction() {}
};

class UndoAdd: public UndoAction
{
private:
    Coat addedCoat;
    Repository& repo;
public:
    UndoAdd(Repository& _repo, const Coat& s): repo{ _repo }, addedCoat { s } {}
    virtual void executeUndo() override
    {
        this->repo.removeCoat(addedCoat);
    }
    virtual void executeRedo() override
    {
        this->repo.addCoat(addedCoat);
    }
};

class UndoRemove: public UndoAction
{
private:
    Coat removedCoat;
    Repository& repo;
public:
    UndoRemove(Repository& _repo, const Coat& s): repo{ _repo }, removedCoat { s } {}
    virtual void executeUndo() override
    {
        this->repo.addCoat(removedCoat);
    }
    virtual void executeRedo() override
    {
        this->repo.removeCoat(removedCoat);
    }
};

class UndoUpdate: public UndoAction
{
private:
    Coat oldCoat, newCoat;
    Repository& repo;
public:
    UndoUpdate(Repository& _repo, const Coat& c1, const Coat& c2): repo{ _repo }, oldCoat { c1 }, newCoat { c2 } {}
    virtual void executeUndo() override
    {
        this->repo.updateCoat(oldCoat.getSize(), oldCoat.getColour(), oldCoat.getPrice(), oldCoat.getQuantity(), oldCoat.getPhotograph(), oldCoat.getLength());
    }
    virtual void executeRedo() override
    {
        this->repo.updateCoat(newCoat.getSize(), newCoat.getColour(), newCoat.getPrice(), newCoat.getQuantity(), newCoat.getPhotograph(), newCoat.getLength());
    }

};


class UndoBasket
{
public:
    virtual void executeUndoBasket() = 0;
    virtual void executeRedoBasket() = 0;
    // virtual destructor!
    virtual ~UndoBasket() {}
};

class UndoAddBasket: public UndoBasket
{
private:
    Coat addedCoat;
    FileBasket& basket;
public:
    UndoAddBasket(FileBasket& _basket, const Coat& s): basket{ _basket }, addedCoat { s } {}
    virtual void executeUndoBasket() override
    {
        this->basket.removeCoat(addedCoat);
    }
    virtual void executeRedoBasket() override
    {
        this->basket.addCoat(addedCoat);
    }
};

class UndoRemoveBasket: public UndoBasket
{
public:
    Coat removedCoat;
    FileBasket& basket;

public:
    UndoRemoveBasket(FileBasket& _basket, const Coat& s): basket{ _basket }, removedCoat { s } {}
    virtual void executeUndoBasket() override
    {
        this->basket.addCoat(removedCoat);
    }
    virtual void executeRedoBasket() override
    {
        this->basket.removeCoat(removedCoat);
    }
};


#endif // UNDO_H
