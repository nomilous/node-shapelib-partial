#ifndef SHAPEHANDLE_H
#define SHAPEHANDLE_H

#include <node.h>
#include "shapefil.h"

class ShapeHandle : public node::ObjectWrap {

    public:

        static void Init( v8::Handle<v8::Object> exports );

    private:

        ShapeHandle();
        ~ShapeHandle();

        static v8::Handle<v8::Value> New(const v8::Arguments& args);

};

#endif