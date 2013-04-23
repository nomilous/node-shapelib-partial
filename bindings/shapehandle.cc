#include "shapehandle.h"

void async_open(uv_work_t *job) {

    //
    // open the shapefile and load shapeInfo
    //

    async_open_request *request =     
        (struct async_open_request *) job->data;

    ShapeHandle *handle = (ShapeHandle *) request->handle;
    handle->SHPOpen( request->error, request->filename );


    //printf("async_open(   '''''%s'''''    )\n", request->filename);

}


void async_open_after(uv_work_t * job, int) {


    HandleScope scope;

    async_open_request *request =     
        (struct async_open_request *) job->data;

    const unsigned argc = 2;
    Handle<Value> argv[argc];
    
    argv[0] = Undefined();
    argv[1] = Undefined();

    if( request->error->code > 0 ) {

        argv[0] = Exception::Error(String::New(request->error->message.c_str()));

    }

    request->callback->Call( Context::GetCurrent()->Global(), argc, argv );


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


void ShapeHandle::SHPOpen( error_struct * error, char * filename ) {

    shapeHandle = ::SHPOpen(filename, "rb");

    if( shapeHandle == NULL ) {

        error->code = 1;
        error->message = "Unable to open shape file.";
        return;

    }

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
    async_open_request * request;
    uv_work_t * job;

    if (args.Length() != 2) {
        return ThrowException(
            Exception::Error(String::New(
                "Expected ShapeHandle::Open(<filename>,<callback>)"))
        );
    }

    //
    // assemble request parameters 
    //

    String::Utf8Value filename(args[0]);
    request = (async_open_request *) malloc(
        sizeof(struct async_open_request) + filename.length() + 1
    );
    request->callback = Persistent<Function>::New(
        Local<Function>::Cast(args[1])
    );
    request->error = new error_struct;
    request->error->code = 0;
    request->handle = ObjectWrap::Unwrap<ShapeHandle>(args.This());
    strncpy( request->filename, *filename, filename.length() + 1 );

    job = new uv_work_t;
    job->data = request;

    uv_queue_work( uv_default_loop(), job, async_open, async_open_after );


    //
    // may entirely do away with this being a class
    // 
    // ShapeHandle* obj = ObjectWrap::Unwrap<ShapeHandle>(args.This());
    // return scope.Close(Boolean::New(true));
    //
    return Undefined();

}
