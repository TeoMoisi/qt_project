#include "admin.h"
#include "ui_admin.h"
#include "QMessageBox"
#include "repository_exceptions.h"
#include <QShortcut>

admin::admin(Controller& c,QWidget *parent) :
    ctrl(c), QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    init();
    this->populateList();
    this->comboBox->addItem("Detailed");
    this->comboBox->addItem("Short");
    QObject::connect(this->add_button, &QPushButton::clicked, this, &admin::addHandler);
    QObject::connect(this->remove_button, &QPushButton::clicked, this, &admin::deleteHandler);
    QObject::connect(this->update_button, &QPushButton::clicked, this, &admin::updateHandler);
    QObject::connect(this->filter_button, &QPushButton::clicked, this, &admin::filterHandler);
    QObject::connect(ui->undo, &QPushButton::clicked, this, &admin::undo_handler);
    QObject::connect(ui->save, &QPushButton::clicked, this, &admin::save_to_file);

    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    QObject::connect(shortcut, &QShortcut::activated, this, &admin::undo_handler);

    QShortcut *shortcut_new = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    QObject::connect(shortcut_new, &QShortcut::activated, this, &admin::redo_handler);

    QObject::connect(this->comboBox, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
            [=](const QString &text){ if(text == "Detailed") populateList(); else populate_short(); });
}

admin::~admin()
{
    delete ui;
}

