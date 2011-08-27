/*
 * =====================================================================================
 *
 *       Filename:  labelItem.cpp
 *
 *    Description:  Tabula Rasa : Implementation de la classe représentant un
 *                  item contenant du texte
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:18:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "labelItem.hpp"
#include <QPainter>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
LabelItem::LabelItem( const QString& texte,
                      const int maxWidth,
                      const int minWidth,
                      const int height,
                      QGraphicsItem* parent,
                      QGraphicsScene* scene )
     : AncreItem( parent, scene ),
       height_( height ),
       maxWidth_( maxWidth ),
       minWidth_( minWidth )
{/*{{{*/
     setLabel( texte );
}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void LabelItem::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{/*{{{*/


     Q_UNUSED( option );
     Q_UNUSED( widget );

     painter->drawText( 0, 0,
                        label_.second, height_,
                        Qt::TextWordWrap | Qt::AlignCenter,
                        label_.first );
}/*}}}*/

QRectF LabelItem::boundingRect() const
{/*{{{*/

     return QRectF( 0, 0, label_.second, height_ );
}/*}}}*/

void LabelItem::setLabel( const QString& texte )
{/*{{{*/


     label_.first = texte.isEmpty() ? "?" : texte;
     prepareGeometryChange();
     label_.second = calculLargeurTexte();
     posBottomAnchor_.setX( label_.second / 2 );
     posBottomAnchor_.setY( height_ );

     posUpAnchor_.setX( label_.second / 2 );
     posUpAnchor_.setY( 0 );
}/*}}}*/

bool LabelItem::isEmpty() const
{/*{{{*/

     if( label_.first.isEmpty() || label_.first == "?" )
          { return true; }

     else
          { return false; }
}/*}}}*/

unsigned int LabelItem::calculLargeurTexte() const
{/*{{{*/

     QFont font( "Cantarell,11,-1,5,50,0,0,0,0,0" );
     QFontMetrics fm( font );
     unsigned int largeurTexte = fm.width( label_.first ) + 10;

     if( largeurTexte > maxWidth_ ) {
          return maxWidth_;
     }

     else if( largeurTexte < minWidth_ ) {
          return minWidth_;
     }

     return largeurTexte;

}/*}}}*/
