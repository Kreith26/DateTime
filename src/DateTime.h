#ifndef _DateTime_H_
#define _DateTime_H_

#include <iostream>
#include <string>

#include <time.h>

// Since
#define SINCE_YEAR               1900

// Summertime
#define SUMMERTIME_BEGIN_DAY       27
#define SUMMERTIME_BEGIN_MONTH      3

#define SUMMERTIME_END_DAY         30
#define SUMMERTIME_END_MONTH       10

class DateTime
{
  public:
    DateTime( );
    DateTime( time_t timestamp );
    DateTime( int day, int month, int year );
    DateTime( int day, int month, int year, int seconds, int minutes, int hours );

    virtual ~DateTime( );

    static DateTime *Now( );

    int GetSeconds( ) { return seconds; }
    int GetMinutes( ) { return minutes; }
    int GetHours( ) { return hours; }

    int GetDay( ) { return day; }
    int GetMonth( ) { return month; }
    int GetYear( ) { return year; }

    int GetDayOfWeek( );
    int GetDayOfYear( );

    bool IsSummertime( );

    void AddSeconds( int seconds );
    void AddMinutes( int minutes );
    void AddHours( int hours );

    void AddDays( int days );
    void AddMonths( int months );
    void AddYears( int years );

    int GetTotalSeconds( );
    int GetTotalMinutes( );
    int GetTotalHours( );
    int GetTotalDays( );
    int GetTotalMonths( );
    int GetTotalYears( );

    std::string GetShortTimeString( );
    std::string GetLongTimeString( );
    std::string GetShortDateString( );
    std::string GetLongDateString( );

    bool IsYearLeapYear( int year );
    bool IsDateSummertime( int day, int month );

    // Nested Date class
    class Date
    {
      public:
        Date( );
        ~Date( );

      protected:
        int day;
        int month;
        int year;
    };

    // Nested Time class
    class Time
    {
      public:
        Time( );
        ~Time( );

      protected:
        int seconds;
        int minutes;
        int years;
    };

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

  protected:
    time_t timestamp;

    int seconds;
    int minutes;
    int hours;

    int day;
    int month;
    int year;

    int weekday;
    int yearday;

    bool summertime;
    bool leapyear;
};

#endif // _DateTime_H_
