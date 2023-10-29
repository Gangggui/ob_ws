#时间 


### 1. boost timer库（计时）

`timer`是一个很小的库，提供简单的时间度量和进度显示功能，也可用于性能测试等计时任务。`timer`库包含三个组件：计时器类`timer`、`progress_timer`和进度指示类`progress_display`。
```c++
#include <boost/timer/timer.hpp>

boost::timer::cpu_timer t;

int main() {
	t.start(); // 开始计时
	this_thread::sleep_for(100ms); //休眠
	t.stop(); // 停止计时
	this_thread::sleep_for(100ms);
	t.resume(); // 恢复计时
	cout << t.format() << endl;
}
```

format方法格式化输出结果；默认的格式定义为：
```c++
"%ws wall,%us user + %ss system = %ts CPU (%p%)\n"
---
%含义为：
%w：times.wall
%u：times.user
%s：times.system
%t：times.user + times.system
%p：The percentage of times.wall represented by times.user + times.system%%
```

cpu_timer 使用3类值来度量程序使用的时间（默认单位为1ns = 1e-9 s）
- wall: 挂钟时间，也就是程序运行的实际时间(精度为1ms)
- user: 用户cpu时间（精度为10~15ms）
- system: 系统cpu时间
定制输出格式`cpu_timer.elapsed()`
```c++
auto x = t.elapsed();
// 转换后输出单位为ms
std::cout << x.wall/1000000.0 << std::endl;
std::cout << x.user/1000000.0 << std::endl;
std::cout << x.system/1000000.0 << std::endl;
```

### 2. boost date_time库（当前时间）

`date_time`库提供了时间日期相关的计算、格式化、转换、输入输岀等功能，为C++的日期时间编程提供了极大便利。

#### 2.1 date_duration类

`date_duration`表示日期长度，是以天为单位的时长，值可以是任意的整数可正可负。`date_time`库为`date_duration`定义了一个常用的 `typedef:days`，此外还提供了 `months`、`years`、`weeks`等另外三个时长类；分别用来表示月，年和星期

测试用例
```c++
#include<iostream>
using namespace std;   

#include<boost/date_time/gregorian/gregorian.hpp>
using namespace  boost::gregorian;

#pragma  comment(lib, "libboost_date_time-vc100-mt-gd-x32-1_67.lib")

int  main()
{ 
   //构造日期
   date   d1(2000, 1, 1);
   date   d2 = from_string("2010-02-02");
   date   d3 = from_string("2010/03/03");
   date   d4 = from_undelimited_string("20100404");//无界定的字符串

   date  d5(min_date_time);//特殊时间值1400-01-01
   date  d6(max_date_time);//特殊时间值9999-12-31

   //输出日期
   cout << d1.year() << "年" <<(int) d1.month() << "月" << d1.day() << endl;
   cout << to_simple_string(d2) << endl;//2010-Feb-02
   cout << to_iso_string(d3) << endl;//20100303
   cout << to_iso_extended_string(d4) << endl;//2010-03-03
   cout << to_iso_string(d5) << endl;
   cout << to_iso_string(d6) << endl;

   //获取今天的日期
   date  today = day_clock::local_day();

   cout << "年"<< today.year() << endl;
   cout << "月"<< today.month() << endl;
   cout << "日"<< today.day() << endl;
   cout <<"星期"<< today.day_of_week() << endl; 
   cout << "一年中的第几周" << today.week_number() << endl;
   cout << "一年中的第多少天" << today.day_of_year() << endl;
   cout << "这个月的结束日期" << today.end_of_month() << endl;

   //时间长度(最小单位是 天)
   days  day1(10);
   days  day2(-5);
   date_duration  du1  = day1 + day2;
   cout <<"10天-5天"<< du1.days() << endl;

   weeks  w1(1);
   cout << "1周的天数" << w1.days() << endl;
   date_duration  du2 = w1 + day1;
   cout << "1周+ 10天" << du2.days() << endl;

   months   mon1(1);//一个月无法知道是多少天 ，并且无法加天数
   cout << "1个月" << mon1.number_of_months() << endl;

   years  year1(1);//一年无法知道是多少天，并且无法加天数
   cout << "1年" << year1.number_of_years()<< endl;

   //如何知道一年多少个月
   months mon2= year1 + months(0);
   cout << "1年多少个月" << mon2.number_of_months() << endl;

   //日期+  日期长度 = 新日期 ，很实用
   date   d10(2018, 1, 31);

   cout << "今天往前推10天是几月几日:" ;
   cout <<  to_iso_extended_string(  d10 + days(-10) ) << endl;

   cout << "今天往后加2周是几月几日:";
   cout << to_iso_extended_string(d10 + weeks(2)) << endl;

   cout << "今天往后推一个月是几月几日:";
   cout << to_iso_extended_string(d10 + months(1)) << endl;

   cout << "今天往后推一年月是几月几日:";
   cout << to_iso_extended_string(d10 + years(1)) << endl;

   getchar();
   return 0;
}
```

