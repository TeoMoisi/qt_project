#include "html_file.h"
#include "repository_exceptions.h"

using namespace std;

void HTMLFile::write_to_file()
{
    ofstream f(this->filename);
    char quotes = '"';

    if (!f.is_open())
        throw FileException("The file could not be opened!");

    f << "<!DOCTYPE html>\n";
    f << "<html>\n";
    f << "<head>\n";
    f << "<title>Shopping Basket</title>\n";
    f << "</head>\n";
    f << "<body>\n";
    f << "<table border=" << "1" << ">\n";
    f << "<tr>\n";
    f << "<td>" << "Size" <<"</td>\n";
    f << "<td>" << "Colour" <<"</td>\n";
    f << "<td>" << "Price" <<"</td>\n";
    f << "<td>" << "Quantity" <<"</td>\n";
    f << "<td>" << "Photo Link" <<"</td>\n";
    f << "<td>" << "Length" <<"</td>\n";
    f << "</tr>\n";
    for (auto s : this->_list)
    {
        f << "<tr>\n";
        f << "<td>" << s.getSize() <<"</td>\n";
        f << "<td>" << s.getColour() <<"</td>\n";
        f << "<td>" << s.getPrice() <<"</td>\n";
        f << "<td>" << s.getQuantity() <<"</td>\n";
        f << "<td><a href=" << quotes << s.getPhotograph() << quotes <<">Link</a></td>\n";
        f << "<td>" << s.getLength() <<"</td>\n";
        f << "</tr>\n";
    }

    f << "</table>\n";
    f << "</body>\n";
    f << "</html>\n";

    f.close();
}

void HTMLFile::display_from_file() const
{
    std::string cmd = "open " + this->filename;
    system(cmd.c_str());
}

void HTMLFile::read_from_file()
{
    ifstream file(this->filename);
    if (!file.is_open())
        throw FileException("The file could not be opened!");

    string s, size, color, price, quantity, link, length;
    for (int i = 0; i < 15; i++)
    {
        getline(file, s);
    }

    getline(file, s);
    while (s != "</table>" && !file.eof())
    {
        getline(file, size, '\n');
        size = size.substr(4, size.size() - 9);
        getline(file, color, '\n');
        color = color.substr(4, color.size() - 9);
        getline(file, price, '\n');
        price = price.substr(4, price.size() - 9);
        getline(file, quantity, '\n');
        quantity = quantity.substr(4, quantity.size() - 9);
        getline(file, link, '\n');

        link = link.substr(12, link.size() - 26);
        getline(file, length, '\n');
        length = length.substr(4, length.size() - 9);

        getline(file, s, '\n');
        getline(file, s, '\n');
        Coat c(stoi(size), color, stoi(price), stoi(quantity), link, stoi(length));
        this->_list.push_back(c);
    }
    file.close();
}


