#ifndef PICTOCONDITIONMULTIPLE_HPP
#define PICTOCONDITIONMULTIPLE_HPP

#include "pictogramme.hpp"

class PictoConditionMultiple : public Pictogramme
{
public:
    enum { Type = UserType + 7 };
    PictoConditionMultiple(  const QString& titre,
                             QGraphicsItem* parent,
                             QGraphicsScene* scene );

    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
    QRectF boundingRect() const;
    void updateDimension();

    QVariant itemChange( GraphicsItemChange change, const QVariant &value );
    virtual int type() const { return Type; }


protected:
       void processAction( QAction* action, QGraphicsSceneContextMenuEvent *event );
};

#endif // PICTOCONDITIONMULTIPLE_HPP
