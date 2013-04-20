#define BUILDING_NODE_EXTENSION
#include <node.h>

using namespace v8;


Handle<Value> Multiply(const Arguments& args) {

  HandleScope scope;
  return scope.Close(

    Number::New(
    
      args[0]->NumberValue() * args[0]->NumberValue()

    )

  );

}

//
// return a function
//

Handle<Value> CreateFunction(const Arguments& args) {

  HandleScope scope;

  Local<FunctionTemplate> tpl = FunctionTemplate::New(Multiply);
  Local<Function> fn = tpl->GetFunction();
  fn->SetName(String::NewSymbol("function")); // omit this to make it anonymous

  return scope.Close(fn);

}



//
// execute a callback
// 

Handle<Value> RunFunction(const Arguments& args) {

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

void Init(Handle<Object> exports) {

  //
  // exports = multiply (run a function)
  //

  exports->Set(

    String::NewSymbol("multiply"),
    FunctionTemplate::New(Multiply)->GetFunction()

  );

  //
  // exports = function (return the function)
  //

  exports->Set(

    String::NewSymbol("function"),
    FunctionTemplate::New(CreateFunction)->GetFunction()

  );

  //
  // exports = callback (runs a callback)
  //

  exports->Set(

    String::NewSymbol("callback"),
    FunctionTemplate::New(RunFunction)->GetFunction()

  );

}

NODE_MODULE(function, Init)
