/*------------------------------------------------------------------------------------------*\
	惊天大爆装的活动控制文件
	07-06-26 	由 Cjxx 创建
	07-06-27  18:46 调试完成时间控制框架
	07-06-28  18:00 完成时间轮寻控制框架（修复之前一个严重BUG）
\*------------------------------------------------------------------------------------------*/
#include <ansi.h>
#include <time.h>
#include <public.h>
inherit SAVE_F;


#define _DEBUG(str) 		  ;//if(objectp(find_char("1"))) tell_user(find_char("1"),str);

#define BZ_WEEK 		  "week"		//	星期轮寻标志
#define BZ_MONTH		  "month"		//	月份轮寻标志
#define BZ_DAY			  "day"			//	天数轮寻标志
#define BZ_HOUR			  "hour"		//	小时轮寻标志

private string active_name	= "惊天大爆装";		//	活动名称
private string cycle_way	= "week";		//	活动轮训规则 BZ_WEEK / BZ_MONTH / BZ_DAY / BZ_HOUR

private int BZ_ACTIVE_BEFORE1	= 5;			//	活动开始前的第一个时间点（分）
private int BZ_ACTIVE_BEFORE2	= 50;			//	活动开始时的第二个时间点（分）--本类暂不支持对此时间点的控制
private int BZ_TIME_CACHE	= 1;			//	临界时间缓冲 -- 可忽略的时间分钟数

private int active_from		= 51700;		//	活动开始时间 [0-6]/[1-31][0-23][0-59] -- 依据活动的轮巡模式
private int active_to		= 51800;		//	活动结束时间 [0-6]/[1-31][0-23][0-59]

private int if_active		= 0;			//	活动是否开始的标志
private int if_active_next	= 1;			//	是否自动开启下一次的标志
private int if_step_near_time	= 0;			//	活动开始前的临近时间是否进行倒分钟记时

private int time_clip(int time_int, int mins); 		//	时间轴整数相减
private int time_add( int time_int, int mins);		//	时间轴整数相加
private int have_mins(int time_int);			//	取得当前整数时间所拥有的分钟数
private int get_time(string way);			//	获取一个系统认可的整数时间戳
private int in_time_area(int time_int, int time_from, int time_to);	//	判断某时间点是否在一个时间段内
private int count_during_time(int time_from, int time_to);		//	计算到下一个时间周期所需要的分钟数


//	爆装活动相关变量设置
private static object *lao_renzha=({});
private static mixed renzha_position= ({
	({010,150,203,}),
	({020,170,168,}),
	({030,142,127,}),
	({040,223,73 ,}),
	({050,239,133,}),
	({060,113,167,}),
	({070,289,183,}),	
});

void turn_off_activity();
void turn_on_activity();

void do_activity();					//	活动流程执行的函数
void on_active_before(int callout_delay_time);		//	活动开始时执行的函数
void on_active_near(int callout_delay_time);		//	活动临近时执行的函数
void on_active_playing(int callout_delay_time);		//	活动开始时执行的函数
void on_active_finish(int callout_delay_time);		//	活动刚刚结束时执行的函数

void SAVE_BINARY() {}

string get_save_file()	{ 
	return "data/baozhuang"SAVE_EXTENSION;
}

//	构造函数
void create() {
	restore();
}

//	设定活动的开始和结束时间 -- 当开始时间大于结束时间时则为跨时间段区域的操作
void set_active_time(int from, int to) {
	int tmp_active_on = if_active;
	active_from = (cycle_way == BZ_WEEK && from > 70000) ? from - 70000 : from;
	active_to   = (cycle_way == BZ_WEEK && to   > 70000) ? to   - 70000 : to;
	turn_off_activity();
	if(tmp_active_on) {
		turn_on_activity();
	}
	_DEBUG(sprintf("设置时间 %d <--> %d",active_from,active_to));
	save();
}

//	取得活动开始结束时间以 “-” 分割开
string get_active_time() {
	return sprintf("%d-%d",active_from,active_to);
}

