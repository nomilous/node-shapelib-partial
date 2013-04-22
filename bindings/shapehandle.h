#ifndef SHAPEHANDLE_H
#define SHAPEHANDLE_H

#include <node.h>
#include <v8.h>
#include <string>
#include <stdlib.h>
#include <node_buffer.h>
#include "shapefil.h"

using namespace std;
using namespace node;
using namespace v8;

class ShapeHandle : public node::ObjectWrap {

    public:

        static void Init( Handle<Object> exports );

    private:

        ShapeHandle();
        ~ShapeHandle();

        static Handle<Value> New(const Arguments& args);
        static Handle<Value> OpenAsync(const Arguments& args);

};

struct async_open_request {

    Persistent<Function> callback;
    char filename[1]; // gets mallocd up to size

};

void async_open(uv_work_t * job);
void async_open_after(uv_work_t * job, int);

#endif
