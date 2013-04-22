#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "shapehandle.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  ShapeHandle::Init(exports);
}

NODE_MODULE(shapelib_bindings, InitAll)
