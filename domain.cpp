#include "domain.h"

#include <string.h>
#include "util.h"

Coat::Coat() {
}

Coat::~Coat() {
}

Coat::Coat(int size, std::string colour, int price, int quantity, std::string Photograph, int length)
{
    this->_size = size;
    this->_colour = colour;
    this->_price = price;
    this->_quantity = quantity;
    this->_Photograph = Photograph;
    this->_length = length;
}

//Getters

int Coat::getSize()
{
    return this->_size;
}

int Coat::getLength()
{
    return this->_length;
}

std::string Coat::getColour()
{
    return this->_colour;
}


int Coat::getPrice()
{
    return this->_price;
}

int Coat::getQuantity()
{
    return this->_quantity;
}


std::string Coat::getPhotograph()
{
    return this->_Photograph;
}

//Setters

void Coat::setSize(int size)
{
    this->_size = size;
}

void Coat::setColour(std::string colour)
{
    this->_colour = colour;
}


void Coat::setPrice(int price)
{
    this->_price = price;
}


void Coat::setQuantity(int quantity)
{
    this->_quantity = quantity;
}


void Coat::setPhotograph(std::string Photograph)
{
    this->_Photograph = Photograph;
}

void Coat::setLength(int length)
{
    this->_length = length;
}

bool Coat::operator==(const Coat& c)
{
    if(c._colour == this->_colour && c._size == this->_size && c._quantity== this->_quantity
       && c._price == this->_price && c._Photograph == this->_Photograph)
        return true;
    return false;
}

bool Coat::operator<(const Coat& c)
{
    if(c._length < this->_length)
        return true;
    return false;
}


void Coat::Launch()
{
    std::string cmd = "open " + this->getPhotograph();
    system(cmd.c_str());
}


std::ostream& operator<<(std::ostream& os, const Coat& ct)
{
    os << ct._size << ',' << ct._colour << ',' << ct._price << ',' << ct._quantity << ',' << ct._Photograph << ',' << ct._length;
    return os;
}

std::istream& operator>>(std::istream& ios, Coat& ct)
{
    std::string line;
    std::string token[6];
    getline(ios, line);
    int i = 0;
    std::istringstream reader(line);
    while (i < 6)
    {
        getline(reader, token[i], ',');
        i++;
    }
    ct._size = toInt(token[0]);
    ct._colour = token[1];
    ct._price = toInt(token[2]);
    ct._quantity = toInt(token[3]);
    ct._Photograph = token[4];
    ct._length = toInt(token[5]);
    return ios;
}



