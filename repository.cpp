#include "repository.h"
#include <algorithm>
#include <fstream>
#include <cassert>
#include <string.h>
#include "repository_exceptions.h"
using namespace std;

Repository::Repository()
{
}

Repository::Repository(const std::string& file_name)
{
    this->file_name = file_name;
    this->read_from_file();
}

void Repository::read_from_file()
{
    ifstream file(this->file_name);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    Coat c;
    while (file >> c)
        this->_list.push_back(c);

    file.close();

}


void Repository::write_to_file()
{
    ofstream file(this->file_name);
    if (!file.is_open())
        throw FileException("The file could not be opened!");
    for (auto c : this->_list)
    {
        file << c << " \n";
    }

    file.close();
}

void Repository::addCoat(Coat t)
{
    if (this->findCoat(t) == 0)
        throw DuplicateCoatException();
    this->_list.push_back(t);
}

void Repository::removeCoat(Coat t)
{
    if (this->findCoat(t) != 0)
        throw DoesNotExist();
    this->_list.erase(find(this->_list.begin(), this->_list.end(), t));
}

int Repository::eq_coat(Coat c1, Coat c2)
{
    if(c1.getColour() == c2.getColour() && c1.getSize() == c2.getSize() && c1.getLength() == c2.getLength())
        return 0;
    return 1;
}

//void Repository::updateCoat(Coat t, Coat t_new)
//{
//    if (this->findCoat(t) != 0)
//        throw DoesNotExist();
//    if (this->findCoat(t_new) == 0)
//        throw DuplicateCoatException();
//    auto it = find(this->_list.begin(), this->_list.end(), t);
//    replace(it, it + 1, t, t_new);
//}

void Repository::updateCoat(int size, std::string colour, int price, int quantity, std::string Photograph, int length)
{
    if (this->findByColour_Size(colour, size) == -1)
        throw DoesNotExist();
    Coat c_new(size, colour, price, quantity, Photograph, length);
    if (this->findCoat(c_new) == 0)
        throw DuplicateCoatException();
    this->_list[findByColour_Size(colour, size)] = c_new;
}

vector<Coat> &Repository::getAll()
{
    return this->_list;
}


vector<Coat> Repository::getFilter(int length)
{
    vector <Coat> res;
    copy_if(this->_list.begin(), this->_list.end(), back_inserter(res), [length](Coat c) {return c.getLength() < length;});
    return res;
}



//returns 0 if the coat t already exists and 1 otherwise
int Repository::findCoat(Coat t)
{

    for(Coat& c: this->_list)
        if(eq_coat(c, t) == 0)
            return 0;
        return 1;
}

Coat Repository::findByColour(const std::string& colour)
{
    for (Coat& c: this->_list)
    {
        if (c.getColour() == colour)
            return c;
    }
    Coat c;
    return c;
}

Coat Repository::find_By_Colour_Size(std::string colour, int size)
{
    for (auto c: this->_list)
    {
        if (c.getColour() == colour && c.getSize() == size)
            return c;
    }
    Coat c;
    return c;

}

int Repository::findByColour_Size(std::string colour, int size)
{
    int i = 0;
    for (auto c: this->_list)
    {
        if (c.getColour() == colour && c.getSize() == size)
            return i;
        i++;
    }
    return -1;

}


