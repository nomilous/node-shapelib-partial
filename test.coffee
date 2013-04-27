#!/usr/bin/env coffee

ShapeFile = require('./build/Release/shapelib_bindings').ShapeFile

shapeFile = new ShapeFile()


shapeFile.open './deps/huh/ne_110m_land', (err, shapeData) ->
    
    console.log open:

        error: err
        data: shapeData


    # 
    # for id in [0..shapeInfo.entities-1]
    #  
    # internal shared handle means no support for concurrent async
    # read from the shapeHandle, use a waterfall this side of the
    # binding.  
    # 

    # shapeFile.readObject 0, (err, shape) ->

    #     console.log readObject:
            
    #         error: err
    #         shape: shape

    


#shapeHandle.close()
#shapeHandle.openSync
#shapeHandle.readObjectSync
