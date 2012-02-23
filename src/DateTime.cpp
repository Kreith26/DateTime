#include "DateTime.h"

DateTime::DateTime( )
{
  Init( 0, 0, 0, 0, 0, 0, 0 );
}

DateTime::DateTime( int day, int month, int year )
{
  Init( day, month, year, 0, 0, 0, 0 );
}

DateTime::DateTime( int day, int month, int year, int hour, int minute, int second )
{
  Init( day, month, year, hour, minute, second, 0 );
}

DateTime::DateTime( int day, int month, int year, int hour, int minute, int second, int millisecond )
{
  Init( day, month, year, hour, minute, second, millisecond );
}

DateTime::DateTime( time_t timestamp )
{
  SetWithTimestamp( timestamp );
}

void DateTime::Init( int day, int month, int year, int hour, int minute, int second, int millisecond )
{
  this->day         = day;
  this->month       = month;
  this->year        = year;

  this->hour        = hour;
  this->minute      = minute;
  this->second      = second;
  this->millisecond = millisecond;
}

DateTime::~DateTime( ) { }

DateTime *DateTime::Now( )
{
  DateTime *dt = new DateTime( );
  dt->SetNow( );
  return dt;
}

void DateTime::SetNow( )
{
  SetWithTimestamp( time( 0 ) );
}

void DateTime::SetWithTimestamp( time_t timestamp )
{
  struct tm time = *localtime( &timestamp );

  Init( time.tm_mday, time.tm_mon + 1, time.tm_year + SINCE_YEAR, time.tm_hour, time.tm_min, time.tm_sec, 0 );
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
  ss << std::setfill( '0' ) << std::setw( 2 ) << hour << ":" << std::setw( 2 ) << minute << ":" << std::setw( 2 ) << second;
  return ss.str( );
}

std::string DateTime::GetLongTimeString( )
{
  std::stringstream ss( std::stringstream::in | std::stringstream::out );
  ss << std::setfill( '0' ) << std::setw( 2 ) << hour << ":" << std::setw( 2 ) << minute << ":" << std::setw( 2 ) << second << ":" << std::setw( 2 ) << millisecond;
  return ss.str( );
}

std::string DateTime::GetShortDateString( )
{
  std::stringstream ss( std::stringstream::in | std::stringstream::out );
  ss << std::setfill( '0' ) << std::setw( 2 ) << day << "." << std::setw( 2 ) << month << "." << year;
  return ss.str( );
}

std::string DateTime::GetLongDateString( )
{
  std::stringstream ss( std::stringstream::in | std::stringstream::out );
  ss << std::setfill( '0' ) << std::setw( 2 ) << day << "." << std::setw( 2 ) << month << "." << year;
  return ss.str( );
}
