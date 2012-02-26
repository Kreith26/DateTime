#ifndef _Exceptions_H_
#define _Exceptions_H_

#include <string>

#define MESSAGE_BUF         512

class Exception
{
  public:
    Exception( const char *format, ... );
    std::string GetMessage( ) { return message; }
  protected:
    std::string message;
};

class MonthNotInRangeException : public Exception
{
  public:
    MonthNotInRangeException( const char *format, ... );
};

class DayNotInMonthException : public Exception
{
  public:
    DayNotInMonthException( const char *format, ... );
};

class HourNotInRangeException : public Exception
{
  public:
    HourNotInRangeException( const char *format, ... );
};

class MinuteNotInRangeException : public Exception
{
  public:
    MinuteNotInRangeException( const char *format, ... );
};

class SecondNotInRangeException : public Exception
{
  public:
    SecondNotInRangeException( const char *format, ... );
};

class MillisecondNotInRangeException : public Exception
{
  public:
    MillisecondNotInRangeException( const char *format, ... );
};

#endif // _Exceptions_H_
