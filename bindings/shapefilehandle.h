#ifndef SHAPEFILEHANDLE_H
#define SHAPEFILEHANDLE_H

/******************************************************************************

Handle the shape file

******************************************************************************/

#include <node.h>
#include <v8.h>
#include <string>
#include <stdlib.h>
#include "shapefil.h"
#include "shapeobject.h"

using namespace std;
using namespace node;
using namespace v8;

class ShapeFileHandle : public ObjectWrap {

    public:

        static void Init( Handle<Object> exports );

        void setFilename(string filename);
        void setCallback(Persistent<Function>);
        void setError(int code, string message);

        string getFilename();
        Persistent<Function> getCallback();
        int getErrorCode();
        string getErrorMessage();
        Local<Array> getShapeObjects();

        bool Open();
        bool ReadShapeObjects();
        bool Close();

        int getShapeCount();
        int getShapeType();
        double * getShapeMinBound();
        double * getShapeMaxBound();

    private:

        ShapeFileHandle();
        ~ShapeFileHandle();

        static Handle<Value> New(const Arguments& args);
        static Handle<Value> OpenAsync(const Arguments& args);

        SHPHandle shapeHandle;  //   *.shp
        DBFHandle dbfHandle;    //   *.dbf

        ShapeObject * shapeObjects;

        int shapeCount;
        int shapeType;
        double shapeMinBound[4];
        double shapeMaxBound[4];

        int dbfRecordCount;     // will usually match n shapes in the .shp file
        int dbfFieldCount;      // fields per record

        string filename;
        Persistent<Function> callback;
        int errorCode;
        string errorMessage;

};

void async_open(uv_work_t * job);
void async_open_after(uv_work_t * job, int);

#endif
