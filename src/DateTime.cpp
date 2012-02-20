#include "DateTime.h"

#include <iomanip>
#include <sstream>

DateTime::DateTime( )
{
  DateTime( 0, 0, 0, 0, 0, 0 );
}

DateTime::DateTime( int day, int month, int year )
{
  DateTime( day, month, year, 0, 0, 0 );
}

DateTime::DateTime( int day, int month, int year, int seconds, int minutes, int hours )
  : seconds( seconds ),
    minutes( minutes ),
    hours( hours ),
    day( day ),
    month( month ),
    year( year )
{
  summertime = IsDateSummertime( day, month );
  leapyear   = IsYearLeapYear( year );
}

DateTime::DateTime( time_t timestamp )
{
  struct tm time = *localtime( &timestamp );
  seconds    = time.tm_sec;
  minutes    = time.tm_min;
  hours      = time.tm_hour;

  day        = time.tm_mday;
  month      = time.tm_mon + 1;
  year       = time.tm_year + SINCE_YEAR;

  weekday    = time.tm_wday;
  yearday    = time.tm_yday;

  summertime = time.tm_isdst > 0;
  leapyear   = IsYearLeapYear( year );
}

DateTime::~DateTime( ) { }

DateTime *DateTime::Now( )
{
  return new DateTime( time( 0 ) );
}

bool DateTime::IsYearLeapYear( int year )
{
  return (( year % 4 == 0 ) && ( year % 100 != 0 )) || ( year % 400 == 0 );
}

bool DateTime::IsDateSummertime( int day, int month )
{
  // FIXME: include day in calculation
  if( month >= SUMMERTIME_BEGIN_MONTH && month <= SUMMERTIME_END_MONTH )
  {
    return true;
  }
  else
  {
    return false;
  }
}

std::string DateTime::GetShortTimeString( )
{
  std::stringstream ss( std::stringstream::in | std::stringstream::out );
  ss << std::setfill( '0' ) << std::setw( 2 ) << hours << ":" << std::setw( 2 ) << minutes << ":" << std::setw( 2 ) << seconds;
  return ss.str( );
}

std::string DateTime::GetLongTimeString( )
{
  // FIXME: Different from GetShortTimeString( ) ?
  std::stringstream ss( std::stringstream::in | std::stringstream::out );
  ss << std::setfill( '0' ) << std::setw( 2 ) << hours << ":" << std::setw( 2 ) << minutes << ":" << std::setw( 2 ) << seconds;
  return ss.str( );
}

std::string DateTime::GetShortDateString( )
{
  std::stringstream ss( std::stringstream::in | std::stringstream::out );
  ss << std::setfill( '0' ) << std::setw( 2 ) << day << ":" << std::setw( 2 ) << month << ":" << year;
  return ss.str( );
}
