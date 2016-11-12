/*
 * =====================================================================================
 *
 *       Filename:  pictoSortie.hpp
 *
 *    Description:  Tabula Rasa : Classe representant un item de Sortie
 *
 *        Version:  1.0
 *        Created:  15/08/2011 03:41:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */
#ifndef PICTOSORTIE_HPP
#define PICTOSORTIE_HPP

#include "pictogramme.hpp"

class PictoSortie: public Pictogramme {

     public:
          enum { Type = UserType + 6 };

          PictoSortie(QGraphicsItem* parent = 0);

          PictoSortie( const PictoSortie& item);


          /*-----------------------------------------------------------------------------
           *  Méthodes
           *-----------------------------------------------------------------------------*/
          void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );
          QRectF boundingRect() const;
          virtual int type() const { return Type; }
          virtual Pictogramme* clone();

          void updateDimension();
          void toXml( QDomDocument& doc, QDomNode& node ) const;

    private:
          PictoSortie& operator=(const PictoSortie& item);
};

#endif // PICTOSORTIE_HPP
