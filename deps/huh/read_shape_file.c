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

    printf( "usage: huh <shapefile> (without file.extension)\n" );
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

  int i;
  
  for( i = 0; i < shapeEntityCount; i++ ) {

    shape = SHPReadObject( shapeHandle, i );

    printf( "\ntype: %i\n", shape->nSHPType );
    printf( "id: %i\n", shape->nShapeId );
    printf( "parts: %i\n", shape->nParts );
    printf( "vertex count: %i\n", shape->nVertices );

    SHPDestroyObject( shape );

  }

  SHPClose( shapeHandle );


  return 0;
}
