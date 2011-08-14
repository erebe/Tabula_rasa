#ifndef LABELITEM_HPP
#define LABELITEM_HPP
#include "ancreItem.hpp"

class LabelItem : public AncreItem
{
public:
    enum { Type = UserType + 1 };

    LabelItem( const QString& texte,
               const int maxWidth = 150,
               const int minWidth = 50,
               const int height = 50,
               QGraphicsItem *parent = 0,
               QGraphicsScene *scene = 0 );

    virtual void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
    QRectF boundingRect() const;

    void setLabel( const QString& texte );
    inline QString label() const { return label_.first; }
    inline unsigned int width() const { return label_.second; }
    virtual int type() const { return Type; }

protected:
    QPair<QString, unsigned int> label_;
    unsigned int height_, maxWidth_, minWidth_;

    unsigned int calculLargeurTexte() const;

};

#endif // LABELITEM_HPP
