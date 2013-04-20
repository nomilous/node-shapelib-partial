#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "myclass.h"

using namespace v8;

void InitAll(Handle<Object> exports) {
  MyClass::Init(exports);
}

NODE_MODULE(class, InitAll)
