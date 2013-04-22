#include <node.h>
#include "shapehandle.h"

using namespace v8;

ShapeHandle::ShapeHandle() {

    printf("ShapeHandle::ShapeHandle()\n");
    
    int shapeEntityCount;
    int shapeType;
    double minBounds[4];
    double maxBounds[4];

    SHPHandle shapeHandle;

    shapeHandle = SHPOpen( "./deps/huh/ne_110m_land", "rb" );
    SHPGetInfo( shapeHandle, &shapeEntityCount, &shapeType, minBounds, maxBounds );
    printf( "entities: %i, type: %i\n", shapeEntityCount, shapeType );
    printf( "min bounds: %f, %f, %f\n", minBounds[0], minBounds[1], minBounds[2] );
    printf( "max bounds: %f, %f, %f\n", maxBounds[0], maxBounds[1], maxBounds[2] );

    SHPClose( shapeHandle );

};

ShapeHandle::~ShapeHandle() {
    printf("ShapeHandle::~ShapeHandle()\n");
};

void ShapeHandle::Init(Handle<Object> exports) {

    printf("ShapeHandle::Init()\n");
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("ShapeHandle"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("ShapeHandle"), constructor);

}

Handle<Value> ShapeHandle::New(const Arguments& args) {

    printf("ShapeHandle::New()\n");
    HandleScope scope;
    ShapeHandle* obj = new ShapeHandle();
    obj->Wrap(args.This());
    return args.This();

}
