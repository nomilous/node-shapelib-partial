#ifndef SHAPEHANDLE_H
#define SHAPEHANDLE_H

#include <node.h>
#include <v8.h>
#include <string>
#include <stdlib.h>
#include "shapefil.h"

using namespace std;
using namespace node;
using namespace v8;

class ShapeHandle : public ObjectWrap {

    public:

        static void Init( Handle<Object> exports );

        void setFilename(string filename);
        void setCallback(Persistent<Function>);
        void setError(int code, string message);

        string getFilename();
        Persistent<Function> getCallback();
        int getErrorCode();
        string getErrorMessage();

        bool SHPOpen();
        bool SHPGetInfo();
        bool SHPReadObject();

        int getShapeEntities();
        int getShapeType();
        double * getShapeMinBound();
        double * getShapeMaxBound();

    private:

        ShapeHandle();
        ~ShapeHandle();

        static Handle<Value> New(const Arguments& args);
        static Handle<Value> OpenAsync(const Arguments& args);
        static Handle<Value> ReadObjectAsync(const Arguments& args);

        SHPHandle shapeHandle;
        int shapeEntities;
        int shapeType;
        double shapeMinBound[4];
        double shapeMaxBound[4];

        string filename;
        Persistent<Function> callback;
        int errorCode;
        string errorMessage;



};

void async_open(uv_work_t * job);
void async_open_after(uv_work_t * job, int);

void async_read_object(uv_work_t * job);
void async_read_object_after(uv_work_t * job, int);

#endif
