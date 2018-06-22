#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admin.h"
#include "user.h"
#include "setuptable.h"

MainWindow::MainWindow(Controller& c, QWidget *parent) :
    ctrl(c), QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->admin_button, &QPushButton::clicked, this, &MainWindow::admin_mode);
    QObject::connect(ui->user_button, &QPushButton::clicked, this, &MainWindow::user_mode);
    QObject::connect(ui->table, &QPushButton::clicked, this, &MainWindow::table_mode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::admin_mode()
{
    admin* a = new admin(this->ctrl);
    a->show();
}

void MainWindow::user_mode()
{
    user* u = new user(this->ctrl);
    u->show();
}

void MainWindow::table_mode()
{
    setUpTable* w = new setUpTable(&this->ctrl);
     w->show();
}



