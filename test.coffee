#!/usr/bin/env coffee

ShapeHandle = require('./build/Release/shapelib_bindings').ShapeHandle

shapeHandle = new ShapeHandle()


shapeHandle.open './deps/huh/kjanasdvpo3i4pfbeprjiv', (err, shapeInfo) ->
    
    console.log 'error:', err
    console.log 'shapeInfo:', shapeInfo


#shapeHandle.readObject id, (err, callback) ->
#shapeHandle.close()
#shapeHandle.openSync
#shapeHandle.readObjectSync
