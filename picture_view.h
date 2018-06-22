#ifndef PICTURE_VIEW_H
#define PICTURE_VIEW_H
#pragma once
#include <QStyledItemDelegate>
#include "repository.h"

class picture_view: public QStyledItemDelegate
{
public:
    picture_view(QWidget *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const override;
};

#endif // PICTURE_VIEW_H
