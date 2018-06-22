#ifndef SETUPTABLE_H
#define SETUPTABLE_H

#include <QWidget>
#include "controller.h"
#include "table_veiw.h"
#include "picture_view.h"

namespace Ui {
class setUpTable;
}

class setUpTable : public QWidget
{
    Q_OBJECT

public:
    explicit setUpTable(Controller* c, QWidget *parent = 0);
    ~setUpTable();

public slots:
    void setupTableView();
    void setupPictureTableView();

private:
    Ui::setUpTable *ui;
    Controller* _ctrl;
    table_veiw* table;

};

#endif // SETUPTABLE_H
