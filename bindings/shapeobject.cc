#include "shapeobject.h"

ShapeObject::ShapeObject() {};
ShapeObject::~ShapeObject() {};

bool ShapeObject::loadShape(SHPHandle shapeHandle, int shapeId) {

    id = shapeId;
    shape = ::SHPReadObject(shapeHandle, shapeId);
    if( shape == NULL) return false;

};

bool ShapeObject::loadRecord(DBFHandle dbfHandle, int recordId) {

};

Local<Object> ShapeObject::getObject() {

    HandleScope scope;
    Local<Object> jsShape = Object::New();

    jsShape->Set(

        String::NewSymbol("id"),
        Number::New(id)

    );

    jsShape->Set(

        //
        // shape can have multiple parts 
        //

        String::NewSymbol("parts"),
        getParts()

    );

    return scope.Close( jsShape );

};


Local<Object> ShapeObject::getParts() {

    HandleScope scope;
    return scope.Close( Object::New() );

};

