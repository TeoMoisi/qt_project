#ifndef FILEBASKET_H
#define FILEBASKET_H

#pragma once
#include "repository.h"

class FileBasket : public Repository
{
protected:
    std::string filename;

public:
    FileBasket(const std::string& filename);
    virtual ~FileBasket() {}

    virtual void display_from_file() const = 0;
    virtual void write_to_file() = 0;
    virtual void read_from_file() = 0;
};

#endif // FILEBASKET_H
