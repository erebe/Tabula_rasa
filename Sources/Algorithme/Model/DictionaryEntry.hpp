#ifndef ELEMENT_H
#define ELEMENT_H

#include <QString>

class DictionaryEntry
{
private:
    QString name_;
    QString type_;
    QString signification_;
public:
    DictionaryEntry();
    DictionaryEntry(QString name, QString type, QString signification);
    void inline setName(const QString &name) { name_ = name; }
    QString inline name() const { return name_; }
    void inline setType(const QString &type) { type_ = type; }
    QString inline type() const { return type_; }
    void inline setSignification(const QString &signification) { signification_ = signification; }
    QString inline signification() const { return signification_; }
    void setPropertyAt(int index, QString value);
    QString propertyAt(int index);
};

#endif // ELEMENT_H
