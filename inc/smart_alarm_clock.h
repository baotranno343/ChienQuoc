#ifndef _SMART_ALARM_CLOCK_H_
#define _SMART_ALARM_CLOCK_H_

#define SAC_TIME_CACHE		1			//	时钟缓冲区（秒）实际缓冲范围应该是这个数字的2倍
#define SAC_TAG_YEAR		"year"			//	定义年标志
#define SAC_TAG_MONTH		"month"			//	定义月标志
#define SAC_TAG_WEEK		"week"			//	定义周标志
#define SAC_TAG_DAY		"day"			//	定义天标志
#define SAC_TAG_HOUR		"hour"			//	定义时标志
#define SAC_TAG_MINUTE		"minute"		//	定义分标志
#define SAC_TAG_SECOND		"second"		//	定义秒标志

#define SAC_MAX_TIMES		5000000			//	最大轮寻次数
#define CYCLE_MINUTE		(60)			//	预定义的分钟周期
#define CYCLE_HOUR		(60*60)			//	预定义的小时周期
#define CYCLE_DAY		(60*60*24)		//	预定义的一天周期
#define CYCLE_WEEK		(60*60*24*7)		//	预定义的星期周期
#endif

