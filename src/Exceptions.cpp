#include "Exceptions.h"

#include <stdio.h>
#include <stdarg.h>

Exception::Exception( const char *format, ... )
{
  char buf[MESSAGE_BUF];
  va_list args;
  va_start( args, format );
  vsprintf( buf, format, args );
  message = std::string( buf );
  va_end( args );
}
