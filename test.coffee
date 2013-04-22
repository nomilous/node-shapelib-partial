#!/usr/bin/env coffee

ShapeHandle = require('./build/Release/shapelib_bindings').ShapeHandle

shapeHandle = new ShapeHandle()

shapeHandle.open './build/Release/shapelib_bindings' 



console.log shapeHandle
