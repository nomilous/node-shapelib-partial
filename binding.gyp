{
  'targets': [
    {
      'target_name': 'shapelib_bindings',
      'sources': [
          'bindings/shapelib.cc',
          'bindings/shapefilehandle.cc'
      ],
      'dependencies': [
        'deps/shapelib/libshp.gyp:shp'
      ]
    }
  ]
}
