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
#include "pictogramme.hpp"
#include "pictoAction.hpp"
#include "pictoSortie.hpp"
#include "pictoIteration.hpp"
#include "pictoProcedure.hpp"
#include "pictoCondition.hpp"
#include "pictoConditionMultiple.hpp"

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
          picto = new PictoAction( "", "", "", 0, scene );

     } else if( mode == AlgorithmeScene::InsertLoop ) {
          picto = new PictoIteration( "", 0, scene );

     } else if( mode == AlgorithmeScene::InsertProcedure ) {
          picto = new PictoProcedure( "", "", "", 0, scene );

     } else if( mode == AlgorithmeScene::InsertCondition ) {
          picto = new PictoCondition( "", 0, scene );

     } else if( mode == AlgorithmeScene::InsertExit ) {
          picto = new PictoSortie( 0, scene );

     } else if( mode == AlgorithmeScene::InsertMultiCondition ) {
          picto = new PictoConditionMultiple( "", 0, scene );

     }

     scene->newItem( picto );
     return picto;

}/*}}}*/
