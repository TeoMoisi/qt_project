#include "controller.h"
#include "repository_exceptions.h"
using namespace std;

Controller::Controller(Repository &repo, FileBasket* &basket): _repo(repo), _basket(basket)
{
}

void Controller::ctrl_write_to_file()
{
    this->_repo.write_to_file();
}

Controller::~Controller()
{
    while (!undoActions.empty())
        {
            delete undoActions.back();
        }
}

void Controller::addCoat(Coat t)
{
    this->validator.validate(t);
    this->_repo.addCoat(t);
    UndoAction* undo_add = new UndoAdd(this->_repo, t);
    this->undoActions.push_back(undo_add);
}

//if the coat t was found, it is removed
void Controller::removeCoat(Coat t)
{
    this->validator.validate(t);
    this->_repo.removeCoat(t);
    UndoAction* undo_remove = new UndoRemove(this->_repo, t);
    this->undoActions.push_back(undo_remove);
}

//void Controller::updateCoat(Coat t, Coat t_new)
//{
//    this->validator.validate(t);
//    this->validator.validate(t_new);
//    this->_repo.updateCoat(t, t_new);
//}

void Controller::updateCoat(int size, std::string colour, int price, int quantity, std::string Photograph, int length)
{
    Coat c_old = this->_repo.find_By_Colour_Size(colour, size);
    Coat c_new(size, colour, price, quantity, Photograph, length);
    this->validator.validate(c_new);
    this->_repo.updateCoat(size, colour, price, quantity, Photograph, length);
    UndoAction* undo_update = new UndoUpdate(this->_repo, c_old, c_new);
    this->undoActions.push_back(undo_update);
}

vector <Coat> & Controller::getAll()
{
    return this->_repo.getAll();
}

vector<Coat> Controller::getFiltered(int length)
{
    return this->_repo.getFilter(length);
}

void Controller::filterActive(int size)
{
    vector<Coat> all = this->_repo.getAll();
    this->_active.clear();
    this->_pos = 0;
    for(Coat& c: all)
    {
        if(std::to_string(size) == " ")
            this->_active.push_back(c);
        else
            if(c.getSize() == size)
                this->_active.push_back(c);
    }
}

vector<Coat> Controller::getActiveList()
{
    return this->_active;
}

//int Controller::currentpos(Coat c)
//{
//    int j = 0;
//    for (int i = 0; i < this->_active.size(); i++)
//    {
//        if (this->_active[i] == c)
//            j = i;
//    }
//    return j;
//}

Coat Controller::getActiveCoat()
{
    return this->_active[this->_pos];
}

Coat Controller::nextCoat()
{
    this->_pos++;
    if (this->_active.size() == _pos)
        _pos = 0;
    Coat currentCoat = this->getActiveCoat();
    return currentCoat;
}


void Controller::addToBasket(Coat c)
{
    if(this->_basket->findCoat(c) == 0)
        throw DuplicateCoatException();
    this->_basket->addCoat(c);
    UndoBasket* undo_add_basket = new UndoAddBasket(*this->_basket, c);
    this->undoBasket.push_back(undo_add_basket);
}

vector<Coat> & Controller::getBasket()
{
    return this->_basket->getAll();
}

//void Controller::removeFromBasket(Coat c)
//{
//    if(this->_basket->findCoat(c) == 1)
//        throw DoesNotExist();
//    this->_basket->removeCoat(c);
//}

void Controller::removeFromBasket(int size, std::string colour)
{
    if (this->_basket->findByColour_Size(colour, size) == -1)
        throw DoesNotExist();
    std::vector<Coat> all = this->getBasket();
    Coat c = all[this->_basket->findByColour_Size(colour, size)];
    this->_basket->removeCoat(c);
    UndoBasket* undo_remove_basket = new UndoRemoveBasket(*this->_basket, c);
    this->undoBasket.push_back(undo_remove_basket);

}

void Controller::saveBasket()
{
    if (this->_basket == nullptr)
        return;

    this->_basket->write_to_file();
}

void Controller::openBasket() const
{
//    if (this->_basket == nullptr)
//        return;
//
    this->_basket->display_from_file();
}

std::vector<UndoAction*> Controller::return_undo()
{
    return this->undoActions;
}

std::vector<UndoAction*> Controller::return_redo()
{
    return this->redoActions;
}

std::vector<UndoBasket*> Controller::return_undo_basket()
{
    return this->undoBasket;
}

std::vector<UndoBasket*> Controller::return_redo_basket()
{
    return this->redoBasket;
}


void Controller::redo()
{
    redoActions.back()->executeRedo();
    delete redoActions.back();
    redoActions.pop_back();

}


void Controller::undo()
{
    undoActions.back()->executeUndo();
    redoActions.push_back(undoActions.back());
    //delete undoActions.back();
    undoActions.pop_back();
}

void Controller::undo_basket()
{
    undoBasket.back()->executeUndoBasket();
    //delete undoBasket.back();
    redoBasket.push_back(undoBasket.back());
    undoBasket.pop_back();
}


void Controller::redo_basket()
{
    redoBasket.back()->executeRedoBasket();
    delete redoBasket.back();
    redoBasket.pop_back();
}

//void Controller::undo_bag()
//{
//    undoBag.back()->executeUndoBag();
//    delete undoBag.back();
//    undoBag.pop_back();
//}

void Controller::init()
{
    Coat c1(32, "red", 250, 7, "https://ro.pinterest.com/pin/330592428882379838/", 150);
    this->addCoat(c1);

    Coat c2(32, "red", 250, 11, "https://ro.pinterest.com/pin/325877723031145418/", 175);
    this->addCoat(c2);

    Coat c3(36, "grey", 250, 9, "https://ro.pinterest.com/pin/385691155582932812/", 200);
    this->addCoat(c3);

    Coat c4(38, "grey", 250, 12, "https://ro.pinterest.com/pin/786581891142613685/", 180);
    this->addCoat(c4);

    Coat c5(34, "black", 285, 15, "https://ro.pinterest.com/pin/112730796902556958/", 150);
    this->addCoat(c5);

    Coat c6(36, "black", 285, 5, "https://ro.pinterest.com/pin/334181234844356254/", 154);
    this->addCoat(c6);

    Coat c7(38, "black", 285, 7, "https://ro.pinterest.com/pin/472948398360263019/", 190);
    this->addCoat(c7);

    Coat c8(38, "blue", 300, 11, "https://ro.pinterest.com/pin/340795896794626329/", 215);
    this->addCoat(c8);

    Coat c9(40, "blue", 300, 15, "https://ro.pinterest.com/pin/388435536596977576/", 230);
    this->addCoat(c9);

    Coat c10(36, "green", 235, 12, "https://ro.pinterest.com/pin/292100725826174961/", 245);
    this->addCoat(c10);

    Coat c11(38, "green", 235, 9, "https://ro.pinterest.com/pin/198510296059706051/", 270);
    this->addCoat(c11);

    Coat c12(40, "green", 235, 6, "https://ro.pinterest.com/pin/36310340731571686/", 205);
    this->addCoat(c12);

    this->ctrl_write_to_file();

}


