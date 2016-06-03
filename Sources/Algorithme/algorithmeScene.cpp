/*
 * =====================================================================================
 *
 *       Filename:  algorithmeScene.cpp
 *
 *    Description:  Tabula Rasa : Implémentation de la classe gérant la scène
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:13:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#include "algorithmeScene.hpp"
#include "pictoBuilder.hpp"

#include "Model/Algorithm.hpp"
#include "Pictogramme/pictogramme.hpp"
#include "Pictogramme/pictoCondition.hpp"
#include "Pictogramme/pictoConditionMultiple.hpp"
#include "Pictogramme/pictoSortie.hpp"
#include "Pictogramme/pictoIteration.hpp"

#include "XML/AlgorithmParser.hpp"
#include "XML/DictionaryWriter.hpp"
#include "XML/XMLNodeCreator.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>

/*-----------------------------------------------------------------------------
 *  Constructeurs / Destructeurs
 *-----------------------------------------------------------------------------*/
AlgorithmeScene::AlgorithmeScene(qreal x, qreal y, qreal width, qreal height, QObject *parent):
    QGraphicsScene(x, y, width, height, parent),
    mode_(MoveItem), line_(0)
{/*{{{*/
    algorithm_ = new Algorithm("Algorithme", new Dictionary);
    actions_["Supprimer"] = contexteMenu_.addAction( tr( "Supprimer" ) );
    contexteMenu_.addSeparator();
    actions_["Delier"] = contexteMenu_.addAction( tr( "Délier de tous" ) );
    contexteMenu_.addSeparator();
    actions_["Details"] = contexteMenu_.addAction( tr( "Masquer les assertions" ) );
    actions_["EmptyDetails"] = contexteMenu_.addAction( tr( "Masquer les assertions vides" ) );



    selectionArea_.second = 0;
}/*}}}*/

AlgorithmeScene::~AlgorithmeScene()
{
    /*{{{*/
    Pictogramme *picto;
    foreach(picto, algorithm()->allPictograms())
        delete picto;
}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Méthodes
 *-----------------------------------------------------------------------------*/
void AlgorithmeScene::setName( const QString& name )
{
    algorithm()->setName(name);
}

QString AlgorithmeScene::name()
{
    return algorithm()->name();
}

void AlgorithmeScene::deleteItem(Pictogramme *item)
{
    /*{{{*/
    algorithm()->removePictogram(item);
    removeItem(item);
    delete item;
}/*}}}*/

void AlgorithmeScene::newItem(Pictogramme *picto)
{
    /*{{{*/
    if (picto) {
        algorithm()->addPictogram(picto);
        addItem(picto);
        emit itemAdded(picto);
    }
}/*}}}*/

void AlgorithmeScene::saveToXml(QTextStream &out) const
{
    /*{{{*/
    QDomDocument doc("Tabula_Rasa");

    QDomNode noeud = doc.createProcessingInstruction("xml", "version=\"1.0\"");
    doc.insertBefore(noeud, doc.firstChild());

    QDomElement root = doc.createElement("Algorithme");
    doc.appendChild(root);

    QDomElement name = doc.createElement("nom");
    name.appendChild(doc.createTextNode(algorithm()->name()));
    root.appendChild(name);

    QDomElement date = doc.createElement("date_creation");
    date.appendChild(doc.createTextNode(QDateTime::currentDateTime().toString("d/M/yyyy hh:mm")));
    root.appendChild(date);

    QDomElement elements = doc.createElement("Elements");

    Pictogramme *picto;
    foreach(picto, algorithm()->allPictograms()) {
        if (!picto->isChild()) {
            picto->toXml(doc, elements);
        }
    }
    root.appendChild(elements);

    XMLNodeCreator nodeCreator(doc);
    DictionaryWriter dictionaryWriter(nodeCreator);
    QDomElement dictionaryNode = dictionaryWriter.write(algorithm()->dictionary());
    root.appendChild(dictionaryNode);


    doc.save(out, 2);
}/*}}}*/

void AlgorithmeScene::loadFromXml(const QDomDocument &doc)
{/*{{{*/

    AlgorithmParser parser;
    algorithm_ = parser.parse(doc.documentElement());

    /* Little hack to display liaisons, should refactor item insertion */
    foreach( Pictogramme* item, algorithm()->allPictograms()) {
        addItem(item);
        item->itemChange(QGraphicsItem::ItemPositionChange, QVariant());
    }

}/*}}}*/


/*-----------------------------------------------------------------------------
 *  Gestionnaires d'évènements
 *-----------------------------------------------------------------------------*/
void AlgorithmeScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{/*{{{*/
    mouseEvent->accept();

    if(mouseEvent->button() != Qt::LeftButton) {
        QGraphicsScene::mousePressEvent(mouseEvent);
        return;
    }

    switch (mode_) {

    case EditLink:
        drawLiaison(mouseEvent->scenePos(), mouseEvent->scenePos());
        break;

    case MoveItem:

        if (!items(mouseEvent->scenePos()).count()) {
            drawSelectionRect(mouseEvent->scenePos(), QPointF(0,0));

            if(mouseEvent->modifiers() == Qt::ControlModifier) {
                return; /* to avoid items get unselected when adding new ones */
            }

        }
        break;

    default:
        break;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);

}/*}}}*/

void AlgorithmeScene::drawSelectionRect(QPointF topLeft, QPointF bottomRight) {

    QPointF topL;
    QPointF bottomR;

    if(!selectionArea_.second) {
        selectionArea_.first = topLeft;
        selectionArea_.second = new QGraphicsRectItem();
        QGraphicsScene::addItem(selectionArea_.second);
        topL = topLeft;
        bottomR = topLeft;
    } else {

        //Be sure that the rectangle is right oriented
        topL.setX((topLeft.x() < bottomRight.x()) ? topLeft.x() : bottomRight.x());
        topL.setY((topLeft.y() < bottomRight.y()) ? topLeft.y() : bottomRight.y());

        bottomR.setX((topLeft.x() > bottomRight.x()) ? topLeft.x() : bottomRight.x());
        bottomR.setY((topLeft.y() > bottomRight.y()) ? topLeft.y() : bottomRight.y());
    }

    selectionArea_.second->setRect(QRectF(topL, bottomR));

}

void AlgorithmeScene::drawLiaison(QPointF x, QPointF y) {

    if(!line_) {
        line_ = new QGraphicsLineItem();
        QGraphicsScene::addItem(line_);
    }

    line_->setLine(QLineF(x, y));
}

void AlgorithmeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    /*{{{*/
    mouseEvent->accept();

    //Attempt to link pictogramme
    if (mode_ == EditLink && line_ != NULL) {
        drawLiaison(line_->line().p1(), mouseEvent->scenePos());
        return;
    }

    //Attempt to select pictogrammes
    if (mode_ == MoveItem && selectionArea_.second != NULL) {
        drawSelectionRect(selectionArea_.first,  mouseEvent->scenePos());

        /* Control modifier means we want to add more items to the selection */
        if(mouseEvent->modifiers() != Qt::ControlModifier) {
            foreach(QGraphicsItem * item, selectedItems()) {
                item->setSelected(false);
            }
        }

        /* select items */
        foreach(QGraphicsItem * item, items(selectionArea_.second->rect())) {
            item->setSelected(true);
        }
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);


}/*}}}*/

void AlgorithmeScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    /*{{{*/
    mouseEvent->accept();
    emit algorithmeChanged();

    if (mouseEvent->button() != Qt::LeftButton) {
        return;
    }

    /* delete selection area */
    if (selectionArea_.second != 0) {
        delete selectionArea_.second;
        selectionArea_.second = 0;
    }

    /*-----------------------------------------------------------------------------
     *  Mode d'edition des liaisons
     *-----------------------------------------------------------------------------*/
    if (line_ != 0 && mode_ == EditLink) { /*{{{*/
        QList<QGraphicsItem *> startItems = items(line_->line().p2());
        QList<QGraphicsItem *> endItems = items(line_->line().p1());

        if (startItems.count() && startItems.first() == line_) {
            startItems.removeFirst();
        }

        if (endItems.count() && endItems.first() == line_) {
            endItems.removeFirst();
        }

        removeItem(line_);
        delete line_;
        line_ = 0;



        foreach(QGraphicsItem * item, startItems) {
            if (!item->isEnabled()) {
                startItems.removeOne(item);
            }
        }
        foreach(QGraphicsItem * item, endItems) {
            if (!item->isEnabled()) {
                endItems.removeOne(item);
            }
        }

        if (startItems.count() && endItems.count()) {
            Pictogramme *enfant, *parent;
            enfant = parent = 0;

            if (startItems.first()->parentItem() != 0) {
                enfant =  static_cast<Pictogramme *>(startItems.first()->parentItem());

            } else {
                enfant = static_cast<Pictogramme *>(startItems.first());
            }

            if (endItems.first()->parentItem() != 0 &&
                    !qgraphicsitem_cast<PictoCondition *>(endItems.first()->parentItem())
                    && !qgraphicsitem_cast<PictoConditionMultiple *>(endItems.first()->parentItem())) {
                parent = static_cast<Pictogramme *>(endItems.first()->parentItem());

            } else if (!qgraphicsitem_cast<PictoCondition *>(endItems.first())
                       && !qgraphicsitem_cast<PictoConditionMultiple *>(endItems.first())) {
                parent = static_cast<Pictogramme *>(endItems.first());
            }

            if (qgraphicsitem_cast<PictoIteration *>(parent) &&
                    qgraphicsitem_cast<PictoSortie *>(enfant)) {

                emit liaisonError();
                return;
            }

            if ((parent != 0) && (enfant != parent)) {
                if (!parent->addChild(enfant)) {

                    emit liaisonError();
                }
            }
        }
    }/*}}}*/


    /*-----------------------------------------------------------------------------
     *  Mode d'insertion d'item
     *-----------------------------------------------------------------------------*/
    if ((mode_ != EditLink) && (mode_ != MoveItem)) {     /*{{{*/
        Pictogramme *picto = PictoBuilder::fromMode(mode_);

        if (picto) {
            newItem( picto );
            QRectF size = picto->boundingRect();
            picto->setPos(mouseEvent->scenePos().x() - (size.width() / 2),
                          mouseEvent->scenePos().y() - (size.height() / 2));
        }

        if (mouseEvent->modifiers() != Qt::ControlModifier) {
            setMode(AlgorithmeScene::MoveItem);
            emit modeChanged(AlgorithmeScene::MoveItem);
        }
    }/*}}}*/


    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}/*}}}*/

