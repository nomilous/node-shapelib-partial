#!/usr/bin/env coffee

ShapeHandle = require('./build/Release/shapelib_bindings').ShapeHandle

shapeHandle = new ShapeHandle()


shapeHandle.open './deps/huh/ne_110m_land', (err, shapeInfo) ->
    
    #console.log 'error:', err
    console.log shapeInfo


#shapeHandle.readObject id, (err, callback) ->
#shapeHandle.close()
#shapeHandle.openSync
#shapeHandle.readObjectSync
