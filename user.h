#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include "controller.h"
#include "repository_exceptions.h"

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(Controller &c, QWidget *parent = 0);
    ~user();
    void populate();

public slots:
    void filter();
    void remove();
    void save();
    void open();
    void undo_handler();
    void redo_handler();

private:
    Ui::user *ui;
    Controller& ctrl;

    QPushButton* remove_button;
    QPushButton* filter_button;
    QPushButton* save_button;
    QPushButton* open_button;
    QLineEdit* edit_filter;
    QLineEdit* size;
    QLineEdit* colour;
    QListWidget* basket;
    QListWidget* total;
    QPushButton* undo_button;
    QPushButton* redo_button;
};

#endif // USER_H
