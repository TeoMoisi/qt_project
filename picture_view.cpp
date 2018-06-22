#include "picture_view.h"
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
picture_view::picture_view(QWidget *parent) : QStyledItemDelegate{ parent }
{

}


void picture_view::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QString coat = index.model()->data(index, Qt::EditRole).toString();

    if (index.column() != 4)
    {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    if (coat.contains("https://ro.pinterest.com/pin/330592428882379838/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat1.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/325877723031145418/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat2.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/385691155582932812/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat3.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/786581891142613685/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat4.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/112730796902556958/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat5.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/334181234844356254/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat6.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/472948398360263019/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat7.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/340795896794626329/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat8.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/388435536596977576/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat9.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/292100725826174961/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat10.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/198510296059706051/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat11.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("https://ro.pinterest.com/pin/36310340731571686/"))
    {
        QPixmap pixMap("/Users/teofanamoisi/Desktop/qt_lab/coat12.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
}

QSize picture_view::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (index.column() == 4)
    {
        return QSize(100, 100);
    }

    return QStyledItemDelegate::sizeHint(option, index);
}



