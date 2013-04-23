#ifndef SHAPEHANDLE_H
#define SHAPEHANDLE_H

#include <node.h>
#include <v8.h>
#include <string>
#include <stdlib.h>
#include <node_buffer.h>
#include "shapefil.h"

#define THROW_ERROR_EXCEPTION(x) ThrowException(Exception::Error(String::New(x)))

using namespace std;
using namespace node;
using namespace v8;

struct error_struct {

  int code;
  string message;

};

class ShapeHandle : public node::ObjectWrap {

    public:

        static void Init( Handle<Object> exports );
        void SHPOpen( error_struct * error, char * filename );

    private:

        ShapeHandle();
        ~ShapeHandle();

        static Handle<Value> New(const Arguments& args);
        static Handle<Value> OpenAsync(const Arguments& args);

        SHPHandle shapeHandle;

};

struct async_open_request {

    Persistent<Function> callback;
    ShapeHandle * handle;
    error_struct * error;
    char filename[1]; // gets mallocd up to size

};

void async_open(uv_work_t * job);
void async_open_after(uv_work_t * job, int);

#endif
