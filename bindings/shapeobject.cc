#include "shapeobject.h"

ShapeObject::ShapeObject() {};
ShapeObject::~ShapeObject() {};

bool ShapeObject::loadObject(SHPHandle shapeHandle, int shapeId) {

    printf( "read shape %i\n", shapeId);

    shape = ::SHPReadObject(shapeHandle, shapeId);

    if( shape == NULL) return false;

};
