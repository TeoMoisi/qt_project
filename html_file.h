#ifndef HTML_FILE_H
#define HTML_FILE_H


#include <stdio.h>

#include "filebasket.h"
#include <string>

class HTMLFile: public FileBasket
{
public:
    HTMLFile(const std::string& filename) : FileBasket{ filename } { read_from_file(); }

    void write_to_file() override;

    void display_from_file() const override;

    void read_from_file() override;
};

#endif // HTML_FILE_H
