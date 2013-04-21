### Sample data

Earth landmass polygons, including major islands. From [Natural Earth](http://www.naturalearthdata.com/), with much appreciation!


```bash

wget http://www.naturalearthdata.com/http//www.naturalearthdata.com/download/110m/physical/ne_110m_land.zip
unzip ne_110m_land.zip

```

### build shapelib

```bash

cd ../shapelib
make

#
# runs fine on osx
#

```

### compile and run `huh`

```bash

gcc -I ../shapelib ../shapelib/libshp.a read_shape_file.c -o read_shape_file && ./read_shape_file ne_110m_land | head -n 20


loading shape file: ne_110m_land
entities: 127, type: 5
min bounds: -180.000000, -90.000000, 0.000000
max bounds: 180.000000, 83.645130, 0.000000

type: 5
id: 0
parts: 1
vertex count: 13
-59.572095, -80.040179, 0.000000, 0.000000
-59.865849, -80.549657, 0.000000, 0.000000
-60.159656, -81.000327, 0.000000, 0.000000
-62.255393, -80.863178, 0.000000, 0.000000
-64.488125, -80.921934, 0.000000, 0.000000
-65.741666, -80.588827, 0.000000, 0.000000
-65.741666, -80.549657, 0.000000, 0.000000
-66.290031, -80.255773, 0.000000, 0.000000
-64.037688, -80.294944, 0.000000, 0.000000
-61.883246, -80.392870, 0.000000, 0.000000
-61.138976, -79.981371, 0.000000, 0.000000



```