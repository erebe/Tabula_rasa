#include "DictionaryEntry.hpp"

DictionaryEntry::DictionaryEntry()
{
}

DictionaryEntry::DictionaryEntry(QString name, QString type, QString signification) {
    setName(name);
    setType(type);
    setSignification(signification);
}

void DictionaryEntry::setPropertyAt(int index, QString value) {
    if (index == 0) {
        setName(value);
    }
    else if (index == 1) {
        setType(value);
    }
    else {
        setSignification(value);
    }
}

QString DictionaryEntry::propertyAt(int index) {
    if (index == 0) {
        return name();
    }
    else if (index == 1) {
        return type();
    }
    return signification();
}
