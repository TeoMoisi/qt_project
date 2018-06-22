#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QComboBox>
#include "controller.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(Controller &c, QWidget *parent = 0);
    ~admin();
    void init();
    void add();

    void populateList();
    void populate_short();

private:
    Ui::admin *ui;
    Controller& ctrl;
    QListWidget* coats_list;
    QPushButton *add_button, *remove_button, *update_button, *filter_button, *save, *undo;
    QLineEdit *edit_size, *edit_colour, *edit_price, *edit_quantity, *edit_link, *edit_length;
    QComboBox* comboBox;

public slots:
    void addHandler();
    void deleteHandler();
    void updateHandler();
    void filterHandler();
    void save_to_file();
    void undo_handler();
    void redo_handler();
};

#endif // ADMIN_H
