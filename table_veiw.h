#ifndef TABLE_VEIW_H
#define TABLE_VEIW_H
#include <QAbstractTableModel>
#include "controller.h"

class table_veiw: public QAbstractTableModel
{
public:
    table_veiw(Controller* c, QObject* parent = NULL);
    ~table_veiw();
    int rowCount(const QModelIndex &parent = QModelIndex{}) const override;
    int columnCount(const QModelIndex &parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex & index) const override;


private:
    Controller* _ctrl;
};

#endif // TABLE_VEIW_H
