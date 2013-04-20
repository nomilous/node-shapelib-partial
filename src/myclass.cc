#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "myclass.h"

using namespace v8;

MyClass::MyClass() {};
MyClass::~MyClass() {};

void MyClass::Init(Handle<Object> exports) {

  //
  // Prepare the constructor template
  //

  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

  tpl->SetClassName(String::NewSymbol("MyClass"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);


  //
  // Prepare the prototype template
  // 

  tpl->PrototypeTemplate()->Set(

    String::NewSymbol("increment"),
    FunctionTemplate::New(Increment)->GetFunction()

  );


  //
  // Assemble and export the javascript object ('class')
  // 

  Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
  exports->Set(String::NewSymbol("MyClass"), constructor);

}


//
// The constructor
// 

Handle<Value> MyClass::New(const Arguments& args) {

  HandleScope scope;

  MyClass* obj = new MyClass();
  obj->counter_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
  obj->Wrap(args.This());

  return args.This();

}

Handle<Value> MyClass::Increment(const Arguments& args) {

  HandleScope scope;

  //
  // 'this' is accessable from args.This()
  //

  MyClass* obj = ObjectWrap::Unwrap<MyClass>(args.This());
  obj->counter_ += 1;

  return scope.Close(Number::New(obj->counter_));

}
