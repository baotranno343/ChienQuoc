/*----------------------------------------------------------------------------------------------------*\
	聪明的闹钟：LPC 时间流程控制组件
	由cjxx 创建 07-07-04
	功能：这里提供一种对时间的灵活掌握方式，能够使用户通过思维逻辑直接与代码进行时钟定时的交互
	时间格式：
	一：当前时间到下一个时间点
	     年	      月     日	    时	   分	  秒
	[1970-5000][01-12][01-31][00-23][00-59][00-59]-（最小单位）
	二：当前时间到下一个时间点
	                    周日    时	   分	  秒
	                  [0-6][00-23][00-59][00-59]-（最小单位）
	三：当前时间
	                    周日    时     分     秒
	                   [0-+] /[0-+] /[0-+] / [0-+]-（最小单位）
	程序思路：
		提供几种方法让用户向本类中的私有变量数组中添加灵活结构的时钟标志，
	设定一个下次需要回调的最近时间点，在这个时间点上回调对应名称的用户函数。
	调用完这个函数后对这个时钟做修改处理，之后定义出新的回调处理函数定时调用。
	当用户在任意时刻调用了增加，修改或删除，本时钟点操作的函数时，都会重新计算最近
	的下一个时间点，并根据改变情况对当前需要回调的函数次序作出修改，保证实时更新，
	每个时钟的调用次数都应该进行效对如果出现错误应该进行错误报告，并且应该允许调
	用时钟有0-3秒的误差，超过这个范围的时钟没有被执行或重复执行都属于错误状态。
	目的：
		用户需要考虑的是程序的主逻辑，可以把时间调用交给本类处理，以提高工作效
	率。此类设定为标准基类，一定要被继承后才能使用，呵呵。
	预计完成时间：07-07-05P19
	07-07-10 完成所有，比预计时间晚了 5天，不过后3天是周末又测试了一天，所以实际完成
	时间应该是 3-4天
	目前的功能：
		1 解析几乎所有可被理解的时间格式
		2 回调方式处理任意次序和规则的时钟
\*----------------------------------------------------------------------------------------------------*/
#include <time.h>
#include <smart_alarm_clock.h>

#define _DEBUG(str) ; //if(objectp(find_char("1"))) tell_user(find_char("1"),str);

#define SAC_CALL_OUT_FUNC "open_alarm_clock" //	回调函数的名称

class clock_struct
{
	int next_stamp;									   //	下次执行时的绝对时间戳
	int times;										   //	循环次数 -- 当轮寻次数被减到0 则取消。超过最大轮寻次数则按照无限循环处理
	int cycle_time;									   //	轮寻时间 -- 此时间由用户自行设定
	mixed *func;									   //	用户回调函数信息
} private class clock_struct *all_alarm_clocks = ({}); //	保存当前存在的所有时钟结构
private
int next_st = 0; //	下一次需要执行的时间戳编号 -- 记录时钟结构在全部结构中的序号
private
int all_clocks_size = 0; //	记录一共有多少个时钟--包括不可用时钟
private
int is_clock_running = 0; //	时钟是否正在运行的标志
private
int alarm_clock_size = 0; //	当前拥有的有效闹钟个数 -- 不定期效对 -- DEBUG
private
int *alarm_clock_now = ({}); //	闹钟执行的先后顺序索引

private
static string *time_cycle_hash = ({
	SAC_TAG_YEAR,
	SAC_TAG_MONTH,
	SAC_TAG_DAY,
	SAC_TAG_HOUR,
	SAC_TAG_MINUTE,
	SAC_TAG_SECOND,
});
private
static mapping time_be_check = ([SAC_TAG_YEAR:({
												  0,
												  0,
												  6,
												  4,
												  TIME_YEAR,
											  }),
								SAC_TAG_MONTH:({
												  0,
												  0,
												  5,
												  2,
												  TIME_MON,
											  }),
								 SAC_TAG_WEEK:({
												  0,
												  0,
												  4,
												  2,
												  TIME_WDAY,
											  }),
								  SAC_TAG_DAY:({
												  0,
												  0,
												  4,
												  2,
												  TIME_MDAY,
											  }),
								 SAC_TAG_HOUR:({
												  0,
												  0,
												  3,
												  2,
												  TIME_HOUR,
											  }),
							   SAC_TAG_MINUTE:({
												  0,
												  0,
												  2,
												  2,
												  TIME_MIN,
											  }),
							   SAC_TAG_SECOND:({
												  0,
												  0,
												  1,
												  2,
												  TIME_SEC,
											  }),
]);
private
static mapping class_cycle_time = ([ //	比较有规律的时间周期集合
	1:1,
	2:1 * 60,
	3:1 * 60 * 60,
	4:1 * 60 * 60 * 24,
	6:1 * 60 * 60 * 24 * 365,
]);

