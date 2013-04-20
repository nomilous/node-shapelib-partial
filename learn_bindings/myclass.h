#ifndef MYCLASS_H
#define MYCLASS_H

#include <node.h>

class MyClass : public node::ObjectWrap {
 public:

  //
  // Init to assemble the object('class')
  //

  static void Init(v8::Handle<v8::Object> exports);


 private:
  
  MyClass();
  ~MyClass();



  //
  // New() new class contructor
  //

  static v8::Handle<v8::Value> New(const v8::Arguments& args);

  //
  // Increment() as class method
  //

  static v8::Handle<v8::Value> Increment(const v8::Arguments& args);

  //
  // class variable
  //

  double counter_;


};

#endif
