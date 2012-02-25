#include <iostream>
#include <stdlib.h>

#include "DateTime.h"

int main( int argc, char **argv )
{
  DateTime *now = DateTime::Now( );
  DateTime *dt = new DateTime( 21, 2, 2012, 12, 0, 0 );
  std::cout << dt->GetLongTimeString( ) << std::endl;
  std::cout << dt->GetLongDateString( ) << std::endl;
  std::cout << dt->GetTimestamp( ) << std::endl;

  dt->AddDays( 35 );
  dt->AddSeconds( 70 );

  std::cout << dt->GetLongTimeString( ) << std::endl;
  std::cout << dt->GetLongDateString( ) << std::endl;

  TimeSpan *ts = new TimeSpan( 100 );

  dt->Add( ts );

  std::cout << dt->GetLongTimeString( ) << std::endl;
  std::cout << dt->GetLongDateString( ) << std::endl;

  std::cout << now->GetTimestamp( ) << std::endl;
  std::cout << dt->GetTimestamp( ) << std::endl;

  std::cout << now->GetAsString( ) << std::endl;
  std::cout << dt->GetAsString( ) << std::endl;

  std::cout << "Comparisation:" << std::endl;
  if( now < dt )
  {
    std::cout << "Now is less then other" << std::endl;
  }
  else
  {
    std::cout << "Now is bigger or equal then other" << std::endl;
  }
  return EXIT_SUCCESS;
}