/*--------------------------------公有函数接口----------------------------------------*/
/*------------------------------------常用--------------------------------------------*/
void turn_on_alarm_clock();																							  //	开启闹钟功能
void turn_off_alarm_clock();																						  //	关闭闹钟功能
int restore_alarm_clock();																							  //	关闭并重置所有时钟状态
int find_next_time_stamp(string max_unit, string time_str, string min_unit);										  //	根据字符信息找到下一个符合要求的时间戳正数
int add_alarm_clock(string max_unit, string time_str, string min_unit, mixed *f, int cycle_times, int per_cycle_sec); //	添加一个新的时间点到闹钟
int get_clock_running();																							  //	取得时钟是否在运行中
/*-----------------------------------不常用-------------------------------------------*/
int del_alarm_clock(int clock_num);																									 //	删除一个闹钟提醒，成功返回 1 失败返回 0
int upd_alarm_clock(int clock_num, string max_unit, string time_str, string min_unit, mixed *f, int cycle_times, int per_cycle_sec); //	修改一个闹钟提醒，成功返回 1 失败返回 0
/*----------------------------------功能函数------------------------------------------*/
string str(mixed int_num);				//	把一个整数转换成字符串
string show_time_stamp(int time_stamp); //	把一个时间戳整数还原为字串
/*------------------------------------完毕--------------------------------------------*/

