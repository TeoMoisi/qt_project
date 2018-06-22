#include "ui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>


void admin::init()
{

    QHBoxLayout* mainLayout = new QHBoxLayout {this};
    QVBoxLayout* leftLayout = new QVBoxLayout{};
    QVBoxLayout* rightLayout = new QVBoxLayout{};

    this->widget_List = new QListWidget{};

    QLabel* all_coats = new QLabel{" Size | Colour | Price | Quantity | Link | Length |"};

    leftLayout->addWidget(all_coats);
    leftLayout->addWidget(widget_List);

    QHBoxLayout* bottomLayout = new QHBoxLayout{};
    QVBoxLayout* labelsLayout = new QVBoxLayout{};
    QVBoxLayout* editLayout = new QVBoxLayout{};

    QLabel* label_size = new QLabel{"Size"};
    this-> edit_size = new QLineEdit{};

    QLabel* label_colour= new QLabel{"Colour"};
    this-> edit_colour = new QLineEdit{};

    QLabel* label_price= new QLabel{"Price"};
    this-> edit_price = new QLineEdit{};

    QLabel* label_quantity = new QLabel{"Quantity"};
    this-> edit_quantity = new QLineEdit{};

    QLabel* label_link = new QLabel{"Photo link"};
    this-> edit_link = new QLineEdit{};

    QLabel* label_length = new QLabel{"Length"};
    this-> edit_length = new QLineEdit{};

    labelsLayout->addWidget(label_size);
    labelsLayout->addWidget(label_colour);
    labelsLayout->addWidget(label_price);
    labelsLayout->addWidget(label_quantity);
    labelsLayout->addWidget(label_link);
    labelsLayout->addWidget(label_length);

    editLayout->addWidget(edit_size);
    editLayout->addWidget(edit_colour);
    editLayout->addWidget(edit_price);
    editLayout->addWidget(edit_quantity);
    editLayout->addWidget(edit_link);
    editLayout->addWidget(edit_length);


    bottomLayout->addLayout(labelsLayout);
    bottomLayout->addLayout(editLayout);

    leftLayout->addLayout(bottomLayout);

    QHBoxLayout* buttonsLayout = new QHBoxLayout{};


    this-> add_button = new QPushButton{"Add"};
    this-> remove_button = new QPushButton{"Remove"};
    QPushButton* update_button = new QPushButton{"Update"};


    buttonsLayout->addWidget(add_button);
    buttonsLayout->addWidget(remove_button);
    buttonsLayout->addWidget(update_button);

    QHBoxLayout* filterLayout = new QHBoxLayout{};

    QPushButton* filter_button = new QPushButton{"Filter"};

    filterLayout->addWidget(filter_button);

    leftLayout->addLayout(buttonsLayout);
    leftLayout->addLayout(filterLayout);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

}

void admin::populateList()
{
    this->widget_List->clear();
    std::vector<Coat> coats= this -> controller.getAll();

    for (auto c: coats)
    {
           std::string sir = "";
           sir += std::to_string(c.getSize()) + " | " + c.getColour() + " | " +std::to_string(c.getPrice()) + " | " + std::to_string(c.getQuantity()) + " | " + c.getPhotograph() + " | " + std::to_string(c.getLength());
           this->widget_List->addItem(QString::fromStdString(sir));
    }
}

admin::admin(Controller &ctrl): controller{ctrl}
{
    init();

    this->populateList();

    QObject::connect(this->add_button, &QPushButton::clicked, this, &Admin::addHandler);
    QObject::connect(this->remove_button, &QPushButton::clicked, this, &Admin::deleteHandler);
    QObject::connect(this->update_button, &QPushButton::clicked, this, &Admin::updateHandler);
}

void admin::addHandler()
{
    QString size = this->edit_size->text();
    QString colour = this->edit_colour->text();
    QString price = this->edit_price->text();
    QString quantity = this->edit_quantity->text();
    QString link = this->edit_link->text();
    QString length = this->edit_length->text();

    Coat c(size.toInt(), colour.toStdString(), price.toInt(), quantity.toInt(), link.toStdString(), length.toInt());
    this->controller.addCoat(c);
    populateList();

    this->edit_size->clear();
    this->edit_colour->clear();
    this->edit_price->clear();
    this->edit_quantity->clear();
    this->edit_link->clear();
    this->edit_length->clear();
}

void admin::deleteHandler()
{
    QString size = this->edit_size->text();
    QString colour = this->edit_colour->text();
    QString price = this->edit_price->text();
    QString quantity = this->edit_quantity->text();
    QString link = this->edit_link->text();
    QString length = this->edit_length->text();

    Coat c(size.toInt(), colour.toStdString(), price.toInt(), quantity.toInt(), link.toStdString(), length.toInt());
    this->controller.removeCoat(c);
    populateList();
}


void admin::updateHandler()
{}


