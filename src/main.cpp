#include <iostream>
#include <stdlib.h>

#include "DateTime.h"

int main( int argc, char **argv )
{
  DateTime *dt = DateTime::Now( );
  std::cout << dt->GetShortTimeString( ) << std::endl;
  std::cout << dt->GetShortDateString( ) << std::endl;
  return EXIT_SUCCESS;
}