#### 2.2 date_period类

`date_period`类用来表示日期范围的概念，它是时间轴上一个左闭右开区间，端点是两个date对象。

日期迭代器可以用++、--操作符连续访问日期，这些迭代器包括：`day_iterator、week_iterator、month_iterator`和`year_iterator` 注意：它们并不符合标准迭代器的定义，没有difference_type、pointer、reference等内部类型定义，不能使用std::advance()或者+=来前进或者后退。

示例代码：
```c++

#include<iostream>
using namespace std;   
  
#include<boost/date_time/gregorian/gregorian.hpp>
using namespace  boost::gregorian;

#pragma  comment(lib, "libboost_date_time-vc100-mt-gd-x32-1_67.lib")

int  main()
{ 
   date  d1(2000, 1, 1);
   date  d2(2000, 2, 1);

   //构造一个日期范围
   date_period  dp1(d1, d2);//两个日期确定一个范围
   cout << dp1 << endl;//左闭右开，不包含2000/2/1
   cout << dp1.length() << endl;//返回这个范围的天数

   //把日期范围平移
   dp1.shift(date_duration(10)); 
   cout << dp1 << endl;//向后移动10天

   //把日期向两边延伸
   dp1.expand(date_duration(1));//向两边移动一天
   cout << dp1 << endl; 

   //检测某个日期是否在这个日期范围里面
   cout << dp1.contains(  date(2000,2,20)  ) << endl;


   //日期迭代器

   date  d3(2000, 1, 1);
   day_iterator  it1(d3,10);//默认步长是1
   ++it1;//不会影响原日期，只是输出结果
   ++it1;
   cout <<"day_iterator   "<< *it1 << endl;


   week_iterator  it2(d3, 2);
   --it2;//向前移动2周
   cout << "week_iterator   " << *it2 << endl;

   month_iterator  it3(d3);
   --it3;//向前移动1月
   cout << "month_iterator   " << *it3 << endl;
    
   year_iterator  it4(d3, 10);
   ++it4;//向后移动10年
   cout << "month_iterator   " << *it4 << endl;

   return 0;
```

### 2.3 ptime类

`date_time`库它包含两个组件，处理日期的组件 gregorian和处理时间的组件 `posix_time`。date类用于创建日期，ptime类则用于定义一个时间。

ptime是 date_time库处理时间的核心类，它使用64位（微秒）或96位（纳秒）的整数在内部存储时间数据。

