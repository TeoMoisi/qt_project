#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include "controller.h"
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Controller &c, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void admin_mode();
    void user_mode();
    void table_mode();

private:
    Ui::MainWindow *ui;
    Controller& ctrl;
    QPushButton* admin_button;
    QPushButton* user_button;
    QPushButton* table;

};

#endif // MAINWINDOW_H