//	设置周期模式
void set_cycle_way(string way) {
	cycle_way = way == BZ_WEEK ? way : way == BZ_MONTH ? way : way == BZ_DAY ? way : BZ_HOUR;
	save();
	_DEBUG(sprintf("设置运转周期为 %s",cycle_way));	
}

// 	设置活动临近时间点1
void set_active_before1(int mins) {
	BZ_ACTIVE_BEFORE1 = mins;
	save();
}

//	设置时间临界缓冲
void set_time_cache(int mins) {
	BZ_TIME_CACHE = mins;
	save();
}

//	开启活动
void turn_on_activity() {	
	turn_off_activity();
	_DEBUG("DEBUG -- 开启活动");
	if_active = 1;
	do_activity();
	save();
}

//	关闭活动
void turn_off_activity() {
	_DEBUG("DEBUG -- 关闭活动");
	if_active = 0;
	on_active_finish(0);
	do_activity();
	save();
}

//	把当前时间戳显示为一个可识别的时间字串
string show_time_stamp(int time_stamp) {
	mixed *time_box = localtime(time_stamp);
	return sprintf("%04d-%02d-%02d %02d:%02d:%02d",time_box[TIME_YEAR],time_box[TIME_MON]+1,time_box[TIME_MDAY],time_box[TIME_HOUR],time_box[TIME_MIN],time_box[TIME_SEC]);
}

//	进行活动 -- 中心时间调配器（本类的中心控制函数）
void do_activity() {	
	string func_name = "do_activity";
	int now_time ,callout_delay_time;
	if(!if_active) {
		remove_call_out(func_name);
		return;
	}
	now_time = get_time(cycle_way);
	if(in_time_area(now_time,time_clip(active_from,BZ_ACTIVE_BEFORE1),active_from)) {
		callout_delay_time = count_during_time(now_time,active_from);
		on_active_near(callout_delay_time);		//	活动前几分钟
		call_out(func_name,if_step_near_time ? 60 : callout_delay_time*60);
		return;		
	} else if(in_time_area(now_time,time_clip(active_from,BZ_TIME_CACHE),active_to)) {
		callout_delay_time = count_during_time(now_time,time_add(active_to,BZ_TIME_CACHE));
		on_active_playing(callout_delay_time);		//	活动中
		call_out(func_name,callout_delay_time*60);
		return;		
	} else if(in_time_area(now_time,time_clip(active_to,BZ_TIME_CACHE?BZ_TIME_CACHE:1),time_add(active_to,BZ_TIME_CACHE+2))) {
		on_active_finish(0);				//	活动刚刚结束
		if(!if_active_next) {
			remove_call_out(func_name);
			return;
		}
	}
	callout_delay_time = count_during_time(now_time,time_clip(active_from,BZ_ACTIVE_BEFORE1));
	on_active_before(callout_delay_time);			//	活动之外 （之后 / 之前）
	call_out(func_name,callout_delay_time*60);
	_DEBUG(sprintf("下次回调时间是 %s",show_time_stamp(time()+callout_delay_time*60)));
}

//	活动开始时执行的函数
void on_active_before(int callout_delay_time) {
	_DEBUG(sprintf("DEBUG--目前活动还没有开始，再次调用活动函数在（%d）分钟后",callout_delay_time));
}
//	活动临近时执行的函数
void on_active_near(int callout_delay_time) {
	_DEBUG(sprintf("DEBUG-- 现在是活动前的几分钟状态，活动正式开始在（%d）分钟后",callout_delay_time));
	USER_D->user_channel(sprintf("%d分钟后超丰厚奖励的%s活动即将开始，为了得到更好的装备，冲啊！",callout_delay_time,active_name));	
}