```c++
#include<iostream>
using namespace std;   
  
//日期组件
#include<boost/date_time/gregorian/gregorian.hpp>
using namespace  boost::gregorian;

//时间组件
#include<boost/date_time/posix_time/posix_time.hpp>
using namespace  boost::posix_time;

#pragma  comment(lib, "libboost_date_time-vc100-mt-gd-x32-1_67.lib")

int  main()
{ 
   //时间的构造
   ptime  t1 = time_from_string("2000-01-01 10:00:02");
   cout << t1 << endl;

   ptime  t2 = from_iso_string("20000101T100003");//用字母T分割日期时间
   cout << t2 << endl;
    
   ptime   t3 = second_clock::local_time();//秒精度
   cout << t3 << endl;

   ptime   t4 = microsec_clock::local_time();//微秒精度
   cout << t4 << endl;

   ptime   t5 (min_date_time);//特殊值
   cout << t5 << endl;

   ptime   t6(max_date_time);//特殊值
   cout << t6 << endl;

   //类似日期长度date_duration，也有时间长度

   //1小时10分钟20秒99毫秒
   time_duration  td1(1, 10, 20, 99*1000); //最后一个参数的单位是微秒
   cout << td1 << endl;


   //1小时10分钟21秒 （自动往前进位）
   time_duration  td2(1, 10, 20,1000 * 1000); //最后一个参数的单位是微秒
   cout << td2 << endl;

   //1小时10分钟20秒  1微秒 
   time_duration  td3=  duration_from_string("1:10:20:000001"); //最后一个参数的单位是微秒
   cout << td3 << endl; 

   //hours
   hours  h(1);
   cout << h.total_seconds() << "秒" << h.total_milliseconds() << "毫秒"
   	<< h.total_microseconds() << "微秒" << h.total_nanoseconds() << "纳秒" << endl;

   //利用时间长度构造
   time_duration td4 = hours(1) + minutes(10) + seconds(20) +microsec(30)+ microseconds(10);
   cout << td4 << endl;


   return 0;
}
```

#### 2.4 time_period类

类似日期迭代器，时间也有迭代器，但是只有一个`time_iterator`；可以用`++`、`--`操作符连续访问时间。

```c++
#include<iostream>
using namespace std;   

//日期组件
#include<boost/date_time/gregorian/gregorian.hpp>
using namespace  boost::gregorian;

//时间组件
#include<boost/date_time/posix_time/posix_time.hpp>
using namespace  boost::posix_time;

#pragma  comment(lib, "libboost_date_time-vc100-mt-gd-x32-1_67.lib")

int  main()
{ 
   //起始时间
   ptime  p1 = time_from_string("2000-01-01 00:00:01");
   //结束时间
   ptime  p2(date(2000, 1, 2));// 默认是 2000-01-01 23:59:59.999;

   //产生一个时间范围,   类似 日期范围  date_period的用法
   time_period  tp(p1, p2);//  p2>p1才可以
   cout << tp << endl;

   time_duration  td = tp.length();//返回时间长度
   cout << td<< endl;

   //把时间范围向后平移9秒
   tp.shift(seconds(9));
   cout << tp << endl;

   //把时间范围向两边扩大1小时
   tp.expand(hours(1));
   cout << tp << endl;

   //某个时间是否在这个时间范围内
   ptime  p3 = time_from_string("2010-01-01 00:00:01");
   cout << tp.contains(p3) << endl;


   //----------------------------------------------------------

   //类似日期迭代器year_iterator, month_iterator等，时间迭代器time_iterator
   ptime  p4 = time_from_string("2000-01-01 00:00:01");
   time_iterator  it(p4, seconds(10));//以10秒为步长

   for (int i = 0; i < 3; ++i) ++it; //迭代器的移动不会影响p4的值

   cout <<"时间迭代器向后移动30秒" <<*it << endl;


   time_iterator  it2(p4, hours(24));//以24小时为步长
   ++it2;//迭代器的移动不会影响p4的值
   cout << "时间迭代器向后移动24小时" << *it2 << endl;

   //日期时间格式化
   date  d1 = day_clock::local_day();
   date_facet  *pDF = new  date_facet("%Y年  %m月  %d日");
   cout.imbue(locale(cout.getloc(), pDF));//指定输出流的语言环境
   cout << d1 << endl;

   ptime  t1 = microsec_clock::local_time();
   time_facet  *pTF = new  time_facet("%Y年  %m月  %d日   %H:%M:%S  %F");
   cout.imbue(locale(cout.getloc(), pTF));//指定输出流的语言环境
   cout << t1 << endl;

   getchar();
   return 0;
}

```