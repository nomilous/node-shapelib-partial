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

struct ObjectField {

    DBFFieldType type;
    char name[12];
    double doubleValue;
    int intValue;
    char * stringValue;

};

class ShapeObject {
//class ShapeObject : public ObjectWrap {

    public:

        ShapeObject();
        ~ShapeObject();

        bool loadShape(SHPHandle shapeHandle, int shapeId);
        bool loadRecord(DBFHandle dbfHandle, int recordId, int fieldCount);

        Local<Object> getObject();

    private: 

        int id;
        SHPObject * shape;

        int fieldCount;
        ObjectField * fields;
        Local<Array> getParts();
        Local<Object> getFields();

};

#endif
