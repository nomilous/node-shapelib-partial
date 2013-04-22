#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "shapehandle.h"

using namespace v8;

ShapeHandle::ShapeHandle() {};
ShapeHandle::~ShapeHandle() {};

void ShapeHandle::Init(Handle<Object> exports) {

  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("ShapeHandle"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("ShapeHandle"), constructor);

}

Handle<Value> ShapeHandle::New(const Arguments& args) {

  HandleScope scope;
  ShapeHandle* obj = new ShapeHandle();
  obj->Wrap(args.This());
  return args.This();

}
