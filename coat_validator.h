#ifndef COAT_VALIDATOR_H
#define COAT_VALIDATOR_H

#pragma once
#include <stdio.h>
#include "domain.h"
#include <vector>
#include <string>

class CoatException
{
private:
    std::vector<std::string> errors;

public:
    CoatException(std::vector<std::string> _errors);
    std::vector<std::string> getErrors() const;
};

class CoatValidator
{
public:
    CoatValidator() {}
    static void validate(Coat& s);
    int _read_int(std::string msg);
};


#endif // COAT_VALIDATOR_H
