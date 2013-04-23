#include "shapehandle.h"

void async_open(uv_work_t * job) {

    ShapeHandle * handle = (ShapeHandle *) job->data;
    handle->SHPOpen();

}


void async_open_after(uv_work_t * job, int) {

    HandleScope scope;

    const unsigned argc = 2;
    Handle<Value> argv[argc];

    argv[0] = Undefined();
    argv[1] = Undefined();

    ShapeHandle * handle = (ShapeHandle *) job->data;

    if( handle->getErrorCode() > 0 ) {
        argv[0] = Exception::Error(String::New(handle->getErrorMessage().c_str()));
    }

    handle->getCallback()->Call( Context::GetCurrent()->Global(), argc, argv );


    //
    // and free() resources
    //

}

ShapeHandle::ShapeHandle() {

    printf("ShapeHandle::ShapeHandle()\n");
    
    //
    // pending push into async operation with .open( <shapefile>, callback )
    //

    // int shapeEntityCount;
    // int shapeType;
    // double minBounds[4];
    // double maxBounds[4];

    // SHPHandle shapeHandle;

    // shapeHandle = SHPOpen( "./deps/huh/ne_110m_land", "rb" );
    // SHPGetInfo( shapeHandle, &shapeEntityCount, &shapeType, minBounds, maxBounds );
    // printf( "entities: %i, type: %i\n", shapeEntityCount, shapeType );
    // printf( "min bounds: %f, %f, %f\n", minBounds[0], minBounds[1], minBounds[2] );
    // printf( "max bounds: %f, %f, %f\n", maxBounds[0], maxBounds[1], maxBounds[2] );

    // SHPClose( shapeHandle );

};

ShapeHandle::~ShapeHandle() {
    printf("ShapeHandle::~ShapeHandle()\n");
};


void ShapeHandle::SHPOpen() {

    shapeHandle = ::SHPOpen(filename.c_str(), "rb");

    if( shapeHandle == NULL ) {
        errorCode = 1;
        errorMessage = "Unable to open shape file.";
        return;
    }

};


void ShapeHandle::setFilename(string filename) {
    this->filename = filename;
};

string ShapeHandle::getFilename() {
    return filename;
};

void ShapeHandle::setCallback(Persistent<Function> callback) {
    this->callback = callback;
};

Persistent<Function> ShapeHandle::getCallback() {
    return callback;
};

void ShapeHandle::setError(int code, string message) {
    errorCode = code;
    errorMessage = message;
};

int ShapeHandle::getErrorCode() {
    return errorCode;
};

string ShapeHandle::getErrorMessage() {
        return errorMessage;
};

void ShapeHandle::Init(Handle<Object> exports) {

    printf("ShapeHandle::Init()\n");
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

    tpl->SetClassName(String::NewSymbol("ShapeHandle"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(
        String::NewSymbol("open"),
        FunctionTemplate::New(OpenAsync)->GetFunction()
    );

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

Handle<Value> ShapeHandle::OpenAsync(const Arguments& args) {

    HandleScope scope;
    uv_work_t * job;

    if (args.Length() != 2) {
        return ThrowException(
            Exception::Error(String::New(
                "Expected ShapeHandle::Open(<filename>,<callback>)"))
        );
    }

    ShapeHandle* obj = ObjectWrap::Unwrap<ShapeHandle>(args.This());

    obj->setFilename(*String::Utf8Value(args[0]->ToString()));
    obj->setCallback(Persistent<Function>::New(Local<Function>::Cast(args[1])));
    obj->setError(0,"");

    job = new uv_work_t;
    job->data = obj;

    uv_queue_work( uv_default_loop(), job, async_open, async_open_after );

    return Undefined();

}
