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
  this->days         = days;
  this->hours        = hours;
  this->minutes      = minutes;
  this->seconds      = seconds;
  this->milliseconds = milliseconds;
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

double TimeSpan::GetTotalMilliseconds( ) const
{
  return milliseconds + seconds * FACTOR_SEC_TO_MILLI + minutes * FACTOR_MIN_TO_MILLI + hours * FACTOR_HOUR_TO_MILLI + days * FACTOR_DAY_TO_MILLI;
}

double TimeSpan::GetTotalSeconds( ) const
{
  return GetTotalMilliseconds( ) / FACTOR_SEC_TO_MILLI;
}

double TimeSpan::GetTotalMinutes( ) const
{
  return GetTotalSeconds( ) / FACTOR_MIN_TO_SEC;
}

double TimeSpan::GetTotalHours( ) const
{
  return GetTotalMinutes( ) / FACTOR_HOUR_TO_MIN;
}

double TimeSpan::GetTotalDays( ) const
{
  return GetTotalHours( ) / FACTOR_DAY_TO_HOUR;
}
