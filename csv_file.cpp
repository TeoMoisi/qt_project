#include "csv_file.h"
#include "repository_exceptions.h"

using namespace std;

void CSVBasket::write_to_file()
{
    ofstream f(this->filename);

    if (!f.is_open())
        throw FileException("The file could not be opened!");

    for (auto s : this->_list)
        f << s << "\n";

    f.close();
}

void CSVBasket::display_from_file() const
{
    //std::string name = "/Users/teofanamoisi/Desktop/OOP/lab5-6-finalcopy/lab5-6/basket.csv";
    std::string cmd = "open " + this->filename;
    system(cmd.c_str());
}

void CSVBasket::read_from_file()
{
    ifstream file(this->filename);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    Coat c;
    while (file >> c)
        this->_list.push_back(c);

    file.close();
}


