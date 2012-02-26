#include "DateTime.h"

#include "Exceptions.h"

DateTime::DateTime( )
{
  this->day         = day;
  this->month       = month;
  this->year        = year;

  this->hour        = hour;
  this->minute      = minute;
  this->second      = second;
  this->millisecond = millisecond;

  InitMonths( );
  InitMonthNames( );
  InitDayNames( );
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
  this->year = year;

  InitMonths( );
  InitMonthNames( );
  InitDayNames( );

  if( !IsValidMonth( month ) )
  {
    throw Exception( "Month %d is not in range", month );
  }

  if( !IsValidDayOfMonth( day, month ) )
  {
    throw Exception( "Day %d is not in month %d's range", day, month );
  }

  if( !IsValidHour( hour ) )
  {
    throw Exception( "Hour %d is not in valid range ( %d - %d )", hour, MIN_HOUR, MAX_HOUR );
  }

  if( !IsValidMinute( minute ) )
  {
    throw Exception( "Minute %d is not in valid range ( %d - %d )", minute, MIN_MINUTE, MAX_MINUTE );
  }

  if( !IsValidSecond( second ) )
  {
    throw Exception( "Second %d is not in valid range ( %d - %d )", second, MIN_SECOND, MAX_SECOND );
  }

  if( !IsValidMillisecond( millisecond ) )
  {
    throw Exception( "Millisecond %d is not in valid range ( %d - %d )", millisecond, MIN_MILLISECOND, MAX_MILLISECOND );
  }

  this->day         = day;
  this->month       = month;

  this->hour        = hour;
  this->minute      = minute;
  this->second      = second;
  this->millisecond = millisecond;
}

void DateTime::InitMonths( )
{
  // Perhaps an algorithm would be more efficient
  daysOfMonth[Months::January]   = 31;
  daysOfMonth[Months::February]  = IsLeapYear( ) ? 29 : 28; // In a leapyear 29 else 28
  daysOfMonth[Months::March]     = 31;
  daysOfMonth[Months::April]     = 30;
  daysOfMonth[Months::May]       = 31;
  daysOfMonth[Months::June]      = 30;
  daysOfMonth[Months::July]      = 31;
  daysOfMonth[Months::August]    = 31;
  daysOfMonth[Months::September] = 30;
  daysOfMonth[Months::October]   = 31;
  daysOfMonth[Months::November]  = 30;
  daysOfMonth[Months::December]  = 31;
}

void DateTime::InitMonthNames( )
{
  monthNames[Months::January]    = "January";
  monthNames[Months::February]   = "February";
  monthNames[Months::March]      = "March";
  monthNames[Months::April]      = "April";
  monthNames[Months::May]        = "May";
  monthNames[Months::June]       = "June";
  monthNames[Months::July]       = "July";
  monthNames[Months::August]     = "August";
  monthNames[Months::September]  = "September";
  monthNames[Months::October]    = "October";
  monthNames[Months::November]   = "November";
  monthNames[Months::December]   = "December";
}

