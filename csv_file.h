#ifndef CSV_FILE_H
#define CSV_FILE_H


#include <stdio.h>
#pragma once
#include "filebasket.h"
#include <string>

class CSVBasket: public FileBasket
{
public:
    CSVBasket(const std::string& filename) : FileBasket{ filename } { read_from_file(); }

    void write_to_file() override;

    void display_from_file() const override;

    void read_from_file() override;
};

#endif // CSV_FILE_H
