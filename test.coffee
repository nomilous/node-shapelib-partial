#!/usr/bin/env coffee

ShapeHandle = require('./build/Release/shapelib_bindings').ShapeHandle

shapeHandle = new ShapeHandle()


shapeHandle.open './deps/huh/ne_110m_land', (err, shapeInfo) ->
    
    console.log 'open:', 
        error: err
        shapeInfo: shapeInfo


    for id in [0..shapeInfo.entities-1]

        shapeHandle.readObject id, (err, shape) ->

            console.log 'readObject:',
                error: err
                shape: shape


#shapeHandle.close()
#shapeHandle.openSync
#shapeHandle.readObjectSync