void AlgorithmeScene::contextMenuEvent( QGraphicsSceneContextMenuEvent * contextMenuEvent ) {
    contextMenuEvent->accept();

    //    /* Context menu on the sélection */
    //    if(selectedItems().count() > 1) {
    //        mouseGrabberItem()->ungrabMouse();

    //        QAction* selectedAction = contexteMenu_.exec( contextMenuEvent->screenPos() );
    //        if( selectedAction == actions_["Supprimer"]) {
    //            deleteSelectedItem();

    //        } else if(selectedAction == actions_["Delier"]) {
    //            foreach(QGraphicsItem* item, selectedItems()) {
    //                static_cast<Pictogramme*>(item)->detach();

    //            }
    //        }

    //    }else {
    //        QGraphicsScene::contextMenuEvent(contextMenuEvent);
    //    }

    QGraphicsScene::contextMenuEvent(contextMenuEvent);
}

void AlgorithmeScene::selectAll()
{
    /*{{{*/

    foreach(Pictogramme * picto, algorithm()->allPictograms()) {
        picto->setSelected(true);
    }

}/*}}}*/

void AlgorithmeScene::deleteSelectedItem()
{
    foreach(Pictogramme * picto, algorithm()->allPictograms()) {
        if( picto->isSelected())
            this->deleteItem(picto);

    }
}

void AlgorithmeScene::adjust(int delta)
{
    /*{{{*/

    qreal maxX, maxY, minX, minY;
    maxX = maxY = 0;
    minX = width();
    minY = height();

    Pictogramme *item;
    QPointF point;

    foreach(item, algorithm()->allPictograms()) {

        point = item->scenePos();

        if (maxX < (point.x() + item->width())) {
            maxX = point.x() + item->width();
        }

        if (maxY < point.y()) {
            maxY = point.y();
        }

        if (minX > point.x()) {
            minX = point.x();
        }

        if (minY > point.y()) {
            minY = point.y();
        }
    }


    setSceneRect(minX - delta , minY - delta,
                 maxX - minX + (2 * delta),
                 maxY - minY + 50 + (2 * delta));
}/*}}}*/


QList<Pictogramme *> AlgorithmeScene::copySelected() const
{

    QList<Pictogramme*> selected;
    foreach(Pictogramme * picto, algorithm()->allPictograms()) {
        if(picto->isSelected())
            selected.append(picto);
    }

    return copy(selected);
}

QList<Pictogramme *> AlgorithmeScene::copy(QList<Pictogramme*> items) const
{
    QMap<Pictogramme*, Pictogramme*> oldNewTable;
    foreach(Pictogramme * picto, items) {
        oldNewTable.insert(picto, picto->clone());
    }

    QList<Pictogramme*> copies = oldNewTable.values();
    foreach(Pictogramme* picto, oldNewTable.keys()) {


        foreach (AncreItem* child, picto->childrenList()) {
            if(oldNewTable.contains(static_cast<Pictogramme*>(child))) {
                oldNewTable[picto]->addChild(oldNewTable[static_cast<Pictogramme*>(child)]);
                oldNewTable[picto]->setLinkStyle(picto->linkStyle());
            }
        }
    }

    return copies;

}

void AlgorithmeScene::paste(QList<Pictogramme *> items)
{
    clearSelection();
    foreach(Pictogramme* picto, items) {
        newItem(picto);
        picto->setSelected(true);
        picto->updateLink();
    }

    setMode(AlgorithmeScene::MoveItem);
    emit modeChanged(AlgorithmeScene::MoveItem);
}
