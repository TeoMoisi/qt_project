#include "coat_validator.h"
#include "string"


CoatException::CoatException(std::vector<std::string> _errors): errors{_errors}
{
}

std::vector<std::string> CoatException::getErrors() const
{
    return this->errors;
}

void CoatValidator::validate(Coat & c)
{
    std::vector<std::string> errors;
    if (c.getColour().size() < 2)
        errors.push_back("The colour cannot be less than 2 characters!\n");

    if (c.getLength() <= 0)
        errors.push_back(std::string("The length cannot be 0 or negative!\n"));

    if (c.getQuantity() <= 0)
        errors.push_back(std::string("The quantity cannot be 0 or negative!\n"));

    if (c.getSize() <= 0)
        errors.push_back(std::string("The size cannot be 0 or negative!\n"));

    if (c.getPrice() <= 0)
        errors.push_back(std::string("The price cannot be 0 or negative!\n"));

    if (errors.size() > 0)
        throw CoatException(errors);
}

int CoatValidator::_read_int(std::string msg)
{

    std::vector<std::string> errors;
    int value;
    bool been = false;
    do
    {
        if(been == true)
            errors.push_back("The number must be positive!\n");
        if (errors.size() > 0)
            throw CoatException(errors);
        std::cout << msg;
        std::cin >> value;
        while(std::cin.fail())
        {
            errors.push_back("Please input an integer!\n");
            if (errors.size() > 0)
                throw CoatException(errors);
            std::cout << msg;
            std::cin.clear();
            std::cin.ignore(256, '\n');
            std::cin >> value;
        }
        std::cin.ignore();
        been = true;
    } while(value <= 0);
    if (errors.size() > 0)
        throw CoatException(errors);
    else
        return value;
}

