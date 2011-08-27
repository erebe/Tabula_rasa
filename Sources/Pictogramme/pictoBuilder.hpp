/*
 * =====================================================================================
 *
 *       Filename:  pictoBuilder.hpp
 *
 *    Description:  Classe permettant de construire des pictogrammes pour une Scène
 *
 *        Version:  1.0
 *        Created:  27/08/2011 04:41:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Erebe (), erebe@erebe.eu
 *        Company:  Erebe corporation
 *
 * =====================================================================================
 */

#ifndef PICTOBUILDER_H
#define PICTOBUILDER_H

#include <QtXml>

#include "algorithmeScene.hpp"

class Pictogramme;

class PictoBuilder {
     public:
          static Pictogramme* fromXml( const QDomElement& node,
                                       AlgorithmeScene* scene );

          static Pictogramme* fromMode( AlgorithmeScene::Mode mode,
                                        AlgorithmeScene* scene );
};

#endif // PICTOBUILDER_H
