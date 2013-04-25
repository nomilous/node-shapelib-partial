#!/usr/bin/env coffee

ShapeHandle = require('./build/Release/shapelib_bindings').ShapeHandle

shapeHandle = new ShapeHandle()


shapeHandle.open './deps/huh/ne_110m_land', (err, shapeInfo) ->
    
    console.log open:

        error: err
        shapeInfo: shapeInfo


    # 
    # for id in [0..shapeInfo.entities-1]
    #  
    # internal shared handle means no support for concurrent async
    # read from the shapeHandle, use a waterfall this side of the
    # binding.  
    # 

    shapeHandle.readObject 0, (err, shape) ->

        console.log readObject:
            
            error: err
            shape: shape

    


#shapeHandle.close()
#shapeHandle.openSync
#shapeHandle.readObjectSync
