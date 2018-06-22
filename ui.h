#ifndef UI_H
#define UI_H

#pragma once
#include <QWidget>
#include <vector>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "controller.h"


namespace Ui {
class Admin;
}

class Admin : public QWidget
{

    Q_OBJECT

private:
    Ui::Admin *ui;
    Controller& controller;
    QListWidget* widget_List;
    QPushButton * add_button, * remove_button, * update_button;
    QLineEdit* edit_size, *edit_colour, *edit_price, *edit_quantity, *edit_link, *edit_length;

public:
    explicit Admin(Controller & c, QWidget *parent = 0);
    ~Admin();
    void init();
    void add();

    void populateList();

public slots:
    void addHandler();
    void deleteHandler();
    void updateHandler();
};

#endif // UI_H
