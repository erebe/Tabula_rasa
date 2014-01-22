/*
 * =====================================================================================
 *
 *       Filename:  pictoBuilder.cpp
 *
 *    Description:  Classe permettant de construire des pictogrammes pour une Scène
 *
 *        Version:  1.0
 *        Created:  27/08/2011 04:42:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */

#include "pictoBuilder.hpp"
#include "Pictogramme/pictogramme.hpp"
#include "Pictogramme/pictoAction.hpp"
#include "Pictogramme/pictoSortie.hpp"
#include "Pictogramme/pictoIteration.hpp"
#include "Pictogramme/pictoProcedure.hpp"
#include "Pictogramme/pictoCondition.hpp"
#include "Pictogramme/pictoConditionMultiple.hpp"

Pictogramme* PictoBuilder::fromXml( const QDomElement& node,
                                    AlgorithmeScene* scene )
{/*{{{*/
     QString tagName = node.tagName();
     Pictogramme* picto = 0;

     if( tagName == "Action" ) {
          picto = new PictoAction( node, scene );

     } else if( tagName == "Procedure" ) {
          picto = new PictoProcedure( node, scene );

     } else if( tagName == "Condition" ) {
          picto = new PictoCondition( node, scene );

     } else if( tagName == "ConditionMultiple" ) {
          picto = new PictoConditionMultiple( node, scene );

     } else if( tagName == "Sortie" ) {
          picto = new PictoSortie( node, scene );

     } else if( tagName == "Iteration" ) {
          picto = new PictoIteration( node, scene );
     }

     scene->newItem( picto );
     return picto;
}/*}}}*/

Pictogramme* PictoBuilder::fromMode( AlgorithmeScene::Mode mode,
                                     AlgorithmeScene* scene )
{/*{{{*/
     Pictogramme* picto = 0;

     if( mode == AlgorithmeScene::InsertAction ) {
          picto = new PictoAction( "", "", "" );

     } else if( mode == AlgorithmeScene::InsertLoop ) {
          picto = new PictoIteration( "");

     } else if( mode == AlgorithmeScene::InsertProcedure ) {
          picto = new PictoProcedure( "", "", "" );

     } else if( mode == AlgorithmeScene::InsertCondition ) {
          picto = new PictoCondition( "" );

     } else if( mode == AlgorithmeScene::InsertExit ) {
          picto = new PictoSortie();

     } else if( mode == AlgorithmeScene::InsertMultiCondition ) {
          picto = new PictoConditionMultiple( "" );
     }

     scene->newItem( picto );
     return picto;
}/*}}}*/