//	重新设置系统时钟状态，并计算下次回调时间等标志
private
void reset_alarm_clock(int st_num)
{
	if (all_alarm_clocks[st_num]->times <= 1)
	{
		_DEBUG(sprintf("DEBUG -- Người sử dụng đồng hồ %d Hoàn tất việc bắt đầu xóa bỏ ~", st_num));
		all_alarm_clocks[st_num]->times = 0;
		del_alarm_clock(st_num);
	}
	else
	{
		if (all_alarm_clocks[st_num]->times < SAC_MAX_TIMES)
		{
			all_alarm_clocks[st_num]->times--;
		}
		all_alarm_clocks[st_num]->next_stamp = all_alarm_clocks[st_num]->next_stamp + all_alarm_clocks[st_num]->cycle_time;
	}
}
//	重置所有时钟状态,保证所有时钟均可正常运转
private
void reset_all_alarm_clock(int now_stamp)
{
	for (int i = 0; i < alarm_clock_size; i++)
	{
		if (all_alarm_clocks[alarm_clock_now[i]]->next_stamp < now_stamp - SAC_TIME_CACHE)
		{
			reset_alarm_clock(alarm_clock_now[i]);
		}
	}
}
//	判断一个时间整数是否在当前指定的时间范围内
private
int in_clock_range(int time_stamp, int st_num)
{
	return (all_alarm_clocks[st_num]->times > 0 && time_stamp >= all_alarm_clocks[st_num]->next_stamp - SAC_TIME_CACHE && time_stamp <= all_alarm_clocks[st_num]->next_stamp + SAC_TIME_CACHE) ? 1 : 0;
}
//	返回下一次需要回调的时钟编号
private
int prepare_next_call()
{
	int nearest_clock = all_alarm_clocks[alarm_clock_now[0]]->next_stamp;
	int st_num = 0;
	for (int i = 1; i < alarm_clock_size; i++)
	{
		if (all_alarm_clocks[alarm_clock_now[i]]->next_stamp < nearest_clock)
		{
			nearest_clock = all_alarm_clocks[alarm_clock_now[i]]->next_stamp;
			st_num = i;
		}
	}
	return alarm_clock_now[st_num];
}
//	时钟控制的主调函数
private
void open_alarm_clock()
{
	int now_time = time();
	int tmp_next_st;
	_DEBUG("DEBUG -- ----- Tiến vào kết cấu -----");
	reset_all_alarm_clock(now_time);
	if (alarm_clock_size > 0)
	{
		if (in_clock_range(now_time, next_st))
		{
			_DEBUG(sprintf("DEBUG -- %s Bắt đầu về điều đánh số là %d Người sử dụng hàm số", show_time_stamp(now_time), next_st));
			tmp_next_st = next_st;
			reset_alarm_clock(next_st);
			_DEBUG(sprintf("DEBUG -- %d Còn thừa về điều số lần là %d", tmp_next_st, all_alarm_clocks[tmp_next_st]->times));
			call_other(this_object(), all_alarm_clocks[tmp_next_st]->func + ({all_alarm_clocks[tmp_next_st]->times}));
			if (alarm_clock_size <= 0)
			{
				restore_alarm_clock();
				return;
			}
		}
		next_st = prepare_next_call();
		_DEBUG(sprintf("DEBUG -- Lần sau về điều đồng hồ đánh số là %d", next_st));
		_DEBUG(sprintf("DEBUG -- Lần sau về điều thời gian vì %s", show_time_stamp(all_alarm_clocks[next_st]->next_stamp)));
		call_out(SAC_CALL_OUT_FUNC, abs(all_alarm_clocks[next_st]->next_stamp - time()));
	}
}
//	判断一个星期/日的数字结构包含的秒数
private
int have_secs(int time_int)
{
	return ((time_int / 1000000) * 24 * 60 * 60) + (((time_int % 1000000) / 10000) * 60 * 60) + (((time_int % 10000) / 100) * 60) + (time_int % 100);
}
//	判断一个字典中是否存在某个 KEY
private
int mapping_has_key(mixed key_name, mapping map)
{
	mixed *map_key = keys(map);
	return member_array(key_name, map_key) == -1 ? 0 : 1;
}
//	空函数什么都不做 -- 可以用来调试
private
do_nothing(string str)
{
	_DEBUG(sprintf("DEBUG -- Chấp hành do_nothing: %s", str));
}

