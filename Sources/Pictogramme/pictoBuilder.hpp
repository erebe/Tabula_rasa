#ifndef PICTOBUILDER_H
#define PICTOBUILDER_H

#include <QtXml>

class AlgorithmeScene;
class Pictogramme;

class PictoBuilder {
     public:
          static Pictogramme* fromXml( const QDomElement& node,
                                       AlgorithmeScene* scene );

          static Pictogramme* fromMode( int mode,
                                        AlgorithmeScene* scene );
};

#endif // PICTOBUILDER_H
