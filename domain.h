#ifndef DOMAIN_H
#define DOMAIN_H
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


class Coat
{
public:

    //default constructor
    Coat();

    //constructor for object Coat, having as properties: size, colou, price, quantity and photograph(link)
    Coat(int size, std::string colour, int price, int quantity, std::string Photograph, int length);

    //default destructor
    ~Coat();

    //size getter
    int getSize();

    int getLength();

    //colour getter
    std::string getColour();

    //price getter
    int getPrice();

    //quantity getter
    int getQuantity();

    //photograph_link getter
    std::string getPhotograph();

    //size setter
    void setSize(int size);

    //colour setter
    void setColour(std::string colour);

    //price setter
    void setPrice(int price);

    //photograph_link setter
    void setPhotograph(std::string Photograph);

    //quantity setter
    void setQuantity(int quantity);

    void setLength(int length);

    //
    //static Coat fromstring(std::string aux);

    //returns true if two objects are equal and false otherwise
    bool operator==(const Coat& c);

    bool operator<(const Coat& c);

    /** Method to play the link of the coat's photograph.*/
    void Launch();

    friend std::ostream& operator<<(std::ostream& os, const Coat& ct);
    friend std::istream& operator>>(std::istream& is, Coat& ct);

private:
    std::string _colour, _Photograph;
    int _size;
    int _price;
    int _quantity;
    int _length;

};




#endif // DOMAIN_H
