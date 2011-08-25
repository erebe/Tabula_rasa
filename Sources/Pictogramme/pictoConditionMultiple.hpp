/*
 * =====================================================================================
 *
 *       Filename:  pictoConditionMultiple.hpp
 *
 *    Description:  Tabula Rasa : Classe représentant une condition Multiple
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:26:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef PICTOCONDITIONMULTIPLE_HPP
#define PICTOCONDITIONMULTIPLE_HPP

#include "pictogramme.hpp"

class PictoConditionMultiple : public Pictogramme {

public:
    enum { Type = UserType + 7 };
    PictoConditionMultiple( const QString& titre,
                            QGraphicsItem* parent,
                            QGraphicsScene* scene );

    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
    QRectF boundingRect() const;
    void updateDimension();

    QVariant itemChange( GraphicsItemChange change, const QVariant& value );
    virtual int type() const {
        return Type;
    }

    void toXml( QDomDocument& doc, QDomNode& node ) const;


protected:
    void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );
};

#endif // PICTOCONDITIONMULTIPLE_HPP
