#ifndef SHAPEOBJECT_H
#define SHAPEOBJECT_H

/******************************************************************************

Handle a shape.

******************************************************************************/

#include <node.h>
#include <v8.h>
#include "shapefil.h"

using namespace node;
using namespace v8;

class ShapeObject {
//class ShapeObject : public ObjectWrap {

    public:

        ShapeObject();
        ~ShapeObject();

        bool loadObject(SHPHandle shapeHandle, int shapeId);
        Local<Object> getObject();

    private: 

        int id;
        SHPObject * shape;
        Local<Object> getParts();

};

#endif
