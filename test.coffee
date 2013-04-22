#!/usr/bin/env coffee

ShapeHandle = require('./build/Release/shapelib_bindings').ShapeHandle

shapeHandle = new ShapeHandle( './deps/huh/ne_110m_land' )

console.log shapeHandle
