/*
 * =====================================================================================
 *
 *       Filename:  ancreItem.hpp
 *
 *    Description:  Tabula Rasa : classe représentant un item possédant des ancres (aimant)
 *                  Il peut avoir une liaison
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:14:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef ANCREITEM_HPP
#define ANCREITEM_HPP
#include "liaisonItem.hpp"
#include <QEvent>

class AncreItem: public QGraphicsItem {

public:
    AncreItem( QGraphicsItem* parent = 0, QGraphicsScene* scene = 0 );
    virtual ~AncreItem();
    QPointF positionAncreBasse() const {
        return posBottomAnchor_;
    }
    QPointF positionAncreHaute() const {
        return posUpAnchor_;
    }


    virtual void setParent( AncreItem* parent );

    virtual void updateLink();
    virtual int type() const {
        return Type;
    }

    virtual QVariant itemChange( GraphicsItemChange change, const QVariant& value );
    void deleteLink();
    void detach();
    void deleteChildren();

protected:
    QPointF posBottomAnchor_;
    QPointF posUpAnchor_;

    AncreItem* parent_;
    QList<AncreItem*> children_;
    LiaisonItem* liaison_;

    virtual void addChild( AncreItem* child );

};

#endif // ANCREITEM_HPP
