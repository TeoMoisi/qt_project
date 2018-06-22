#include "mainwindow.h"
#include <QApplication>
#include "csv_file.h"
#include "html_file.h"
#include "repository_exceptions.h"
#include <QMessageBox>
#include "QInputDialog"
#include "setuptable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try
    {
    Repository repo("/Users/teofanamoisi/Desktop/qt_lab/coats.txt");
    FileBasket* basket;
    QWidget* wg = new QWidget{};
    QString text = QInputDialog::getText(wg, "Basket", "What file do you prefer for your basket? CSV or HTML");
    if(text.toStdString() == "csv")
        basket = new CSVBasket("/Users/teofanamoisi/Desktop/qt_lab/coats.csv");
    else
        basket = new HTMLFile("/Users/teofanamoisi/Desktop/qt_lab/coats.html");
    Controller ctrl(repo, basket);
    //ctrl.init();
    MainWindow window(ctrl);
    window.show();
    //setUpTable w{ &ctrl };
    //w.show();
    //delete basket;
    return a.exec();
    }
    catch (FileException&)
    {
            std::string s = "Repository file could not be opened! The application will terminate.";
            QMessageBox msgBox;
            QString qstr = QString::fromStdString(s);
            msgBox.setText(qstr);
            msgBox.exec();
            return 1;
     }
}
