#include <ansi.h>
#include <time.h>
#include <task.h>
inherit ITEM;

int is_usable() { return 1; }

// 函数:构造处理
void create()
{
        set_name("Hồ Lô Thu Yêu");
        set_picid_1(3514);
        set_picid_2(3514);
        set_unit("个");
        set_value(1);
        set_no_give(1);
        set_no_get(1);
        set_no_drop(1);
        set_no_sell(1); 
}

// 函数:获取描述
string get_desc() 
{ 
	object me = this_player();
	if (me)
        	return sprintf("Dùng để thu thập yêu quái hút vào Hồ Lô Thu Yêu\nSố lượng thu thập:%d/450", me->get_save_2("refine.count")) ;
        else
        	return "Dùng để thu thập yêu quái hút vào Hồ Lô Thu Yêu" ;
}

// 函数:使用效果
int get_use_effect( object me ) 
{
	return __FILE__->use_item(me,this_object());	
}

int use_item(object me, object item)
{
	int level, exp;
	int iTime, day;
	mixed *mxTime;
	if (me->get_save_2("refine.status")!=1) return 1;
	if (me->get_save_2("refine.count")>=450) 
	{
		iTime = time();
		mxTime = localtime(iTime);
		day = mxTime[TIME_YDAY];			
		level = me->get_save_2("refine.level");
		exp = "/sys/npc/energy"->get_exp_bonus(level);
		exp = exp*450/2;
		me->add_exp(exp);
                me->add_log("&refine", exp);
                me->add_log("#refine", 1);	
                me->set_save_2("refine.status", 2);
                me->set_save_2("refine.day", day);
                me->set_save_2("refine.count", 0);
                write_user( me, HIR "Thu thập yêu quái, bạn được thưởng %d điểm kinh nghiệm.", exp );	
                send_user(me, "%c%s", ';', sprintf(HIR "Thu thập yêu quái, bạn được thưởng %d điểm kinh nghiệm.", exp ));	
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_REFINE, 1, "" );
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1, TID_REFINE, "" );                
		return 1;
	}
	send_user( me, "%c%s", '!', "Chưa thu thập đủ số lượng.");
	return 0;
}