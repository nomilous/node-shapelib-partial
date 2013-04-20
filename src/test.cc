#include <node.h>
#include <v8.h>

using namespace v8;

//
// define a function that squares the passed number
// 

Handle<Value> Square(const Arguments& args) {

  HandleScope scope;

  Local<Number> num = Number::New(

    args[0]->NumberValue() * args[0]->NumberValue()

  );
  return scope.Close( num );

}


//
// export the function
// 

void square(Handle<Object> exports) {

  exports->Set(

    String::NewSymbol("square"),
    FunctionTemplate::New(Square)->GetFunction()

  );

}

NODE_MODULE(test, square)
