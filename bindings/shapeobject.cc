#include "shapeobject.h"

ShapeObject::ShapeObject() {};
ShapeObject::~ShapeObject() {};

bool ShapeObject::loadShapeHandle(SHPHandle shapeHandle, int shapeId) {

    id = shapeId;
    shape = ::SHPReadObject(shapeHandle, shapeId);
    if( shape == NULL) return false;
    return true;

};

bool ShapeObject::loadRecordHandle(DBFHandle dbfHandle, int recordId, int fieldCount) {

    this->dbfHandle = dbfHandle;
    this->fieldCount = fieldCount;
    return true;

};

Local<Object> ShapeObject::getObject() {

    HandleScope scope;
    Local<Object> jsShape = Object::New();

    jsShape->Set(

        String::NewSymbol("id"),
        Number::New(id)

    );

    jsShape->Set(

        String::NewSymbol("type"),
        Number::New(shape->nSHPType)

    );

    jsShape->Set(

        String::NewSymbol("partCount"),
        Number::New(shape->nParts)

    );

    jsShape->Set(

        String::NewSymbol("vertexCount"),
        Number::New(shape->nVertices)

    );

    jsShape->Set(

        String::NewSymbol("fields"),
        getFields()

    );

    jsShape->Set(

        String::NewSymbol("vertices"),
        getParts()

    );

    return scope.Close( jsShape );

};


Local<Array> ShapeObject::getParts() {

    HandleScope scope;

    // Local<Array> parts = Array::New();

    //
    // i'm confuzed about how to read the parts, 
    // so only supporting first part
    //
    // or that's what i think i'm doing,
    // docs a bit vague on the meaning of part
    //

    Local<Array> vertices = Array::New();

    int i;
    for(i = 0; i < shape->nVertices; i++ ) {

        Local<Array> vertex = Array::New();

        vertex->Set(Number::New(0), Number::New(shape->padfX[i]));
        vertex->Set(Number::New(1), Number::New(shape->padfY[i]));
        vertex->Set(Number::New(2), Number::New(shape->padfZ[i]));
        vertex->Set(Number::New(3), Number::New(shape->padfM[i]));

        vertices->Set(i, vertex);

    }

    //parts->Set(Number::New(0), vertices);

    return scope.Close(vertices);

};

Local<Object> ShapeObject::getFields() {

    HandleScope scope;

    Local<Object> obj = Object::New();

    if(dbfHandle != NULL) {

        char name[12];
        int width;
        int decimals;
        int i;

        for( i = 0; i < fieldCount; i++ ) {

            switch( DBFGetFieldInfo(dbfHandle, i, name, &width, &decimals) ) {

                case FTString:

                    obj->Set(

                        String::NewSymbol(name),
                        String::New((char *) DBFReadStringAttribute(dbfHandle, id, i))

                    );
                    break;

                case FTInteger:

                    obj->Set(

                        String::NewSymbol(name),
                        Number::New(DBFReadIntegerAttribute(dbfHandle, id, i))

                    );
                    break;

                case FTDouble:

                    obj->Set(

                        String::NewSymbol(name),
                        Number::New(DBFReadDoubleAttribute(dbfHandle, id, i))

                    );
                    break;
            }
        }
    }

    return scope.Close( obj );

};

