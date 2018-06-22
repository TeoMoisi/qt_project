#include "coat_table.h"

coat_table::coat_table(Repository &coat_repo, QObject* parent) : QAbstractTableModel{ parent }, coat_repo{ repo }
{

}

coat_table::~coat_table()
{
}


int coat_table::rowCount(const QModelIndex & parent) const
{
    int number = this->coat_repo._list.size();
    return number + 1;
}

int coat_table::columnCount(const QModelIndex & parent) const
{
    return 6;
}

QVariant coat_table::data(const QModelIndex & index, int role) const
{
    int row = index.row();
    int column = index.column();

    // get the genes
    std::vector<Coat> coats = this->coat_repo.getCoats();

    // Allow adding in the table
    // this is to show an empty row at the end of the table - to allow adding new genes
    if (row == coats.size())
    {
        return QVariant();
    }

    // get the gene from the current row
    Coat c = coats[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        switch (column)
        {
        case 0:
            return std::to_string(c.getSize());
        case 1:
            return QString::fromStdString(c.getColour());
        case 2:
            return std::to_string(c.getPrice());
        case 3:
            return std::to_string(c.getQuantity());
        case 4:
            return QString::fromStdString(c.getPhotograph());
        case 5:
            return std::to_string(c.getLength());
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
            return QBrush{ QColor{0, 250, 154} };
        }
    }

    return QVariant{};
}


QVariant coat_tablel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                return QString{ "Coat size" };
            case 1:
                return QString{ "Coat colour" };
            case 2:
                return QString{ "Coat price" };
            case 3:
                return QString{ "Coat quantity" };
            case 4:
                return QString{ "Coat photo" };
            case 5:
                return QString{ "Coat length" };
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

bool coat_table::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    // set the new data to the gene
    int geneIndex = index.row();

    // get the genes
    std::vector<Coat> coats = this->coat_repo.getCoats();

    // Allow adding in the table
    //if the index is >= number of genes => a new gene is added
    if (geneIndex == coats.size())
    {
        this->beginInsertRows(QModelIndex{}, geneIndex, geneIndex);

        switch (index.column())
        {
        case 0:
            this->coat_repo.addCoat(Coat{ value.toString().toStdString(), "", "" });
            break;
        case 1:
            this->coat_repo.addCoat(Coat{ "", value.toString().toStdString(), ""});
            break;
        case 2:
            this->coat_repo.addCoat(Coat{ "", "", value.toString().toStdString() });
            break;
        }

        this->endInsertRows();
        return true;
    }

    Caot& currentCoat = coats[coatIndex];
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
        break;
    case 3:
        currentCoat.setQuantity(value.toInt());
        break;
    case 4:
        currentCoat.setPhotograph(value.toString().toStdString());
        break;
    case 5:
        currentCoat.setLength(value.toInt());
    }
    this->repo.updateGene(geneIndex, currentGene);

    // emit the dataChanged signal
    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags coat_table::flags(const QModelIndex & index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}


