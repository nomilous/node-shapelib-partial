
Node bindings for [shapelib.maptools.org](http://shapelib.maptools.org/)'s implementation of the [ESRI](http://www.esri.com/) shapefile specification with [libuv](http://nikhilm.github.io/uvbook/index.html) for async file access and decode.

### Current version

0.0.1


### Disclaimer

Only implements reading shapefiles (no write).<br />
No tests.<br />
My first attempt at node binding to a c library<br />
It occasionally segfaults. (don't know why - c is not my thing)<br />


### Usage

```bash
npm install node-shapelib-partial
```

```coffee

ShapeFile = require('node-shapelib-partial').ShapeFile
shapeFile = new ShapeFile()

shapeFile.open './shape/shape_file_basename', (error, shapeData) -> 
    
    # 
    # callback with shapeData
    # 


```
