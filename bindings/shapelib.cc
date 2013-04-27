#include <node.h>
#include "shapefilehandle.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
    ShapeFileHandle::Init(exports);
}

NODE_MODULE(shapelib_bindings, InitAll)