//	设置NPC的一般属性
void set_npc_status(object npc,int level,int *skills,int *other_stat) {
	int i,size;
	for(i=0,size=sizeof(skills);i<size;i++) {	//	设置技能
		npc->set_skill(skills[i],level);
	}
	if(other_stat[0]) {				//	0 设置行进速度
		npc->set_walk_speed(other_stat[0]);
	}
	if(other_stat[1]) {				//	1 设置攻击速度
		npc->set_attack_speed(other_stat[1]);
	}
	if(other_stat[2]) {				//	2 增加物理防御
		npc->add_dp(npc->get_dp()*other_stat[2]/100);
	}
	if(other_stat[3]) {				//	3 增加血上限
		npc->add_max_hp(npc->get_max_hp()*other_stat[3]/100);
	}
	if(other_stat[4]) {				//	4 增加躲闪
		npc->add_sp(npc->get_sp()*other_stat[4]/100);
	}
	if(other_stat[5]) {				//	5 增加物理攻击			
		npc->add_ap(npc->get_ap()*other_stat[5]/100);		
	}
	if(other_stat[6]) {				//	6 增加法术力
		npc->add_mp(npc->get_mp()*other_stat[6]/100);
	}
	if(other_stat[7]) {				//	7 增加法防
		npc->add_pp(npc->get_pp()*other_stat[7]/100);
	}
	if(other_stat[8]) {				//	8 增加法术攻击力
		npc->add_cp(npc->get_cp()*other_stat[8]/100);
	}
	if(other_stat[9]) {				//	9 设定怪物类型
		npc->set("robber.type",other_stat[9]);	
	}
}
//	活动开始时执行的函数 -- 这里写死在爆装活动中了先
void on_active_playing(int callout_delay_time) {
	int x,y,z,i,count,burst_point,rand_int,level;
	object map,renzha;
	level = 80;
	_DEBUG(sprintf("DEBUG--目前活动正在进行中，再次调用活动函数在（%d）分钟后",callout_delay_time));
	USER_D->user_channel(sprintf("%s活动已经开始了，为了得到更好的装备，速速去七国城外消灭老人渣吧！",active_name));
	for(i=0,count=1;i<100;i++) {
		burst_point = XY_D->get_city_point(count,IS_CHAR_BLOCK);
		if(!burst_point) {
			_DEBUG("DEBUG -- 地图坐标没有初始化成功");
			continue;
		}
		renzha = new("npc/boss/9962_laorenzha");
		if(!objectp(renzha)) {
			_DEBUG("DEBUG--老人渣没有生成成功");
			continue;
		}
		NPC_ENERGY_D->init_level(renzha,level);	//	给这个家伙设置一下等级
		renzha->set_max_seek(8);
		rand_int = random(100);			//	100 几率去做一些通用设置
		_DEBUG(sprintf("门派随机数%d",rand_int));
		if(rand_int < 20) {			//	低物防高敏
			set_npc_status(renzha,level,({3483,2512,2416}),({3,10,-30,60000,1100,10,50,0,0,1}));
		} else if(rand_int < 40 ) {		//	高物防低法防
			set_npc_status(renzha,level,({2216,2313,2314}),({3,10,300,60000,0,20,50,-40,0,2}));
		} else if(rand_int < 60 ) {		//	高法防低物防
			set_npc_status(renzha,level,({4251,4231,4232,4234,4243}),({4,10,-30,60000,0,0,600,80,20,3}));
		} else if(rand_int < 70 ) {		//	长血
			set_npc_status(renzha,level,({3173,2118,2114,2115}),({3,10,-30,75000,0,30,30,-30,0,4}));
		} else if(rand_int < 90 ) {		//	长血高物防高法防
			set_npc_status(renzha,level,({3632,2616,2615}),({3,10,35,60000,300,50,100,100,0,5}));
		} else {				//	强攻加召唤
			renzha->set_char_picid(8013);
			set_npc_status(renzha,level,({4143,4144,4145}),({3,8,45,60000,300,0,150,45,0,6}));
		}
		z =  burst_point / 1000000;	
		x = (burst_point % 1000000) / 1000;
		y =  burst_point % 1000;
		//_DEBUG(sprintf("DEBUG--(Z-%03d X-%03d Y-%03d)",z,x,y));
		if( !objectp( map = get_map_object(z) ) || !map->is_scene() ) {
			_DEBUG("DEBUG-- 地图处理没有成功");
			continue;
		}
		//	放入到相应的城市中间去
		//	07-07-16 P12:26 修改为定点坐标
		renzha->add_to_scene(renzha_position[count-1][0],renzha_position[count-1][1],renzha_position[count-1][2],3);
		_DEBUG(sprintf("DEBUG--(Z-%03d X-%03d Y-%03d)",renzha_position[count-1][0],renzha_position[count-1][1],renzha_position[count-1][2]));
		//renzha->add_to_scene(z,x,y,3);
		map->add_reset(renzha);
		//	保存指针到一个数组中
		lao_renzha += ({renzha});		
		if(++count > 7 ) {
			break;
		}
	}
}
//	活动刚刚结束时执行的函数
void on_active_finish(int callout_delay_time) {
	int i , size;
	_DEBUG(sprintf("DEBUG--目前活动刚刚结束，再次调用活动函数在（%d）分钟后",callout_delay_time));
	//	活动结束 -- 设置老人渣的消失状态 -- NPC 内部也会进行相应的清楚操作，因此这里有双保险
	for(i=0,size=sizeof(lao_renzha);i<size;i++) {
		if(objectp(lao_renzha[i]) && !objectp(lao_renzha[i]->get_enemy())) {
			lao_renzha[i]->remove_from_scene();
			destruct(lao_renzha[i]);
		}
	}
	lao_renzha = ({});
}

