/*
 * =====================================================================================
 *
 *       Filename:  pictoIteration.hpp
 *
 *    Description:  Tabula Rasa : Classe représentant une iteration
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:36:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef PICTOITERATION_HPP
#define PICTOITERATION_HPP
#include "pictogramme.hpp"
class QGraphicsItem;
class AlgorithmeScene;

class PictoIteration : public Pictogramme {

public:
    enum { Type = UserType + 4 };

    PictoIteration( QString titre,
                    QGraphicsItem* parent,
                    QGraphicsScene* scene );

    PictoIteration( const QDomElement& node,
                    AlgorithmeScene* scene = 0 );

    void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
    QRectF boundingRect() const;
    void updateDimension();

    void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );
    void toXml( QDomDocument& doc, QDomNode& node ) const;


    inline QString label() const {
        return labels_.at( 0 )->label();
    }
    virtual int type() const {
        return Type;
    }


private:
    QPointF points_[3];
    bool isNumberedLoop_;

};

#endif // PICTOITERATION_HPP
