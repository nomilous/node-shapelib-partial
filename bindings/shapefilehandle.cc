#include "shapefilehandle.h"

void async_open(uv_work_t * request) {

    //
    // Running this async request (job) on the background
    // uv_default_loop()
    //

    ShapeFileHandle * handle = (ShapeFileHandle *) request->data;
    
    if( ! handle->Open() ) { return; }
    if( ! handle->ReadShapeObjects() ) { return; }

}

void async_open_after(uv_work_t * request, int) {

    //
    // Upon completion of the request (job)
    // 
    //  - marshal the results into v8 JS objects and
    //    post them to the callback  
    // 

    HandleScope scope;

    const unsigned argc = 2;
    Handle<Value> argv[argc];

    argv[0] = Undefined();
    argv[1] = Undefined();

    ShapeFileHandle * handle = (ShapeFileHandle *) request->data;

    if( handle->getErrorCode() > 0 ) {
        argv[0] = Exception::Error(String::New(handle->getErrorMessage().c_str()));
    } else {

        Local<Object> obj = Object::New();
        obj->Set(
            String::NewSymbol("count"), 
            Number::New(handle->getShapeCount())
        );

        obj->Set(
            String::NewSymbol("type"), 
            Number::New(handle->getShapeType())
        );

        Local<Array> minBound = Array::New(4);
        Local<Array> maxBound = Array::New(4);

        int i;
        for( i = 0; i < 4; i++) {
            minBound->Set(Number::New(i), Number::New( handle->getShapeMinBound()[i] ));
            maxBound->Set(Number::New(i), Number::New( handle->getShapeMaxBound()[i] ));
        }

        obj->Set(
            String::NewSymbol("minBound"), 
            minBound
        );

        obj->Set(
            String::NewSymbol("maxBound"), 
            maxBound
        );

        obj->Set(
            String::NewSymbol("shapes"),
            handle->getShapeObjects()
        );

        argv[1] = obj;

    }

    TryCatch try_catch;
    handle->getCallback()->Call( Context::GetCurrent()->Global(), argc, argv );
    handle->getCallback().Dispose();
    handle->Close();
    delete request;

    if (try_catch.HasCaught())
        FatalException(try_catch);
 
    //printf("free() resources");
    
};


void ShapeFileHandle::Init(Handle<Object> exports) {

    //
    // Assemble and export the v8 JS function prototype 
    //

    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

    tpl->SetClassName(String::NewSymbol("ShapeFile"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    tpl->PrototypeTemplate()->Set(
        String::NewSymbol("open"),
        FunctionTemplate::New(OpenAsync)->GetFunction()
    );

    Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("ShapeFile"), constructor);

};

Handle<Value> ShapeFileHandle::New(const Arguments& args) {

    //
    // JS prototype constructor
    // 
    //    -  wraps *this to propagate context into exported prototype functions
    //

    HandleScope scope;
    ShapeFileHandle* obj = new ShapeFileHandle();
    obj->Wrap(args.This());
    return args.This();

};


Handle<Value> ShapeFileHandle::OpenAsync(const Arguments& args) {

    //
    // JS exported prototype function 
    // 
    //    - un-wrap *this to restore context
    //    - build a request (with the context) to post onto async uv_queue
    //

    HandleScope scope;
    uv_work_t * request;

    if (args.Length() != 2) {
        return ThrowException(
            Exception::Error(String::New(
                "Expected ShapeFileHandle::OpenAsync(<filename>,<callback>)"))
        );
    }

    ShapeFileHandle * obj = ObjectWrap::Unwrap<ShapeFileHandle>(args.This());

    obj->setFilename(

        //
        // arg1 as the shape filename
        //

        *String::Utf8Value(args[0]->ToString())

    );

    obj->setCallback(

        //
        // arg2 as the callback `function(error, shapes) { };`
        // 

        Persistent<Function>::New(Local<Function>::Cast(args[1]))

    );

    obj->setError(0,"");

    request = new uv_work_t;
    request->data = obj;

    uv_queue_work( uv_default_loop(), request, async_open, async_open_after );

    return Undefined();

};


bool ShapeFileHandle::Open() {

    shapeHandle = SHPOpen(filename.c_str(), "rb");
    dbfHandle = DBFOpen(filename.c_str(), "rb");

    if( dbfHandle != NULL ) {
        dbfFieldCount = DBFGetFieldCount(dbfHandle);
        dbfRecordCount = DBFGetRecordCount(dbfHandle);
    }

    //
    // failure to open DBF file is ignored externally
    // ie. no error is loaded
    //

    if( shapeHandle == NULL ) {
        errorCode = 1;
        errorMessage = "Unable to open shape file.";
        return false;
    }

    return true;

};

bool ShapeFileHandle::Close() {

    if( shapeHandle != NULL ) SHPClose(shapeHandle);
    if( dbfHandle != NULL ) DBFClose(dbfHandle);
    return true;
    
};

bool ShapeFileHandle::ReadShapeObjects() {

    SHPGetInfo(shapeHandle, 
        &shapeCount, 
        &shapeType,
        shapeMinBound, 
        shapeMaxBound
    );

    shapeObjects = new ShapeObject[shapeCount];

    int i;
    for(i = 0; i < shapeCount; i++) {

        //
        // first version loads all shapes...
        //
        // - this may be undesirable for really large shape files
        //   and should rether become an overidable default with
        //   the loader accessable through an async call from the
        //   js side to allow for loading only specific shapes
        //   from the file.
        //

        shapeObjects[i].loadShapeHandle(shapeHandle, i);
        if( dbfHandle != NULL ) { 
            if( dbfRecordCount == shapeCount ) {

                shapeObjects[i].loadRecordHandle(dbfHandle, i, dbfFieldCount);

            }
        }
    }

    return true;

};

Local<Array> ShapeFileHandle::getShapeObjects() {

    //
    // return shape objects as v8 JS array 
    // 

    HandleScope scope;
    int i;
    Local<Array> shapes = Array::New(shapeCount);

    for( i = 0; i < shapeCount; i++ ) {

        shapes->Set(

            Number::New(i), 
            shapeObjects[i].getObject()

        );

    }

    return scope.Close( shapes );

};


ShapeFileHandle::ShapeFileHandle() {};
ShapeFileHandle::~ShapeFileHandle() {};

int ShapeFileHandle::getShapeCount() {
    return shapeCount;
};

int ShapeFileHandle::getShapeType() {
    return shapeType;
};

double * ShapeFileHandle::getShapeMinBound() {
    return shapeMinBound;
};

double * ShapeFileHandle::getShapeMaxBound() {
    return shapeMaxBound;
};

void ShapeFileHandle::setFilename(string filename) {
    this->filename = filename;
};

string ShapeFileHandle::getFilename() {
    return filename;
};

void ShapeFileHandle::setCallback(Persistent<Function> callback) {
    this->callback = callback;
};

Persistent<Function> ShapeFileHandle::getCallback() {
    return callback;
};

void ShapeFileHandle::setError(int code, string message) {
    errorCode = code;
    errorMessage = message;
};

int ShapeFileHandle::getErrorCode() {
    return errorCode;
};

string ShapeFileHandle::getErrorMessage() {
        return errorMessage;
};
