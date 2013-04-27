#!/usr/bin/env coffee

ShapeFile = require('./build/Release/shapelib_bindings').ShapeFile

shapeFile = new ShapeFile()


shapeFile.open './deps/huh/ne_110m_land', (err, shapeData) ->
    
    # console.log open:

    #     error: err
    #     data: shapeData

    # for i in [0..shapeData.count-1]

    #     console.log shapeData.shapes[i]


    
    console.log shapeData.shapes[126].vertices[0]
#shapeHandle.close()
#shapeHandle.openSync
#shapeHandle.readObjectSync