/*-----------------------------------------------------------------------------------------*\
	本类解析时间格式的规则算法，力求兼容更多格式的时间格式输入方法，力求简短有效 返回0 
	说明没有获取成功
\*-----------------------------------------------------------------------------------------*/
int find_next_time_stamp(string max_unit, string time_str, string min_unit)
{
	mixed *now_box;
	int i, week_time_user, week_time_now, tmp_time, tmp_len, now_time, str_len;
	int *time_area_slip = ({
		0,
		0,
		0,
		0,
		0,
		0,
	});
	now_time = time();
	if (!mapping_has_key(max_unit, time_be_check) || !mapping_has_key(min_unit, time_be_check))
	{
		_DEBUG("DEBUG -- Người sử dụng truyền vào đơn vị không tồn tại, chương trình trở về");
		return 0;
	}
	time_str = replace_string(time_str, "", "");
	time_str = replace_string(time_str, "-", "");
	time_str = replace_string(time_str, ":", "");
	if (max_unit == SAC_TAG_SECOND && min_unit == SAC_TAG_SECOND)
	{
		return now_time + to_int(time_str);
	}
	else
	{
		now_box = localtime(now_time);
		//	localtime 返回的月份数是  0-11 这里很不好理解因此+1已兼容 mktime
		now_box[TIME_MON] = now_box[TIME_MON] + 1;
		for (i = 0, tmp_len = 0; i < 6; i++)
		{
			if (time_be_check[max_unit][2] >= time_be_check[time_cycle_hash[i]][2] && time_be_check[min_unit][2] <= time_be_check[time_cycle_hash[i]][2])
			{
				tmp_len += time_be_check[time_cycle_hash[i]][3];
			}
		}
		str_len = strlen(time_str);
		if (str_len < tmp_len)
		{
			time_str = repeat_string("0", tmp_len - str_len) + time_str;
		}
		else if (str_len > tmp_len)
		{
			time_str = time_str[0..tmp_len];
		}
		//	取用户定义最近似的时间点
		for (i = 0, tmp_len = 0; i < 6; i++)
		{
			if (time_be_check[max_unit][2] >= time_be_check[time_cycle_hash[i]][2] && time_be_check[min_unit][2] <= time_be_check[time_cycle_hash[i]][2])
			{
				time_area_slip[i] = to_int(time_str[tmp_len..(tmp_len + time_be_check[time_cycle_hash[i]][3] - 1)]);
				tmp_len += time_be_check[time_cycle_hash[i]][3];
			}
			else if (time_be_check[min_unit][2] > time_be_check[time_cycle_hash[i]][2])
			{
				time_area_slip[i] = min_unit == SAC_TAG_MONTH ? 1 : 0;
			}
			else
			{
				time_area_slip[i] = now_box[time_be_check[time_cycle_hash[i]][4]];
			}
		}
		if (max_unit == SAC_TAG_WEEK)
		{
			week_time_user = to_int(sprintf("%s%02d%02d%02d", to_int(time_str[0..time_be_check [SAC_TAG_WEEK][3] - 1]) == 0 ? "7" : time_str[0..time_be_check [SAC_TAG_WEEK][3] - 1], time_area_slip[3], time_area_slip[4], time_area_slip[5]));
			week_time_now = (now_box[TIME_WDAY] == 0 ? 7 : now_box[TIME_WDAY]) * 1000000 + now_box[TIME_HOUR] * 10000 + now_box[TIME_MIN] * 100 + now_box[TIME_SEC];
			if (week_time_user < week_time_now)
			{
				return now_time + ((7 * 24 * 60 * 60) - (have_secs(week_time_now) - have_secs(week_time_user)));
			}
			else
			{
				return now_time + (have_secs(week_time_user) - have_secs(week_time_now));
			}
		}
		else
		{
			tmp_time = mktime(time_area_slip[0], time_area_slip[1], time_area_slip[2], time_area_slip[3], time_area_slip[4], time_area_slip[5]);
			if (tmp_time < now_time)
			{
				if (max_unit == SAC_TAG_YEAR)
				{
					_DEBUG("DEBUG -- Người sử dụng tiến nhập vào thời gian sai: Hạn mức cao nhất là năm đã không cách nào lại kéo dài")
					return 0;
				}
				if (max_unit == SAC_TAG_DAY)
				{
					if (time_area_slip[1] == 12)
					{
						return mktime(time_area_slip[0] + 1, 1, time_area_slip[2], time_area_slip[3], time_area_slip[4], time_area_slip[5]);
					}
					return mktime(time_area_slip[0], time_area_slip[1] + 1, time_area_slip[2], time_area_slip[3], time_area_slip[4], time_area_slip[5]);
				}
				_DEBUG(sprintf("DEBUG -- Trở về một cái tương đối thời gian chu kỳ %d", tmp_time + class_cycle_time[time_be_check[max_unit][2] + 1]));
				return tmp_time + class_cycle_time[time_be_check[max_unit][2] + 1];
			}
			return tmp_time;
		}
	}
}

//	开启闹钟
void turn_on_alarm_clock()
{
	is_clock_running = 1;
	_DEBUG("DEBUG -- Mở đồng hồ báo thức");
	open_alarm_clock();
}

//	关闭闹钟
void turn_off_alarm_clock()
{
	is_clock_running = 0;
	_DEBUG("DEBUG -- Tắt đồng hồ báo thức");
	remove_call_out(SAC_CALL_OUT_FUNC);
}

//	关闭并重置所有时钟状态
int restore_alarm_clock()
{
	turn_off_alarm_clock();	 //	关闭时钟
	all_alarm_clocks = ({}); //	清空所有时钟变量
	alarm_clock_now = ({});	 //	清空所有当前变量
	next_st = 0;			 //	下一次需要执行的时间戳编号 -- 记录时钟结构在全部结构中的序号
	all_clocks_size = 0;	 //	记录一共有多少个时钟--包括不可用时钟
	is_clock_running = 0;	 //	时钟是否正在运行的标志
	alarm_clock_size = 0;	 //	当前拥有的有效闹钟个数 -- 不定期效对 -- DEBUG
	_DEBUG("DEBUG -- Đồng hồ tuần hoàn đã kết thúc, đồng hồ trở về trạng thái ban đầu");
	return 1; //	正常情况下是不会出错的全部返回 1
}

