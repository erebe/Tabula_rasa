/*
 * =====================================================================================
 *
 *       Filename:  pictogramme.hpp
 *
 *    Description:  Tabula Rasa : Classe mère de tous les élements de l'algorithme
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:34:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef PICTOGRAMME_HPP
#define PICTOGRAMME_HPP

#include <QGraphicsItem>
#include <QMenu>
#include <QtXml>

#include "labelItem.hpp"
#include "ancreItem.hpp"

class Pictogramme : public QObject, public AncreItem {

    Q_OBJECT

public:
    Pictogramme( QGraphicsItem* parent = 0, QGraphicsScene* scene = 0 );
    virtual ~Pictogramme();

    virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
    virtual void updateDimension() = 0;
    inline unsigned int width() const {
        return pos_;
    }
    virtual void toXml( QDomDocument& doc, QDomNode& node ) const = 0;



signals:
    void doubleClick( LabelItem* item );


protected:
    QList<LabelItem*> labels_;
    unsigned int pos_;
    QMenu contexteMenu_;
    QMap<QString, QAction*> actions_;

    void mouseDoubleClickEvent( QGraphicsSceneMouseEvent* event );
    void contextMenuEvent( QGraphicsSceneContextMenuEvent* event );
    virtual void processAction( QAction* action, QGraphicsSceneContextMenuEvent* event );

};

#endif // PICTOGRAMME_HPP
