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

        String::NewSymbol("fields"),
        getFields()

    );

    jsShape->Set(

        String::NewSymbol("parts"),
        getParts()

    );

    return scope.Close( jsShape );

};


Local<Array> ShapeObject::getParts() {

    HandleScope scope;

    return scope.Close( Array::New() );

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