void DateTime::InitDayNames( )
{
  dayNames[Days::Monday]         = "Monday";
  dayNames[Days::Thuesday]       = "Thuesday";
  dayNames[Days::Wednesday]      = "Wednesday";
  dayNames[Days::Thursday]       = "Thursday";
  dayNames[Days::Friday]         = "Friday";
  dayNames[Days::Saturday]       = "Saturday";
  dayNames[Days::Sunday]         = "Sunday";
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

time_t DateTime::GetTimestamp( ) const
{
  time_t rawtime;
  struct tm *time = localtime( &rawtime );
  time->tm_year = year - SINCE_YEAR;
  time->tm_mon  = month - 1;
  time->tm_mday = day;
  time->tm_hour = hour;
  time->tm_min  = minute;
  time->tm_sec  = second;
  return mktime( time );
}

struct tm DateTime::GetTMStruct( ) const
{
  time_t rawtime;
  struct tm *time = localtime( &rawtime );
  time->tm_year = year - SINCE_YEAR;
  time->tm_mon  = month - 1;
  time->tm_mday = day;
  time->tm_hour = hour;
  time->tm_min  = minute;
  time->tm_sec  = second;
  mktime( time );
  return *time;
}

void DateTime::Add( const TimeSpan *ts )
{
  AddMilliseconds( ts->GetTotalMilliseconds( ) );
}

void DateTime::AddYears( int years )
{
  year += years;
}

void DateTime::AddMonths( int months )
{
  AddYears( months / MAX_MONTH );
  month += months % MAX_MONTH;
}

void DateTime::AddDays( int days )
{
  AddMonths( days / MAX_DAY );
  day += days % MAX_DAY;
}

void DateTime::AddHours( int hours )
{
  AddDays( hours / MAX_HOUR );
  hour += hours % MAX_HOUR;
}

void DateTime::AddMinutes( int minutes )
{
  AddHours( minutes / MAX_MINUTE );
  minute += minutes % MAX_MINUTE;
}

void DateTime::AddSeconds( int seconds )
{
  AddMinutes( seconds / MAX_SECOND );
  second += seconds % MAX_SECOND;
}

void DateTime::AddMilliseconds( int milliseconds )
{
  AddSeconds( milliseconds / MAX_MILLISECOND );
  millisecond += milliseconds % MAX_MILLISECOND;
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

Days::Day DateTime::GetDayOfWeek( )
{
  return static_cast<Days::Day>( GetTMStruct( ).tm_wday );
}

int DateTime::GetDayOfYear( )
{
  return GetTMStruct( ).tm_yday;
}

int DateTime::GetDaysOfMonth( int month )
{
  return IsValidMonth( month ) ? daysOfMonth[month] : -1;
}

bool DateTime::operator<( const DateTime &dt ) const
{
  return GetTimestamp( ) < dt.GetTimestamp( );
}

bool DateTime::operator>( const DateTime &dt ) const
{
  return GetTimestamp( ) > dt.GetTimestamp( );
}

bool DateTime::operator<=( const DateTime &dt ) const
{
  return GetTimestamp( ) <= dt.GetTimestamp( );
}

bool DateTime::operator>=( const DateTime &dt ) const
{
  return GetTimestamp( ) >= dt.GetTimestamp( );
}

bool DateTime::operator==( const DateTime &dt ) const
{
  return GetTimestamp( ) == dt.GetTimestamp( );
}

DateTime DateTime::operator+( const TimeSpan &ts )
{
  DateTime *tmp = this;
  tmp->Add( &ts );
  return *tmp;
}

//DateTime DateTime::operator-( const TimeSpan &ts );
//TimeSpan DateTime::operator-( const DateTime &dt );

void DateTime::operator+=( const TimeSpan &ts )
{
  Add( &ts );
}

//void DateTime::operator-=( const TimeSpan &ts );

std::string DateTime::GetNameOfDay( int day )
{
  if( IsValidWeekday( day ) )
  {
    return dayNames[day - 1];
  }
  else
  {
    throw Exception( "Day %d is not in valid weekday range ( %d - %d )", day, MIN_WEEKDAY, MAX_WEEKDAY );
  }
}

std::string DateTime::GetNameOfMonth( int month )
{
  if( IsValidMonth( month ) )
  {
    return monthNames[month - 1];
  }
  else
  {
    throw Exception( "Month %d is not in valid range ( %d - %d )", month, MIN_MONTH, MAX_MONTH );
  }
}

std::string DateTime::GetAsString( )
{
  return GetShortDateString( ) + std::string( " - " ) + GetShortTimeString( );
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
  ss << GetNameOfDay( GetDayOfWeek( ) ) << ", " << GetNameOfMonth( month ) << " " << day << ", " << year;
  return ss.str( );
}

bool DateTime::IsValidWeekday( int day )
{
  return day >= MIN_WEEKDAY && day <= MAX_WEEKDAY;
}

bool DateTime::IsValidDayOfMonth( int day, int month )
{
  if( IsValidMonth( month ) )
  {
    return day >= 1 && day <= GetDaysOfMonth( month );
  }
  else
  {
    return false;
  }
}

bool DateTime::IsValidMonth( int month )
{
  return month >= MIN_MONTH && month <= MAX_MONTH;
}

bool DateTime::IsValidYear( int year )
{
  return year >= 0;
}

bool DateTime::IsValidHour( int hour )
{
  return hour >= MIN_HOUR && hour <= MAX_HOUR;
}

bool DateTime::IsValidMinute( int minute )
{
  return minute >= MIN_MINUTE && minute <= MAX_MINUTE;
}

bool DateTime::IsValidSecond( int second )
{
  return second >= MIN_SECOND && second <= MAX_SECOND;
}

bool DateTime::IsValidMillisecond( int millisecond )
{
  return millisecond >= MIN_MILLISECOND && millisecond <= MAX_MILLISECOND;
}
