#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QList>
#include "Model/DictionaryEntry.hpp"

class Dictionary
{
private:
    QList<DictionaryEntry> *entries_;
public:
    Dictionary();
    void addEntry(const DictionaryEntry &e);
    inline QList<DictionaryEntry> * entries() const { return entries_; }
    inline int size() const { return entries_->size(); }
    inline DictionaryEntry& elementAt(int index) const { return (*entries_)[index]; }
};

#endif // DICTIONARY_H
