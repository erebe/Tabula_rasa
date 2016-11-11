#ifndef DICTIONARYTABLEVIEWMODEL_H
#define DICTIONARYTABLEVIEWMODEL_H

#include <QAbstractTableModel>
class Dictionary;

class DictionaryTableViewModel : public QAbstractTableModel
{
public:
    DictionaryTableViewModel(Dictionary & dictionary);
    QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    void appendEmptyEntryRow();
    void removeRowAtIndex(int index);
private:
    Dictionary &dictionary_;
};

#endif // DICTIONARYTABLEVIEWMODEL_H
