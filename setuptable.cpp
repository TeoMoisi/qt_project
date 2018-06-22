#include "setuptable.h"
#include "ui_setuptable.h"
#include <QSortFilterProxyModel>

setUpTable::setUpTable(Controller* c, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setUpTable),
    _ctrl(c)
{
    ui->setupUi(this);
    this->table = new table_veiw{ this->_ctrl };
    this->setupTableView();
    this->setupPictureTableView();
}

setUpTable::~setUpTable()
{
    delete ui;
}

void setUpTable::setupTableView()
{
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel{};
    proxyModel->setSourceModel(this->table);
    ui->basket->setSortingEnabled(true);

    ui->basket->setModel(proxyModel);

    ui->basket->resizeColumnsToContents();
}

void setUpTable::setupPictureTableView()
{
    ui->picture_view->setModel(this->table);

    ui->picture_view->setItemDelegate(new picture_view{});

    ui->picture_view->resizeColumnsToContents();
    ui->picture_view->resizeRowsToContents();
    //ui->picture_view->verticalHeader()->hide();
}

