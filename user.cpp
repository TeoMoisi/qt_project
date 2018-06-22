#include "user.h"
#include "ui_user.h"
#include <QMessageBox>
#include <QInputDialog>


user::user(Controller& c, QWidget *parent) :
    ctrl(c), QWidget(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    QObject::connect(this->ui->filter_button, &QPushButton::clicked, this, &user::filter);
    QObject::connect(this->ui->remove_button, &QPushButton::clicked, this, &user::remove);
    QObject::connect(this->ui->save_button, &QPushButton::clicked, this, &user::save);
    QObject::connect(this->ui->open_button, &QPushButton::clicked, this, &user::open);
    QObject::connect(this->ui->undo_button, &QPushButton::clicked, this, &user::undo_handler);
    QObject::connect(this->ui->redo_button, &QPushButton::clicked, this, &user::redo_handler);

}

user::~user()
{
    delete ui;
}

void user::undo_handler()
{
    if (this->ctrl.return_undo_basket().empty())
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
        this->ctrl.undo_basket();
        this->ui->basket->clear();
        populate();
    }
    catch (RepositoryException& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }

}

void user::redo_handler()
{
    if (this->ctrl.return_redo_basket().empty())
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
        this->ctrl.redo_basket();
        this->ui->basket->clear();
        populate();
    }
    catch (RepositoryException& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }

}


void user::populate()
{
    this->ui->basket->clear();
    std::vector<Coat> all = this->ctrl.getBasket();

    int suma = 0;
    for (Coat& c: all)
    {
        suma += c.getPrice();
    }
    for (auto c: all)
    {
           std::string sir = "";
           sir += std::to_string(c.getSize()) + " | " + c.getColour() + " | " +std::to_string(c.getPrice()) + " | " + std::to_string(c.getQuantity()) + " | " + c.getPhotograph() + " | " + std::to_string(c.getLength());
           this->ui->basket->addItem(QString::fromStdString(sir));
    }
    this->ui->total->addItem(QString::fromStdString(std::to_string(suma)));
}

void user::filter()
{
    QString size = this->ui->edit_filter->text();
    this->ctrl.filterActive(size.toInt());
    std::vector<Coat> all = this->ctrl.getActiveList();
    if (all.size() == 0)
    {
        std::string s = "There are no coats in the repository!";
        QMessageBox msgBox;
        QString qstr = QString::fromStdString(s);
        msgBox.setText(qstr);
        msgBox.exec();
        return;
    }
    QString text = "yes";
        while(text.toStdString() == "yes")
        {
            //Coat c = all[i];
            Coat c = this->ctrl.getActiveCoat();
            c.Launch();
            std::string s = "";
            s += "Current coat: " + std::to_string(c.getSize()) + " - " + c.getColour() + " - " + std::to_string(c.getPrice()) + " - " + std::to_string(c.getQuantity()) + " - " + std::to_string(c.getLength());
            QMessageBox msgBox;
            QString qstr = QString::fromStdString(s);
            msgBox.setText(qstr);
            msgBox.exec();
            QWidget* wg = new QWidget{};
            text = QInputDialog::getText(wg, "Basket", "Do you want to add this coat to your basket?");
            if(text.toStdString() == "yes")
            {
                try
                {
                    this->ctrl.addToBasket(c);
                    populate();
                }
                catch (RepositoryException& e)
                {
                    QMessageBox msgBox;
                    msgBox.setText(e.what());
                    msgBox.exec();
                }
            }
            wg = new QWidget{};
            text = QInputDialog::getText(wg, "Basket", "Do you want to see the next coat?");
            if(text.toStdString() == "yes")
            {
                this->ctrl.nextCoat();
            }
        }
        this->ui->edit_filter->clear();
}

void user::remove()
{
    QString size = this->ui->size->text();
    QString colour = this->ui->colour->text();
    try
    {
        this->ctrl.removeFromBasket(size.toInt(), colour.toStdString());
        populate();
    }
    catch (RepositoryException& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
    this->ui->size->clear();
    this->ui->colour->clear();
}

void user::save()
{
    try
    {
        this->ctrl.saveBasket();

        if (this->ctrl.get_basket() == nullptr)
        {
            std::string s = "Basket can not be saved!";
            QMessageBox msgBox;
            QString qstr = QString::fromStdString(s);
            msgBox.setText(qstr);
            msgBox.exec();
            return;
        }

    }
    catch (FileException& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

void user::open()
{
    this->ctrl.openBasket();
}




