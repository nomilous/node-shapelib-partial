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

gcc -I ../shapelib ../shapelib/libshp.a huh.c -o huh && ./huh ne_110m_land


```