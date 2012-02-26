#ifndef _DateTime_H_
#define _DateTime_H_

#include "TimeSpan.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <time.h>

// Since
#define SINCE_YEAR               1900

// Summertime
#define SUMMERTIME_BEGIN_MONTH      3
#define SUMMERTIME_END_MONTH       10

// Min and Max values
#define MIN_MONTH                   1
#define MAX_MONTH                  12

#define MIN_DAY                     1
#define MAX_DAY                    30

#define MIN_WEEKDAY                 0
#define MAX_WEEKDAY                 7

#define MIN_HOUR                    0
#define MAX_HOUR                   24

#define MIN_MINUTE                  0
#define MAX_MINUTE                 60

#define MIN_SECOND                  0
#define MAX_SECOND                 60

#define MIN_MILLISECOND             0
#define MAX_MILLISECOND          1000

namespace Days
{
  enum Day
  {
    Monday,
    Thuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
  };
}

namespace Months
{
  enum Month
  {
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
  };
}

class DateTime
{
  public:
    DateTime( time_t timestamp );
    DateTime( int day, int month, int year );
    DateTime( int day, int month, int year, int hour, int minute, int second );
    DateTime( int day, int month, int year, int hour, int minute, int second, int millisecond );

    virtual ~DateTime( );
    static DateTime *Now( );

    void SetNow( );
    void SetWithTimestamp( time_t timestamp );

    int GetYear( ) const { return year; }
    int GetMonth( ) const { return month; }
    int GetDay( ) const { return day; }

    int GetHour( ) const { return hour; }
    int GetMinute( ) const { return minute; }
    int GetSecond( ) const { return second; }
    int GetMillisecond( ) const { return millisecond; }

    time_t GetTimestamp( ) const;
    struct tm GetTMStruct( ) const;

    // FIXME: Add methods currently just works with positive value
    void Add( const TimeSpan *ts );
    void AddYears( int years );
    void AddMonths( int months );
    void AddDays( int days );
    void AddHours( int hours );
    void AddMinutes( int minutes );
    void AddSeconds( int seconds );
    void AddMilliseconds( int milliseconds );

    bool IsSummertime( ) { return IsYearLeapYear( year ); }
    bool IsLeapYear( ) { return IsDateSummertime( day, month ); }

    static bool IsDateSummertime( int day, int month );
    static bool IsYearLeapYear( int year );

    Days::Day GetDayOfWeek( );
    int GetDayOfYear( );

    int GetDaysOfMonth( int month );

    std::string GetNameOfDay( int day );
    std::string GetNameOfMonth( int month );

    bool operator<( const DateTime &dt ) const;
    bool operator>( const DateTime &dt ) const;
    bool operator<=( const DateTime &dt ) const;
    bool operator>=( const DateTime &dt ) const;
    bool operator==( const DateTime &dt ) const;

    DateTime operator+( const TimeSpan &ts );
    DateTime operator-( const TimeSpan &ts );
    TimeSpan operator-( const DateTime &dt );
    void operator+=( const TimeSpan &ts );
    void operator-=( const TimeSpan &ts );

    std::string GetAsString( );
    std::string GetShortTimeString( );
    std::string GetLongTimeString( );
    std::string GetShortDateString( );
    std::string GetLongDateString( );

  protected:
    DateTime( );
    void Init( int day, int month, int year, int hour, int minute, int second, int millisecond );
    void InitMonths( );
    void InitMonthNames( );
    void InitDayNames( );

    bool IsValidWeekday( int day );
    bool IsValidDayOfMonth( int day, int month );
    bool IsValidMonth( int month );
    bool IsValidYear( int year );

    bool IsValidHour( int hour );
    bool IsValidMinute( int minute );
    bool IsValidSecond( int second );
    bool IsValidMillisecond( int millisecond );

    int daysOfMonth[MAX_MONTH];
    std::string monthNames[MAX_MONTH];
    std::string dayNames[MAX_DAY];

    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;

    bool summertime;
    bool leapyear;
};

#endif // _DateTime_H_
