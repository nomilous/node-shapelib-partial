#include "shapeobject.h"

ShapeObject::ShapeObject() {};
ShapeObject::~ShapeObject() {};

bool ShapeObject::loadShape(SHPHandle shapeHandle, int shapeId) {

    id = shapeId;
    shape = ::SHPReadObject(shapeHandle, shapeId);
    if( shape == NULL) return false;

};

bool ShapeObject::loadRecord(DBFHandle dbfHandle, int recordId, int fieldCount) {

    int i;

    fields = new ObjectField[fieldCount];
    this->fieldCount = fieldCount;

    for(i = 0; i < fieldCount; i++) {

        int width;
        int decimals;


        DBFFieldType type = DBFGetFieldInfo(dbfHandle, i, fields[i].name, &width, &decimals);

        printf("\n\nfield no:%i, name:%s, width:%i, decimals:%i\n", i, fields[i].name, width, decimals);

        if( DBFIsAttributeNULL( dbfHandle, recordId, i ) ) continue;

        fields[i].type  = type;

        switch( type ) {

            case FTInteger:

                fields[i].intValue = DBFReadIntegerAttribute(dbfHandle, recordId, i);
                break;

            case FTDouble:

                fields[i].doubleValue = DBFReadDoubleAttribute(dbfHandle, recordId, i);
                break;

            case FTString:

                char * value = (char *) DBFReadStringAttribute(dbfHandle, recordId, i);
                fields[i].stringValue = new char[width + 1];
                strncpy(fields[i].stringValue, value, width + 1);
                break;

        }
        
    }

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

    printf("free parts resources\n");
    return scope.Close( Array::New() );

};

Local<Object> ShapeObject::getFields() {

    HandleScope scope;

    Local<Object> obj = Object::New();
    int i;
    for( i = 0; i < fieldCount; i++ ) {

        switch( fields[i].type ) {

            case FTString:

                obj->Set(

                    String::NewSymbol(fields[i].name),
                    String::New(fields[i].stringValue)

                );
                break;

            case FTInteger:

                obj->Set(

                    String::NewSymbol(fields[i].name),
                    Number::New(fields[i].intValue)

                );
                break;

            case FTDouble:

                obj->Set(

                    String::NewSymbol(fields[i].name),
                    Number::New(fields[i].doubleValue)
                    
                );
                break;
        }
    }

    printf("free fields resources\n");
    return scope.Close( obj );
    //return obj;

};

