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



int main( int argc, char ** argv )
{

  if( argc < 2 ) { 

    printf( "usage: huh <shapefile> (without file.extension)\n" );
    return;

  }

  strcpy( shapeFile, argv[1] );
  printf( "loading shape file: %s\n", shapeFile );

  
  shapeHandle = SHPOpen( shapeFile, "rb" );



  return 0;
}
