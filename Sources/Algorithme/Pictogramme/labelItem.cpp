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
#include "liaisonItem.hpp"
#include <QPainter>
#include <QDebug>

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

LabelItem::LabelItem(const LabelItem &item):
    AncreItem(item),
    label_(item.label_), height_(item.height_),
    maxWidth_(item.maxWidth_), minWidth_(item.minWidth_)
{
    setLabel(item.label_.first);
}

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
     formatString();

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
     QFont font( "times", 10 );
     QFontMetrics fm( font );

     unsigned int largeurTexte = 0;
     unsigned int current;

     QStringList lignes = label_.first.split( "\n" );
     foreach( const QString & ligne, lignes ) {
          current = fm.width( ligne );

          if( current > largeurTexte )
               { largeurTexte = fm.width( ligne ); }
     }

     largeurTexte += 10;

     if( largeurTexte > maxWidth_ ) {
          return maxWidth_;

     } else if( largeurTexte < minWidth_ ) {
          return minWidth_;
     }

     return largeurTexte;
}/*}}}*/

void LabelItem::formatString()
{/*{{{*/

     label_.first.replace( "->", "→" );
     label_.first.replace( "<-", "←" );
}/*}}}*/

void LabelItem::onChildrenChange()
{/*{{{*/
    if( children_.size() == 1 )
        setLinkStyle( LiaisonItem::Linear );
    else
        setLinkStyle( LiaisonItem::Simple );
}/*}}}*/
