#!/usr/bin/env coffee

ShapeHandle = require('./build/Release/shapelib_bindings').ShapeHandle

shapeHandle = new ShapeHandle()

shapeHandle.open './deps/huh/ne_110_land', (err, shapeInfo) ->
    
    console.log 'error:', err
    console.log 'shapeInfo:', shapeInfo

