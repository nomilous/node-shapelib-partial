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

        bool loadShape(SHPHandle shapeHandle, int shapeId);
        bool loadRecord(DBFHandle dbfHandle, int shapeId);
        
        Local<Object> getObject();

    private: 

        int id;
        SHPObject * shape;
        Local<Object> getParts();

};

#endif
