#ifndef CONTROLLER_H
#define CONTROLLER_H

#pragma once
#include <stdio.h>
#include "coat_validator.h"
#include "filebasket.h"
#include "undo.h"

class Controller
{
public:
    //Controller(const Repository& r) : _repo(r) {};

    Repository getRepo() const { return _repo; };

    Repository* get_basket() const { return _basket; }

    void ctrl_write_to_file();

    /** Default conscructor */
    Controller(Repository &repo, FileBasket* &basket);
    ~Controller();

    /** Method to add Coat to the Repository*/
    /** If the given element already exists, it returns false, if it doesn't, it is added and the function returns true*/
    void addCoat(Coat c);

    /** Method to remove Coat to the Repository*/
    /** If the element doesn't exist, it returns false, if it does, it is removed from the repository and the dunction returns true*/
    void removeCoat(Coat c);

    /** Method to update an element of type Coat with another one of the same type*/
    /** Returns false if the t_old element does not exist, otherwise, it is updated with the new one and returns true*/
    //void updateCoat(Coat t_old, Coat t_new);
    void updateCoat(int size, std::string colour, int price, int quantity, std::string Photograph, int length);

    /** Method to get all the Coats from repository*/
    std::vector <Coat> &getAll();

    /** Method to get all the filtered coats*/
    std::vector<Coat> getFiltered(int length);

    /** Method to filter all the coats by size*/
    void filterActive(int size);

    /** Method to iterate through the dynamic vector of the filtered coats, in order to play the next link and get the information about the next coat*/
    Coat nextCoat();

    /** Method to reryurn the dynamic vector of the filtered by size coats*/
    std::vector<Coat> getActiveList();

    /** Method to return the current coat.*/
    Coat getActiveCoat();

    /** Method to add the current coat to the shoopimng basket.
     It returns 0 if the coat was not added and 1 otherwise.*/
    void addToBasket(Coat c);

    /** Method to return the dynamic vector of the coats added in the shopping basket*/
    std::vector<Coat> & getBasket();

    /** Method to remove the current coat from the shopping basket.
     It reeturns 0 if the coat was removed and 1 otherwise.*/
    //void removeFromBasket(Coat c);

    void removeFromBasket(int size, std::string colour);

    /** Method to return the position of the current coat.*/
    //int currentpos(Coat c);
    CoatValidator validator;

    void saveBasket();

    void openBasket() const;

    void init();

    std::vector<UndoAction*> return_undo();

    void undo();

    std::vector<UndoAction*> return_redo();

    void redo();

    std::vector<UndoBasket*> return_undo_basket();

    void undo_basket();

    std::vector<UndoBasket*> return_redo_basket();

    void redo_basket();


private:
    Repository _repo;
    FileBasket* _basket;

    std::vector<Coat> _active;
    int _pos;
    std::vector<UndoAction*> undoActions;
    std::vector<UndoAction*> redoActions;
    std::vector<UndoBasket*> undoBasket;
    std::vector<UndoBasket*> redoBasket;
};

#endif // CONTROLLER_H
