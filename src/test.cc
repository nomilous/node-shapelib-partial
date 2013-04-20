#include <node.h>
#include <v8.h>

using namespace v8;

//
// define a function that squares the passed number
// 

Handle<Value> Square(const Arguments& args) {

  HandleScope scope;

  //
  // get callback from arg1
  //

  Local<Function> callback = Local<Function>::Cast(args[1]);

  //
  // calling back needs argCount and argArray
  //

  const unsigned argc = 1;
  Local<Value> argv[argc] = Number::New(

    //
    // calculate squared value to call back
    //

    args[0]->NumberValue() * args[0]->NumberValue()

  );
  


  callback->Call(

    Context::GetCurrent()->Global(), argc, argv

  );

  return scope.Close( Undefined() );

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
