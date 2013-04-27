binding = require('../build/Release/shapelib_bindings').ShapeFile

module.exports = class ShapeFile

    open: (filename, callback) -> 

        (new binding).open filename, callback
