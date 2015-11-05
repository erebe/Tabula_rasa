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
#include "XML/PictoActionParser.hpp"
#include "XML/PictoConditionParser.hpp"
#include "XML/PictoConditionMultipleParser.hpp"
#include "XML/PictoIterationParser.hpp"
#include "XML/PictoProcedureParser.hpp"
#include "XML/PictoSortieParser.hpp"

Pictogramme* PictoBuilder::fromXml( const QDomElement& node,
                                    AlgorithmeScene* scene )
{/*{{{*/
     QString tagName = node.tagName();
     PictoParser *parser = 0;
     if( tagName == "Action" ) {
         parser = new PictoActionParser();
     } else if( tagName == "Procedure" ) {
         parser = new PictoProcedureParser();
     } else if( tagName == "Condition" ) {
         parser = new PictoConditionParser();
     } else if( tagName == "ConditionMultiple" ) {
         parser = new PictoConditionMultipleParser();
     } else if( tagName == "Sortie" ) {
         parser = new PictoSortieParser();
     } else if( tagName == "Iteration" ) {
         parser = new PictoIterationParser();
     }
     Pictogramme* picto = parser->parse(node, scene);
     delete parser;
     scene->newItem( picto );
     return picto;
}/*}}}*/

Pictogramme* PictoBuilder::fromMode( AlgorithmeScene::Mode mode,
                                     AlgorithmeScene* scene )
{/*{{{*/
     Pictogramme* picto = 0;

     if( mode == AlgorithmeScene::InsertAction ) {
          picto = new PictoAction();

     } else if( mode == AlgorithmeScene::InsertLoop ) {
          picto = new PictoIteration();

     } else if( mode == AlgorithmeScene::InsertProcedure ) {
          picto = new PictoProcedure();

     } else if( mode == AlgorithmeScene::InsertCondition ) {
          picto = new PictoCondition("?");

     } else if( mode == AlgorithmeScene::InsertExit ) {
          picto = new PictoSortie();

     } else if( mode == AlgorithmeScene::InsertMultiCondition ) {
          picto = new PictoConditionMultiple("?");
     }

     scene->newItem( picto );
     return picto;
}/*}}}*/
