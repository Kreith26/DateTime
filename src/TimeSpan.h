#ifndef _TimeSpan_H_
#define _TimeSpan_H_

// Factors to calculate to other time units
#define FACTOR_SEC_TO_MILLI                     1000
#define FACTOR_MIN_TO_MILLI                60 * 1000
#define FACTOR_MIN_TO_SEC                         60
#define FACTOR_HOUR_TO_MILLI          60 * 60 * 1000
#define FACTOR_HOUR_TO_MIN                        60
#define FACTOR_DAY_TO_MILLI      24 * 60 * 60 * 1000
#define FACTOR_DAY_TO_HOUR                        24

class TimeSpan
{
  public:
    TimeSpan( int seconds );
    TimeSpan( int hours, int minutes, int seconds );
    TimeSpan( int days, int hours, int minutes, int seconds );
    TimeSpan( int days, int hours, int minutes, int seconds, int milliseconds );

    virtual ~TimeSpan( );

    static TimeSpan FromMilliseconds( int milliseconds );
    static TimeSpan FromSeconds( int seconds );
    static TimeSpan FromMinutes( int minutes );
    static TimeSpan FromHours( int hours );
    static TimeSpan FromDays( int days );

    int GetMilliseconds( ) { return milliseconds; }
    int GetSeconds( ) { return seconds; }
    int GetMinutes( ) { return minutes; }
    int GetHours( ) { return hours; }
    int GetDays( ) { return days; }

    double GetTotalMilliseconds( );
    double GetTotalSeconds( );
    double GetTotalMinutes( );
    double GetTotalHours( );
    double GetTotalDays( );

  protected:
    void Init( int days, int hours, int minutes, int seconds, int milliseconds);
    int milliseconds;
    int seconds;
    int minutes;
    int hours;
    int days;
};

#endif // _TimeSpan_H_