//	获取当前是否在运行的标志
int get_clock_running()
{
	return is_clock_running;
}

//	添加一个闹钟提醒，成功返回 >-1 数字表示当前获得的时钟编号 失败返回 -1
int add_alarm_clock(string max_unit, string time_str, string min_unit, mixed *f, int cycle_times, int per_cycle_sec)
{
	class clock_struct new_alarm_clock;
	int tmp_time;
	_DEBUG(sprintf("DEBUG -- %s Tăng thêm thời gian: Bắt đầu phân tích xâu chuỗi", show_time_stamp(time())));
	tmp_time = find_next_time_stamp(max_unit, time_str, min_unit);
	if (!tmp_time)
	{
		return -1;
	}
	_DEBUG(sprintf("DEBUG -- Lúc này về lại thời gian:%s Về điều số lần:%d", show_time_stamp(tmp_time), cycle_times));
	new_alarm_clock = new (class clock_struct);
	new_alarm_clock->times = cycle_times ? cycle_times : 1;
	new_alarm_clock->next_stamp = tmp_time;
	new_alarm_clock->cycle_time = per_cycle_sec ? per_cycle_sec : 1;
	new_alarm_clock->func = arrayp(f) ? f : ({"do_nothing", max_unit + "." + time_str + "." + min_unit});
	all_alarm_clocks += ({new_alarm_clock});
	alarm_clock_now += ({all_clocks_size});
	alarm_clock_size++;
	next_st = prepare_next_call();
	if (is_clock_running)
	{
		remove_call_out(SAC_CALL_OUT_FUNC);
		call_out(SAC_CALL_OUT_FUNC, abs(all_alarm_clocks[next_st]->next_stamp - time()));
	}
	_DEBUG(sprintf("DEBUG -- Trước mắt hữu hiệu đồng hồ số lượng vì:%d", alarm_clock_size));
	_DEBUG(sprintf("DEBUG -- Lần này đồng hồ số hiệu là:%d", all_clocks_size));
	_DEBUG(sprintf("DEBUG -- Lần sau về điều đồng hồ số hiệu:%d", next_st));
	return all_clocks_size++;
}

//	修改一个闹钟提醒，成功返回 1 失败返回 0
int upd_alarm_clock(int clock_num, string max_unit, string time_str, string min_unit, mixed *f, int cycle_times, int per_cycle_sec)
{
	int tmp_time;
	int tmp_next_st = next_st;
	if (0 > member_array(clock_num, alarm_clock_now))
	{
		return 0;
	}
	if (mapping_has_key(max_unit, time_be_check) && mapping_has_key(min_unit, time_be_check) && time_str && time_str != "0")
	{
		tmp_time = find_next_time_stamp(max_unit, time_str, min_unit);
		if (!tmp_time)
		{
			return 0;
		}
		all_alarm_clocks[clock_num]->next_stamp = tmp_time;
	}
	if (cycle_times)
	{
		all_alarm_clocks[clock_num]->times = cycle_times;
	}
	if (per_cycle_sec)
	{
		all_alarm_clocks[clock_num]->cycle_time = per_cycle_sec;
	}
	if (arrayp(f))
	{
		all_alarm_clocks[clock_num]->func = f;
	}
	next_st = prepare_next_call();
	if (next_st != tmp_next_st && is_clock_running)
	{
		remove_call_out(SAC_CALL_OUT_FUNC);
		call_out(SAC_CALL_OUT_FUNC, abs(all_alarm_clocks[next_st]->next_stamp - time()));
	}
	return 1;
}