void admin::redo_handler()
{
    if (this->ctrl.return_redo().empty())
    {
        std::string s = "There are no redos to do!";
        QMessageBox msgBox;
        QString qstr = QString::fromStdString(s);
        msgBox.setText(qstr);
        msgBox.exec();
        return;
    }
    try
    {
        this->ctrl.redo();
        this->coats_list->clear();
        populateList();
    }
    catch (RepositoryException& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

void admin::undo_handler()
{
    if (this->ctrl.return_undo().empty())
    {
        std::string s = "There are no undos to do!";
        QMessageBox msgBox;
        QString qstr = QString::fromStdString(s);
        msgBox.setText(qstr);
        msgBox.exec();
        return;
    }
    try
    {
        this->ctrl.undo();
        this->coats_list->clear();
        populateList();
    }
    catch (RepositoryException& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }

}

void admin::save_to_file()
{
    this->ctrl.ctrl_write_to_file();
}

void admin::init()
{

    QHBoxLayout* mainLayout = new QHBoxLayout {this};
    QVBoxLayout* leftLayout = new QVBoxLayout{};
    QVBoxLayout* rightLayout = new QVBoxLayout{};

    this->coats_list = new QListWidget{};

    QLabel* all_coats = new QLabel{" Size | Colour | Price | Quantity | Link | Length |"};

    this->comboBox = new QComboBox{};
    leftLayout->addWidget(comboBox);

    leftLayout->addWidget(all_coats);
    leftLayout->addWidget(coats_list);

    QHBoxLayout* bottomLayout = new QHBoxLayout{};
    QVBoxLayout* labelsLayout = new QVBoxLayout{};
    QVBoxLayout* editLayout = new QVBoxLayout{};
    QHBoxLayout* filterLayout = new QHBoxLayout{};
    QHBoxLayout* buttonsLayout = new QHBoxLayout{};

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

    this-> add_button = new QPushButton{"Add"};
    this-> remove_button = new QPushButton{"Remove"};
    this->update_button = new QPushButton{"Update"};
    this->filter_button = new QPushButton{"Filter"};

    filterLayout->addWidget(filter_button);

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

    buttonsLayout->addWidget(add_button);
    buttonsLayout->addWidget(remove_button);
    buttonsLayout->addWidget(update_button);

    leftLayout->addLayout(buttonsLayout);
    leftLayout->addLayout(filterLayout);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

}

void admin::populateList()
{
    this->coats_list->clear();
    std::vector<Coat> coats= this->ctrl.getAll();

    if (coats.size() == 0)
            {
                std::string s = "There are no coats in the repository!";
                QMessageBox msgBox;
                QString qstr = QString::fromStdString(s);
                msgBox.setText(qstr);
                msgBox.exec();
                return;
            }

    for (auto c: coats)
    {
           std::string sir = "";
           sir += std::to_string(c.getSize()) + " | " + c.getColour() + " | " +std::to_string(c.getPrice()) + " | " + std::to_string(c.getQuantity()) + " | " + c.getPhotograph() + " | " + std::to_string(c.getLength());
           this->coats_list->addItem(QString::fromStdString(sir));
           this->coats_list->item(0)->setBackgroundColor(Qt::red);
    }
}

void admin::populate_short()
{
    this->coats_list->clear();
    std::vector<Coat> coats= this->ctrl.getAll();

    if (coats.size() == 0)
            {
                std::string s = "There are no coats in the repository!";
                QMessageBox msgBox;
                QString qstr = QString::fromStdString(s);
                msgBox.setText(qstr);
                msgBox.exec();
                return;
            }

    for (auto c: coats)
    {
           std::string sir = "";
           sir += std::to_string(c.getSize()) + " | " + c.getColour() + " | " +std::to_string(c.getPrice());
           this->coats_list->addItem(QString::fromStdString(sir));
    }
}


void admin::addHandler()
{
    QString size = this->edit_size->text();
    QString colour = this->edit_colour->text();
    QString price = this->edit_price->text();
    QString quantity = this->edit_quantity->text();
    QString link = this->edit_link->text();
    QString length = this->edit_length->text();

    try
    {
    Coat c(size.toInt(), colour.toStdString(), price.toInt(), quantity.toInt(), link.toStdString(), length.toInt());
    this->ctrl.addCoat(c);
    //this->ctrl.ctrl_write_to_file();
    populateList();
    }
    catch (CoatException& e)
    {
        for (auto s: e.getErrors())
        {
            QMessageBox msgBox;
            QString qstr = QString::fromStdString(s);
            msgBox.setText(qstr);
            msgBox.exec();
        }
    }
    catch (RepositoryException& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }


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

    try
    {
    Coat c(size.toInt(), colour.toStdString(), price.toInt(), quantity.toInt(), link.toStdString(), length.toInt());
    this->ctrl.removeCoat(c);
    //this->ctrl.ctrl_write_to_file();
    populateList();
    }
    catch (CoatException& e)
    {
        for (auto s: e.getErrors())
        {
            QMessageBox msgBox;
            QString qstr = QString::fromStdString(s);
            msgBox.setText(qstr);
            msgBox.exec();
        }
    }
    catch (RepositoryException& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }

    this->edit_size->clear();
    this->edit_colour->clear();
    this->edit_price->clear();
    this->edit_quantity->clear();
    this->edit_link->clear();
    this->edit_length->clear();
}

void admin::updateHandler()
{
    QString size = this->edit_size->text();
    QString colour = this->edit_colour->text();
    QString price = this->edit_price->text();
    QString quantity = this->edit_quantity->text();
    QString link = this->edit_link->text();
    QString length = this->edit_length->text();

    try
    {
        this->ctrl.updateCoat(size.toInt(), colour.toStdString(), price.toInt(), quantity.toInt(), link.toStdString(), length.toInt());
        //this->ctrl.ctrl_write_to_file();
        populateList();
    }
    catch (CoatException& e)
    {
        for (auto s: e.getErrors())
        {
            QMessageBox msgBox;
            QString qstr = QString::fromStdString(s);
            msgBox.setText(qstr);
            msgBox.exec();
        }
    }
    catch (RepositoryException& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }

    this->edit_size->clear();
    this->edit_colour->clear();
    this->edit_price->clear();
    this->edit_quantity->clear();
    this->edit_link->clear();
    this->edit_length->clear();


}

void admin::filterHandler()
{
    QString length = this->edit_length->text();
    std::vector<Coat> all = this->ctrl.getFiltered(length.toInt());
    if (all.size() == 0)
    {
        std::string s = "No coats with less than the given length!";
        QMessageBox msgBox;
        QString qstr = QString::fromStdString(s);
        msgBox.setText(qstr);
        msgBox.exec();
        return;
    }
    this->coats_list->clear();
    for (auto c: all)
    {
           std::string sir = "";
           sir += std::to_string(c.getSize()) + " | " + c.getColour() + " | " +std::to_string(c.getPrice()) + " | " + std::to_string(c.getQuantity()) + " | " + c.getPhotograph() + " | " + std::to_string(c.getLength());
           this->coats_list->addItem(QString::fromStdString(sir));
    }
    this->edit_length->clear();

}
