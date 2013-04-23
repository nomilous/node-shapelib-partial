#include "shapehandle.h"

void async_open(uv_work_t * job) {

    ShapeHandle * handle = (ShapeHandle *) job->data;
    
    if( ! handle->SHPOpen() ) { return; }
    if( ! handle->SHPGetInfo() ) { return; }

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
    } else {

        Local<Object> obj = Object::New();
        obj->Set(
            String::NewSymbol("entities"), 
            Number::New(handle->getShapeEntities())
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

        argv[1] = obj;

    }

    handle->getCallback()->Call( Context::GetCurrent()->Global(), argc, argv );

    //
    // and free() resources
    //

}

ShapeHandle::ShapeHandle() {};
ShapeHandle::~ShapeHandle() {};

bool ShapeHandle::SHPOpen() {

    shapeHandle = ::SHPOpen(filename.c_str(), "rb");

    if( shapeHandle == NULL ) {
        errorCode = 1;
        errorMessage = "Unable to open shape file.";
        return false;
    }

    return true;

};

bool ShapeHandle::SHPGetInfo() {

    ::SHPGetInfo(shapeHandle, 
        &shapeEntities, 
        &shapeType,
        shapeMinBound, 
        shapeMaxBound
    );

    return true;

};

int ShapeHandle::getShapeEntities() {
    return shapeEntities;
};

int ShapeHandle::getShapeType() {
    return shapeType;
};

double * ShapeHandle::getShapeMinBound() {
    return shapeMinBound;
};

double * ShapeHandle::getShapeMaxBound() {
    return shapeMaxBound;
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

    //printf("ShapeHandle::Init()\n");
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

    //printf("ShapeHandle::New()\n");
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
