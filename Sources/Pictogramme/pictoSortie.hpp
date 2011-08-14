#ifndef PICTOSORTIE_HPP
#define PICTOSORTIE_HPP

#include "pictogramme.hpp"

class PictoSortie: public Pictogramme
{
public:
   enum { Type = UserType + 6 };
   PictoSortie( QGraphicsItem* parent = 0,
                QGraphicsScene* scene = 0 );


   void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
   QRectF boundingRect() const;
   void updateDimension();

   virtual int type() const { return Type; }
};

#endif // PICTOSORTIE_HPP
