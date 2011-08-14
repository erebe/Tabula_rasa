#ifndef PICTOGRAMME_HPP
#define PICTOGRAMME_HPP

#include <QGraphicsItem>
#include <QMenu>
#include "labelItem.hpp"
#include "ancreItem.hpp"

class Pictogramme : public QObject, public AncreItem
{
        Q_OBJECT

public:
   Pictogramme( QGraphicsItem* parent = 0, QGraphicsScene* scene = 0 );
   virtual ~Pictogramme();

   virtual void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget );
   virtual void updateDimension() = 0;
   inline unsigned int width() const { return pos_; }



signals:
   void doubleClick( LabelItem* item );


protected:
   QList<LabelItem*> labels_;
   unsigned int pos_;
   QMenu contexteMenu_;
   QMap<QString, QAction*> actions_;

   void mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event );
   void contextMenuEvent( QGraphicsSceneContextMenuEvent *event );
   virtual void processAction( QAction* action, QGraphicsSceneContextMenuEvent *event );

};

#endif // PICTOGRAMME_HPP