//	取得当前整数时间所拥有的分钟数
private int have_mins(int time_int) {
	return ((time_int/10000)*24*60) + ((time_int % 10000)/100)*60 + (time_int % 100);
}
//	取得当前指定模式的时间整数 -- week / month / day / hour 默认为 week
private int get_time(string way) {
	mixed *now_box = localtime(time());
	switch(way) {
		default:
		case BZ_WEEK : return now_box[TIME_WDAY]*10000 + now_box[TIME_HOUR]*100 + now_box[TIME_MIN];
		case BZ_MONTH: return now_box[TIME_MDAY]*10000 + now_box[TIME_HOUR]*100 + now_box[TIME_MIN];
		case BZ_DAY  : return now_box[TIME_HOUR]*100 + now_box[TIME_MIN];
		case BZ_HOUR : return now_box[TIME_MIN];
	}
}
//	指定时间的控制函数 -- 分钟数还原成一个周期内的时间整数戳，如果超过周期则截取至一个周期
private int time_cont(int h_mins) {
	switch(cycle_way) {
		default:
		case BZ_WEEK : h_mins = h_mins % (7*24*60);	break;
		case BZ_MONTH: h_mins = h_mins % (32*24*60) +1;	break;
		case BZ_DAY  : h_mins = h_mins % (24*60);	break;
		case BZ_HOUR : h_mins = h_mins % (60);		break;
	}
	return (h_mins/(24*60))*10000 + ((h_mins % (24*60)) / 60)*100 + ((h_mins % (24*60)) % 60);
}
//	计算一段相对时间的差值
private int count_during_time(int time_from, int time_to) {
	if(time_from <= time_to) {
		return have_mins(time_clip(time_to,have_mins(time_from)));
	} else {
		switch(cycle_way) {
			default:
			case BZ_WEEK : return (7*24*60) - (have_mins(time_from) - have_mins(time_to));
			case BZ_MONTH: return (31*24*60)- (have_mins(time_from) - have_mins(time_to));
			case BZ_DAY  : return (24*60)   - (have_mins(time_from) - have_mins(time_to));
			case BZ_HOUR : return (60)      - (have_mins(time_from) - have_mins(time_to));
		}
	}
}
//	指定时间整数的减操作 -- 被减数如果超出本星期的范围则轮寻到上一个星期的时间值
private int time_clip(int time_int, int mins) {
	return time_cont(have_mins(time_int)-mins);	
}
//	指定时间整数的加操作 -- 被加数如果超出本星期的范围则轮寻到下一个星期的时间值
private int time_add(int time_int, int mins) {
	return time_cont(have_mins(time_int)+mins);
}
//	判断给定的时间戳整数是否在特定时间端内 在则返回 1 否则返回 0 
private int in_time_area(int time_int, int time_from, int time_to) {
	int l = time_int < time_from ? 0 : 1;
	int r = time_int >= time_to  ? 0 : 1;
	return time_from < time_to ? l&r : l|r;
}