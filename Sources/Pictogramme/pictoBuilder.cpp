#include "pictoBuilder.hpp"
#include "pictogramme.hpp"
#include "pictoAction.hpp"
#include "pictoSortie.hpp"
#include "pictoIteration.hpp"
#include "pictoProcedure.hpp"
#include "pictoCondition.hpp"
#include "pictoConditionMultiple.hpp"
#include "algorithmeScene.hpp"

Pictogramme* PictoBuilder::fromXml( const QDomElement& node,
                                    AlgorithmeScene* scene )
{

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


}

Pictogramme* PictoBuilder::fromMode( int mode,
                                     AlgorithmeScene* scene )
{


     Pictogramme* picto = 0;

     if( mode == 3 ) {
          picto = new PictoAction( "", "", "", 0, scene );

     } else if( mode == 5 ) {
          picto = new PictoIteration( "", 0, scene );

     } else if( mode == 4 ) {
          picto = new PictoProcedure( "", "", "", 0, scene );

     } else if( mode == 6 ) {
          picto = new PictoCondition( "", 0, scene );

     } else if( mode == 8 ) {
          picto = new PictoSortie( 0, scene );

     } else if( mode == 7 ) {
          picto = new PictoConditionMultiple( "", 0, scene );

     }

     scene->newItem( picto );
     return picto;

}
