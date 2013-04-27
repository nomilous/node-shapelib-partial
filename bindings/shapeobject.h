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

    public:

        ShapeObject(); 
        ~ShapeObject();

        bool loadShapeHandle(SHPHandle shapeHandle, int shapeId);
        bool loadRecordHandle(DBFHandle dbfHandle, int recordId, int fieldCount);

        Local<Object> getObject();

    private: 

        int id;
        SHPObject * shape;
        DBFHandle dbfHandle;
        int fieldCount;

        Local<Array> getParts();
        Local<Object> getFields();

};

#endif