//	删除一个闹钟提醒，成功返回 1 失败返回 0
int del_alarm_clock(int clock_num)
{
	int tmp_next_st = next_st;
	if (0 > member_array(clock_num, alarm_clock_now))
	{
		_DEBUG(sprintf("DEBUG -- Không cách nào xóa bỏ đánh số là %d Đồng hồ, số hiệu không tồn tại", clock_num));
		return 0;
	}
	if (--alarm_clock_size > 0)
	{
		alarm_clock_now -= ({clock_num});
		_DEBUG(sprintf("DEBUG -- Thành công xóa bỏ đánh số là %d Đồng hồ, trước mắt có %d Cái đồng hồ còn thừa", clock_num, sizeof(alarm_clock_now)));
		next_st = prepare_next_call();
		if (next_st != tmp_next_st && is_clock_running)
		{
			remove_call_out(SAC_CALL_OUT_FUNC);
			call_out(SAC_CALL_OUT_FUNC, abs(all_alarm_clocks[next_st]->next_stamp - time()));
		}
		return 1;
	}
	alarm_clock_size = 0;
	return 1;
}

//	整数转换成字符串
string str(mixed int_num)
{
	return sprintf("%d", to_int(int_num));
}
//	把当前时间戳显示为一个可识别的时间字串
string show_time_stamp(int time_stamp)
{
	mixed *time_box = localtime(time_stamp);
	return sprintf("%04d-%02d-%02d %02d:%02d:%02d", time_box[TIME_YEAR], time_box[TIME_MON] + 1, time_box[TIME_MDAY], time_box[TIME_HOUR], time_box[TIME_MIN], time_box[TIME_SEC]);
}

/*------------------------------------------------------------------------------------------*\
	测试：以下代码用来调试此类的功能，运行test_main 便可获得结果
\*------------------------------------------------------------------------------------------*/
void test_func_1(string str, int times)
{
	if (times == 2)
	{
		if (0 > add_alarm_clock("second", "5", "second", ({"do_nothing", "Nửa đường tăng thêm một lần khảo thí hàm số thành công!"}), 3, 1))
		{
			_DEBUG("DEBUG_f -- Tăng thêm hàm số thành công!");
		}
		else
		{
			_DEBUG("DEBUG_f -- Tăng thêm khảo thí thành công!");
		}
	}
	_DEBUG(sprintf("DEBUG_f -- Thứ %d Lần %s Thành công!", 3 - times, str));
}
void test_func_2(string str, int times)
{
	_DEBUG(sprintf("DEBUG_f -- Về điều khảo thí hàm số 2 còn thừa %d lần", times));
	_DEBUG(sprintf("DEBUG_f -- Kèm theo: %s", str));
}
void test_func_3(string str, int times)
{
	_DEBUG(sprintf("DEBUG_f -- Về điều khảo thí hàm số 3 Còn thừa %d lần", times));
	_DEBUG(sprintf("DEBUG_f -- Kèm theo: %s", str));
	add_alarm_clock("second", "3", "second", ({"test_func_2", "Hàm số 3 Định thời gian điều động 2"}), 1, 0);
	if (times == 2)
	{
		add_alarm_clock("second", "30", "second", ({"test_func_2", "Hàm số 3 Trì hoãn điều động 2"}), 1, 0);
	}
	else if (times == 1)
	{
		add_alarm_clock("second", "10", "second", ({"test_func_4", "Hàm số 3 Định thời gian điều động 4", 3}), 2, CYCLE_MINUTE);
	}
}
void test_func_4(string str, int number, int times)
{
	_DEBUG(sprintf("DEBUG_f -- Về điều khảo thí hàm số 4 Còn thừa số lần %d", times));
	_DEBUG(sprintf("DEBUG_f -- Thu hoạch số lượng tham số %d", number));
}
void test_main()
{
	_DEBUG("Khảo thí bắt đầu");
	turn_on_alarm_clock();
	add_alarm_clock("year", "########", "minute", ({"test_func_1", "main Điều động 1"}), 3, 1);
	add_alarm_clock("day", "11 11:43:05", "second", ({"test_func_2", "main Điều động 2"}), 2, 2);
	add_alarm_clock("week", "3 11:44:20", "second", ({"test_func_3", "main Điều động 3"}), 3, CYCLE_MINUTE);
	_DEBUG("Ban đầu hóa đồng hồ báo thức kết thúc");
}
