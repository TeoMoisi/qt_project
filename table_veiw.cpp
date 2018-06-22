#include "table_veiw.h"
#include <QFont>
#include <QBrush>

table_veiw::table_veiw(Controller* c, QObject* parent) : QAbstractTableModel { parent }, _ctrl{ c }
{

}

table_veiw::~table_veiw()
{}

int table_veiw::rowCount(const QModelIndex & parent) const
{
    int number = this->_ctrl->getBasket().size() + 1;
    return number;
}

int table_veiw::columnCount(const QModelIndex & parent) const
{
    return 6;
}

QVariant table_veiw::data(const QModelIndex & index, int role) const
{
    int row = index.row();
    int column = index.column();

    std::vector<Coat> coats = this->_ctrl->getBasket();

    if (row == coats.size())
    {
        return QVariant();
    }

    Coat c = coats[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return QString::fromStdString(std::to_string(c.getSize()));
        case 1:
            return QString::fromStdString(c.getColour());
        case 2:
            return QString::fromStdString(std::to_string(c.getPrice()));
        case 3:
            return QString::fromStdString(std::to_string(c.getQuantity()));
        case 4:
            return QString::fromStdString(c.getPhotograph());
        case 5:
            return QString::fromStdString(std::to_string(c.getLength()));
        default:
            break;
        }
    }
    if (role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        font.setItalic(false);
        return font;
    }
    if (role == Qt::BackgroundRole)
    {
        if (row % 2 == 1)
        {
            return QBrush{ QColor{0, 150, 200} };
        }
        else
        {
            return QBrush{ QColor{0, 190, 190}};
        }
    }

    return QVariant{};
}

QVariant table_veiw::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString{ "Size" };
            case 1:
                return QString{ "Colour" };
            case 2:
                return QString{ "Price" };
            case 3:
                return QString{ "Quantity" };
            case 4:
                return QString{ "Photo link" };
            case 5:
                return QString{ "Length" };
            default:
                break;
            }
        }
    }
    if (role == Qt::FontRole)
    {
        QFont font("Times", 15, 10, true);
        font.setBold(true);
        font.setItalic(false);
        return font;
    }

    return QVariant{};
}

bool table_veiw::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    int CoatIndex = index.row();

    std::vector<Coat> coats = this->_ctrl->getBasket();

    if (CoatIndex == coats.size())
    {
        this->beginInsertRows(QModelIndex{}, CoatIndex, CoatIndex);
        QString quotes = "";
        switch (index.column())
        {
        case 0:
            this->_ctrl->addToBasket(Coat{value.toInt(), quotes.toStdString(), quotes.toInt() , quotes.toInt(), quotes.toStdString(), quotes.toInt() });
            break;
        case 1:
            this->_ctrl->addToBasket(Coat( quotes.toInt(), value.toString().toStdString(), quotes.toInt(), quotes.toInt(), quotes.toStdString(), quotes.toInt() ));
            break;
        case 2:
            this->_ctrl->addToBasket(Coat{ quotes.toInt(), quotes.toStdString(), value.toInt(), quotes.toInt(), quotes.toStdString(), quotes.toInt() });
            break;
        case 3:
            this->_ctrl->addToBasket(Coat{ quotes.toInt(), quotes.toStdString(), quotes.toInt(), value.toInt(), quotes.toStdString(), quotes.toInt() });
            break;
        case 4:
            this->_ctrl->addToBasket(Coat{ quotes.toInt(), quotes.toStdString(), quotes.toInt(), quotes.toInt(), value.toString().toStdString(), quotes.toInt() });
            break;
        case 5:
            this->_ctrl->addToBasket(Coat( quotes.toInt(), quotes.toStdString(), quotes.toInt() , quotes.toInt() , quotes.toStdString(), value.toInt() ));
            break;
        }

        this->endInsertRows();
        return true;
    }

    Coat& currentCoat = coats[CoatIndex];
    switch (index.column())
    {
    case 0:
        currentCoat.setSize(value.toInt());
        break;
    case 1:
        currentCoat.setColour(value.toString().toStdString());
        break;
    case 2:
        currentCoat.setPrice(value.toInt());
    case 3:
        currentCoat.setQuantity(value.toInt());
        break;
    case 4:
        currentCoat.setPhotograph(value.toString().toStdString());
        break;
    case 5:
        currentCoat.setLength(value.toInt());
    }
    this->_ctrl->updateCoat(currentCoat.getSize(), currentCoat.getColour(), currentCoat.getPrice(), currentCoat.getQuantity(), currentCoat.getPhotograph(), currentCoat.getLength());

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags table_veiw::flags(const QModelIndex & index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}



