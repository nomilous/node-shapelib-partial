#define BUILDING_NODE_EXTENSION
#include <node.h>

using namespace v8;


Handle<Value> CreateObject(const Arguments& args) {

  HandleScope scope;

  Local<Object> obj = Object::New();

  obj->Set(

    String::NewSymbol("key1"), args[0]->ToString()

  );

  obj->Set(

    String::NewSymbol("key2"), args[1]->ToString()

  );

  return scope.Close(obj);
}


void Init(Handle<Object> exports, Handle<Object> module) {

  module->Set(

    //
    // export as 'exports'
    // 

    String::NewSymbol("exports"),
    FunctionTemplate::New(CreateObject)->GetFunction()

  );

}

NODE_MODULE(object, Init)
