#include "DictionaryTableViewModel.hpp"
#include "Model/Dictionary.hpp"
#include "Model/DictionaryEntry.hpp"

DictionaryTableViewModel::DictionaryTableViewModel(Dictionary &dictionary) : dictionary_(dictionary)
{
}


QVariant DictionaryTableViewModel::headerData(int section, Qt::Orientation orientation,
                            int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) {
            return QVariant("Nom");
        }
        if (section == 1) {
            return QVariant("Type");
        }
        return QVariant("Signification");
    }
    // no vertical header
    return QVariant();
}

int DictionaryTableViewModel::rowCount(const QModelIndex &parent) const {
    return dictionary_.size();
}

int DictionaryTableViewModel::columnCount(const QModelIndex &parent) const {
    return 3;
}

QVariant DictionaryTableViewModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        DictionaryEntry &el = dictionary_.elementAt(index.row());
        return QVariant(el.propertyAt(index.column()));
    }
    return QVariant();
}

bool DictionaryTableViewModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        DictionaryEntry &el = dictionary_.elementAt(index.row());
        el.setPropertyAt(index.column(), value.toString());
        return true;
    }
    return false;
}

Qt::ItemFlags DictionaryTableViewModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
}

void DictionaryTableViewModel::appendEmptyEntryRow() {
    beginInsertRows(QModelIndex(), dictionary_.size(), dictionary_.size());
    dictionary_.addEntry(DictionaryEntry());
    endInsertRows();
}
