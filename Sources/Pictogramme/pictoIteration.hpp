#ifndef PICTOITERATION_HPP
#define PICTOITERATION_HPP
#include "pictogramme.hpp"
#include <QGraphicsItem>
#include "labelItem.hpp"

class PictoIteration : public Pictogramme
{
public:
   enum { Type = UserType + 4 };

    PictoIteration( QString titre,
                    QGraphicsItem* parent,
                    QGraphicsScene* scene );

    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
    QRectF boundingRect() const;
    void updateDimension();

    //void setLabel( const QString& titre );
    inline QString label() const {  return labels_.at( 0 )->label(); }
    virtual int type() const { return Type; }


private:
    QPointF points_[3];

};

#endif // PICTOITERATION_HPP
