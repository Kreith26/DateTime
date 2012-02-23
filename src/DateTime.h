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

enum Month
{
  January    = 1,
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

class DateTime
{
  public:
    DateTime( );
    DateTime( time_t timestamp );
    DateTime( int day, int month, int year );
    DateTime( int day, int month, int year, int hours, int minutes, int seconds );
    DateTime( int day, int month, int year, int hours, int minutes, int seconds, int milliseconds );

    virtual ~DateTime( );
    static DateTime *Now( );

    void SetNow( );
    void SetWithTimestamp( time_t timestamp );

    int GetYear( ) { return year; }
    int GetMonth( ) { return month; }
    int GetDay( ) { return day; }

    int GetHour( ) { return hour; }
    int GetMinute( ) { return minute; }
    int GetSecond( ) { return second; }

    void Add( const TimeSpan &ts );
    void AddYears( int years );
    void AddMonths( int months );
    void AddDays( int days );
    void AddHours( int hours );
    void AddMinutes( int minutes );
    void AddSeconds( int seconds );
    void AddMilliseconds( int milliseconds );

    bool IsSummertime( ) { return summertime; }
    bool IsLeapYear( ) { return leapyear; }

    static bool IsDateSummertime( int day, int month );
    static bool IsYearLeapYear( int year );

    bool operator<( const DateTime &dt ) const;
    bool operator>( const DateTime &dt ) const;
    bool operator<=( const DateTime &dt ) const;
    bool operator>=( const DateTime &dt ) const;
    bool operator==( const DateTime &dt ) const;

    DateTime operator+( const TimeSpan &ts ) const;
    DateTime operator-( const TimeSpan &ts ) const;
    TimeSpan operator-( const DateTime &dt ) const;
    void operator+=( const TimeSpan &ts );
    void operator-=( const TimeSpan &ts );

    std::string GetShortTimeString( );
    std::string GetLongTimeString( );
    std::string GetShortDateString( );
    std::string GetLongDateString( );

  protected:
    void Init( int day, int month, int year, int hours, int minutes, int seconds, int milliseconds );

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
