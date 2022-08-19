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
    std::ostringstream output;
    output << month << ", " << day << ", " << year;
    return output.str();
  } // "mm, dd, yyyy"
  void setDay(int d){day = d;}
  void setMonth(int m){month = m;}
  void setYear(int y){year = y;}
  int getDay() const{return day;}
  int getMonth() const{return month;}
  int getYear() const{return year;}
  void addDays(int d)
  {
    int left_days = d + day - 1; //扣掉給予天數
    day = 1; //把給予天數加一
    while(left_days > 0)
    {
      //一個月為31天的
      if(left_days >= 31 && (month == 1 || month == 3 || month == 5
        || month == 7 || month == 8 || month == 10 || month == 12))
      {
        addMonths(1);
        left_days -= 31;
      }
      //一個月為30天的
      else if(left_days >= 30 && (month == 4 || month == 6
        || month == 9 || month == 11))
      {
        addMonths(1);
        left_days -= 30;
      }
      //二月且非閏年
      else if(left_days >= 28 && month == 2 && !isLeapYear(*this))
      {
        addMonths(1);
        left_days -= 28;
      }
      //二月且閏年
      else if(left_days >= 29 && month == 2 && isLeapYear(*this))
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
  }
  void addMonths(int m)
  {
    int add_year = 0;
    //先看輸入的月數有無超過一年
    if(m >= 12)
    {
      add_year = (m / 12);
      m %= 12;
    }

    //再把剩下的與現在月數相加
    //(大於12，需要進位)
    if(m + month > 12)
    {
      add_year++;
      month = m + month - 12;
    }
    else
    {
      month += m;
    }

    addYears(add_year);
  }
  void addYears(int y)
  {
    year += y;
  }
  static bool isLeapYear(const Date &d)
  {
    return ((d.year % 4 == 0 && d.year % 100 != 0) || d.year % 400 == 0) ? true : false;
  }
  //提供另一個版本的判斷閏年，方便判斷
  static bool isLeapYear(const int year)
  {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? true : false;
  }
private:
  int year, month, day;
};

class TimeSpan
{
public:
  TimeSpan():day(0), hour(0), minute(0), second(0){}
  TimeSpan(int d, int hh, int mm, int ss):day(d), hour(hh), minute(mm), second(ss){}
  int toTotalDays(){return day;}
  int toTotalHours(){return day*24 + hour;}
  int toTotalMinutes(){return (day*24 + hour) * 60 + minute;}
  int toTotalSeconds(){return ((day*24 + hour) * 60 + minute) * 60 + second;}
  std::string toString()
  {
    std::ostringstream output;
    output << day << " " << hour << ":" << minute << ":" << second;
    return output.str();
  } // dd HH:MM:SS
private:
  int day, hour, minute, second;
};

class DateTime : public Date
{
public:
  virtual std::string toString()
  {
    std::ostringstream output;
    output << getMonth() << "/" << getDay() << "/" << getYear() << " ";
    output << hour << ":" << minute << ":" << second;
    return output.str();
  }; // "mm/dd/yyyy HH:MM:SS"
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

  //以下與增加月數的架構相似
  void addHours(int h)
  {
    int add_day = 0;

    add_day = h / 24;
    h %= 24;

    if(hour + h >= 24)
    {
      add_day++;
      hour = hour + h - 24;
    }
    else
    {
      hour += h;
    }
    addDays(add_day);
  }
  void addMinutes(int m)
  {
    int add_hour = 0;
    add_hour = m / 60;
    m %= 60;

    if(minute + m >= 60)
    {
      add_hour++;
      minute = minute + m - 60;
    }
    else
    {
      minute += m;
    }
    addHours(add_hour);
  }
  void addSeconds(int s)
  {
    int add_minute = 0;
    add_minute = s / 60;
    s %= 60;

    if(second + s >= 60)
    {
      add_minute++;
      second = second + s - 60;
    }
    else
    {
      second += s;
    }
    addMinutes(add_minute);
  }
  TimeSpan operator-(const DateTime &dt) const
  {
    int left[6] = {this->getYear(), this->getMonth(), this->getDay(), this->getHour(), this->getMinute(), this->getSecond()};
    int right[6] = {dt.getYear(), dt.getMonth(), dt.getDay(), dt.getHour(), dt.getMinute(), dt.getSecond()};

    for(int i = 0;i < 6;i++) //確定left一定比right大
    {
      if(left[i] > right[i])
        break;

      if(left[i] < right[i])
      {
        for(int iter = 0;iter < 6;iter++)
        {
          int buf = left[iter];
          left[iter] = right[iter];
          right[iter] = buf;
        }
        break;
      }
    }

    //以下的想法為把兩個時間全部換成 天（年，月，日） 與 秒（時，分，秒），並做減法
    //之後再轉換為之前模樣

    int l_total_day = left[2], r_total_day = right[2];
    int l_total_sec = left[3] * 3600 + left[4] * 60 + left[5];
    int r_total_sec = right[3] * 3600 + right[4] * 60 + right[5];
    for(int i = 0;i < left[0];i++) //把年換算成天（只需要到前一年，因為這一年未過完）
      isLeapYear(i) ? l_total_day += 366 : l_total_day += 365;
    for(int i = 0;i < right[0];i++) //把年換算成天
      isLeapYear(i) ? r_total_day += 366 : r_total_day += 365;

    for(int i = 1;i < left[1];i++) //把月換算成天（只需要到前一月，因為這一月未過完）
    {
      if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
        l_total_day += 31;
      else if(i == 4 || i == 6 || i == 9 || i == 11)
        l_total_day += 30;
      else if(i == 2 && isLeapYear(left[0])) //使用到overloading 的 isLeapYear
        l_total_day += 29;
      else
        l_total_day += 28;
    }
    for(int i = 1;i < right[1];i++) //把月換算成天
    {
      if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
        r_total_day += 31;
      else if(i == 4 || i == 6 || i == 9 || i == 11)
        r_total_day += 30;
      else if(i == 2 && isLeapYear(right[0]))
        r_total_day += 29;
      else
        r_total_day += 28;
    }

    int result_day = l_total_day - r_total_day, result_sec = l_total_sec - r_total_sec;
    if(result_sec < 0) //有可能是負的
    {
      result_day--;
      result_sec += 86400;
    }
    int result_hour = result_sec / 3600, result_min = 0;
    result_sec %= 3600;
    result_min = result_sec / 60;
    result_sec %= 60;

    TimeSpan span(result_day, result_hour, result_min, result_sec);
    return span;
  }
private:
  int hour, minute, second;
};


int main()
{
  Date a(2001,4,1) , b(2002,4,6);
  a.addDays(30);
  b.addMonths(31);
  std::cout << a.toString() << "\n";
  std::cout << b.toString() << "\n";

  /*TimeSpan c(2,1,2,3), d(3,4,5,6);
  std::cout << c.toString() << "\n";
  std::cout << c.toTotalDays() << "\n";
  std::cout << c.toTotalHours() << "\n";
  std::cout << c.toTotalMinutes() << "\n";
  std::cout << c.toTotalSeconds() << "\n";
  std::cout << d.toString() << "\n";
  std::cout << d.toTotalDays() << "\n";
  std::cout << d.toTotalHours() << "\n";
  std::cout << d.toTotalMinutes() << "\n";
  std::cout << d.toTotalSeconds() << "\n";*/

  /*DateTime e(2000,6,16,8,30,15) , f(2004,12,1,19,11,14);

  TimeSpan g = f - e;
  std::cout << g.toString() << "\n";*/
  //std::cout << f.toString() << "\n";
}
