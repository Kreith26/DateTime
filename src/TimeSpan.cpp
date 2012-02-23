#include "TimeSpan.h"

TimeSpan::TimeSpan( int seconds )
{
  Init( 0, 0, 0, seconds, 0 );
}

TimeSpan::TimeSpan( int hours, int minutes, int seconds )
{
  Init( 0, hours, minutes, seconds, 0 );
}

TimeSpan::TimeSpan( int days, int hours, int minutes, int seconds )
{
  Init( days, hours, minutes, seconds, 0 );
}

TimeSpan::TimeSpan( int days, int hours, int minutes, int seconds, int milliseconds )
{
  Init( days, hours, minutes, seconds, milliseconds );
}

void TimeSpan::Init( int days, int hours, int minutes, int seconds, int milliseconds )
{
  days         = days;
  hours        = hours;
  minutes      = minutes;
  seconds      = seconds;
  milliseconds = milliseconds;
}

TimeSpan::~TimeSpan( ) { }

TimeSpan TimeSpan::FromMilliseconds( int milliseconds )
{
  return TimeSpan( 0, 0, 0, 0, milliseconds );
}

TimeSpan TimeSpan::FromSeconds( int seconds )
{
  return TimeSpan( 0, 0, 0, seconds, 0 );
}

TimeSpan TimeSpan::FromMinutes( int minutes )
{
  return TimeSpan( 0, 0, minutes, 0, 0 );
}

TimeSpan TimeSpan::FromHours( int hours )
{
  return TimeSpan( 0, hours, 0, 0, 0 );
}

TimeSpan TimeSpan::FromDays( int days )
{
  return TimeSpan( days, 0, 0, 0, 0 );
}

double TimeSpan::GetTotalMilliseconds( )
{
  return milliseconds + seconds * FACTOR_SEC_TO_MILLI + minutes * FACTOR_MIN_TO_MILLI + hours * FACTOR_HOUR_TO_MILLI + days * FACTOR_DAY_TO_MILLI;
}

double TimeSpan::GetTotalSeconds( )
{
  return GetTotalMilliseconds( ) / FACTOR_SEC_TO_MILLI;
}

double TimeSpan::GetTotalMinutes( )
{
  return GetTotalSeconds( ) / FACTOR_MIN_TO_SEC;
}

double TimeSpan::GetTotalHours( )
{
  return GetTotalMinutes( ) / FACTOR_HOUR_TO_MIN;
}

double TimeSpan::GetTotalDays( )
{
  return GetTotalHours( ) / FACTOR_DAY_TO_HOUR;
}
