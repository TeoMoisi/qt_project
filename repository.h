#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <stdio.h>
#pragma once
#include "domain.h"
#include <cstring>

class Repository
{
protected:
    std::vector <Coat> _list;
    std::string file_name;


public:

    /** Default constructor */
    Repository();
    Repository(const std::string& filename);

    void read_from_file();
    void write_to_file();

    //function to add an element of type Coat
    void addCoat(Coat t);

    //function to remove an element of type Coat
    void removeCoat(Coat t);

    //function to update a given element t of type Coat, with a new one, of the same type
    //void updateCoat(Coat t, Coat t_new);

    void updateCoat(int size, std::string colour, int price, int quantity, std::string Photograph, int length);

    //function to return all the element from the dynamic vector
    std::vector <Coat>& getAll();

    //this function receives as parameter an element of type Coat, return 0 if it was found and 1 otherwise
    int findCoat(Coat t);

    //this function compares two given elements of the same type, returns 0 if they are equal and 0 otherwise
    int eq_coat(Coat c1, Coat c2);

    //this function receives the colour of an element of type Coat and returns the element/s
    Coat findByColour(const std::string& colour);

    //returns all the Coats
    std::vector<Coat> getCoats() const { return _list; };

    /** Method to filter all the coats by colous*/
    std::vector<Coat> getFilter(int length);

    /** Method to sort ascending the filtered coats*/
    //vector<Coat> sortDynVec(vector<Coat> res);

    int findByColour_Size(std::string colour, int size);

    Coat find_By_Colour_Size(std::string colour, int size);
};

std::vector <Coat> operator + (const std::vector <Coat> &a, const Coat &b);
std::vector <Coat> operator + (const Coat &b, const std::vector <Coat> &a);
std::vector <Coat> operator - (const std::vector <Coat> &a, const Coat &b);

#endif // REPOSITORY_H
