#include<iostream>
#include<sstream>
#include<string>

class Date
{
public:
  Date()
  {
    year = 1;
    month = 1;
    day = 1;
  }
  Date(int y, int m, int d)
  {
    year = y;
    month = m;
    day = d;
  }
  virtual std::string toString()
  {
    std::stringstream stream;
    stream << month << ", " << day << ", " << year;
    return stream.str();
  }; // "mm, dd, yyyy"
  void setDay(int d){day = d;}
  void setMonth(int m){month = m;}
  void setYear(int y){year = y;}
  int getDay() const{return day;}
  int getMonth() const{return month;}
  int getYear() const{return year;}
  void addDays(int d)
  {
    int left_days = d + day -1;
    day = 1;
    while(left_days > 0)
    {
      if(left_days >= 31 && (month == 1 || month == 3 || month == 5 ||
         month == 7 || month == 8 || month == 10 || month == 12))
      {
        addMonths(1);
        left_days -= 31;
      }
      else if(left_days >= 30 && (month == 4 || month == 6 || month == 9 ||
         month == 11))
      {
        addMonths(1);
        left_days -= 30;
      }
      //忘記加month == 2
      else if(left_days >= 28 && month == 2 && !isLeapYear(*this))
      {
        addMonths(1);
        left_days -= 28;
      }
      else if(left_days >= 29 && month == 2&& isLeapYear(*this))
      {
        addMonths(1);
        left_days -= 29;
      }
      else
      {
        day += left_days;
        left_days = 0;
      }
    }

  }; // adds the specified number of days to this instance
  void addMonths(int m)
  {
    int left_month = m + month-1;
    month = 1;
    while(left_month >= 12)
    {
      addYears(1);
      left_month -= 12;
    }
    month += left_month;
  } // adds the specified number of months to this instance
  void addYears(int y)
  {
    year += y;
  }; // adds the specified number of years to this instance
  static bool isLeapYear(const Date &d)
  {
    return (d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0;
  }
  static bool isLeapYear(const int y)
  {
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
  }
private:
  int year, month, day;
};
class TimeSpan
{
public:
  TimeSpan();
  TimeSpan(int d, int hh, int mm, int ss):day(d), hour(hh), minute(mm), second(ss){}
  int toTotalDays(){return day;}
  int toTotalHours(){return toTotalDays()*24+hour;}
  int toTotalMinutes(){return toTotalHours()*60+minute;}
  int toTotalSeconds(){return toTotalMinutes()*60+second;}
  std::string toString()
  {
    std::stringstream stream;
    stream << day << " " << hour << ":" << minute << ":" << second;
    return stream.str();
  } // dd HH:MM:SS
private:
  int day=0, hour=0, minute=0, second=0;
};
class DateTime : public Date
{
public:
  virtual std::string toString()
  {
    std::stringstream stream;
    stream << getMonth() << "/" << getDay() << "/" << getYear() << " "
           << hour << ":" << minute << ":" << second;
    return stream.str();
  } // "mm/dd/yyyy HH:MM:SS"
  DateTime() : Date()
  {
    hour = 0;
    minute = 0;
    second = 0;
  }
  DateTime(int y, int m, int d, int hh, int mm, int ss) : Date(y, m, d)
  {
    hour = hh;
    minute = mm;
    second = ss;
  }
  void setHour(int h){hour = h;}
  void setMinute(int m){minute = m;}
  void setSecond(int s){second = s;}
  int getHour() const{return hour;}
  int getMinute() const{return minute;}
  int getSecond() const{return second;}
  void addHours(int h)
  {
    int left_hour = h + hour, add_day = left_hour / 24;
    hour = left_hour % 24;
    addDays(add_day);
  }; // adds the specified number of hours to this instance
  //忘記加addDays()
  void addMinutes(int m)
  {
    int left_minute = m + minute, add_hour = left_minute / 60;
    minute = left_minute % 60;
    addHours(add_hour);
  }; // adds the specified number of minutes to this instance
  void addSeconds(int s)
  {
    int left_second = s + second, add_minute = left_second / 60;
    second = left_second % 60;
    addMinutes(add_minute);
  }; // adds the specified number of seconds to this instance
  TimeSpan operator-(const DateTime &dt) const
  {
    int left[6] = {dt.getYear(), dt.getMonth(), dt.getDay(), dt.hour, dt.minute, dt.second};
    int right[6] = {this->getYear(), this->getMonth(), this->getDay(),
        this->hour, this->minute, this->second};

    for(int i = 0;i < 6;i++)
    {
      //忘記加這個條件
      if(left[i] > right[i])
        break;

      if(left[i] < right[i])
        {
          for(int j = 0;j < 6;j++)
          {
            //忘記把i換成j
            int buf = left[j];
            left[j] = right[j];
            right[j] = buf;
          }
          break; //記得!!!
        }
    }

    int left_day = left[2], left_second = (left[3]*60+left[4])*60 + left[5];
    int right_day = right[2], right_second = (right[3]*60+right[4])*60 + right[5];

    for(int i = 0;i < left[0];i++)
    {
      if(isLeapYear(i))
        left_day += 366;
      else
        left_day += 365;
    }

    for(int i = 0;i < right[0];i++)
    {
      if(isLeapYear(i))
        right_day += 366;
      else
        right_day += 365;
    }

    for(int i = 1;i < left[1];i++)
    {
      if(i == 1 || i == 3 || i == 5 ||
         i == 7 || i == 8 || i == 10 || i == 12)
        left_day += 31;
      else if(i == 4 || i == 6 || i == 9 || i == 11)
        left_day += 30;
      else if(i == 2 && isLeapYear(left[1]))
        left_day += 29;
      else if(i == 2 && !isLeapYear(left[1]))
        left_day += 28;
    }

    for(int i = 1;i < right[1];i++)
    {
      if(i == 1 || i == 3 || i == 5 ||
         i == 7 || i == 8 || i == 10 || i == 12)
        right_day += 31;
      else if(i == 4 || i == 6 || i == 9 || i == 11)
        right_day += 30;
      else if(i == 2 && isLeapYear(right[1]))
        right_day += 29;
      else if(i == 2 && !isLeapYear(right[1]))
        right_day += 28;
    }

    int result_day = left_day - right_day, result_hour = 0, result_minute = 0;
    int result_sec = left_second - right_second;
    if(result_sec < 0)
    {
      result_sec += 86400;
      result_day -= 1;
    }
    result_hour = result_sec / 3600;
    result_sec %= 3600;
    result_minute = result_sec / 60;
    result_sec %= 60;
    return TimeSpan(result_day, result_hour, result_minute, result_sec);

  }; // return a TimeSpan object represents a time interval
private:
  int hour, minute, second;
};
int main() {
  int y, m, d, hh, mm, ss;
  std::cin>>y>>m>>d>>hh>>mm>>ss;
  DateTime d1(y, m, d, hh, mm, ss);
  std::cin>>y>>m>>d>>hh>>mm>>ss;
  DateTime d2(y, m, d, hh, mm, ss);
  std::cout<<(d1 - d2).toTotalSeconds();
  return 0;
}
