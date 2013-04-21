#include <stdlib.h>
#include "string.h"
#include "shapefil.h"


//
// file name from argv[1]
//

char shapeFile[100];

//
// SHPHandle holds the open shape file
//

SHPHandle shapeHandle;

int shapeEntityCount;
int shapeType;
double minBounds[4];  // x,y,z,m boundries minimum
double maxBounds[4];  // max


//
// SHPObject for each extracted object
//

SHPObject *shape;


int main( int argc, char ** argv )
{

  if( argc < 2 ) { 

    printf( "usage: shape_read_file <shapefile> (without file.extension)\n" );
    return;

  }

  strcpy( shapeFile, argv[1] );
  printf( "loading shape file: %s\n", shapeFile );

  //
  // load shape file
  //

  shapeHandle = SHPOpen( shapeFile, "rb" );
  SHPGetInfo( shapeHandle, &shapeEntityCount, &shapeType, minBounds, maxBounds );
  printf( "entities: %i, type: %i\n", shapeEntityCount, shapeType );


  printf( "min bounds: %f, %f, %f\n", minBounds[0], minBounds[1], minBounds[2] );
  printf( "max bounds: %f, %f, %f\n", maxBounds[0], maxBounds[1], maxBounds[2] );

  int i, j;
  for( i = 0; i < shapeEntityCount; i++ ) {
  //for( i = 0; i < 1; i++ ) {

    shape = SHPReadObject( shapeHandle, i );

    printf( "\ntype: %i\n", shape->nSHPType );
    printf( "id: %i\n", shape->nShapeId );
    printf( "parts: %i\n", shape->nParts );
    printf( "vertex count: %i\n", shape->nVertices );

    for( j = 0; j < shape->nVertices; j++ ) {

      printf( "%f, %f, %f, %f\n", shape->padfX[j], shape->padfY[j], shape->padfZ[j], shape->padfM[j] );

    }

    SHPDestroyObject( shape );

  }

  SHPClose( shapeHandle );

  return 0;

}
