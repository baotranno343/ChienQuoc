#include <ansi.h>
#include <skill.h>
inherit COMBINED;
inherit ITEM;

int get_item_value() {return 175 ;}
int get_item_value_2() {return 140 ;}
int get_item_number() {return 10001005 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("战国号角");
        set_picid_1(0095);
        set_picid_2(0095);
        set_value(100);
        set_amount(1);
        set_record(1);
        // -- 与原装备相比增加绑定属性
        set_no_give(1);
        set_no_sell(1);
        //        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "神奇的号角，只有当使用者是队长的时候才会生效。\n持续一个小时内同队伍所有成员在消灭怪物后可额外获得20％的经验奖励。"; 
}
// 函数：获取描述(持续)加血
string get_loop_desc( object me )
{
	return "一小时内同队伍成员可获得20％的经验奖励。";
}
int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	int iWeek;
	
	if ( time() < who->get_extra_exp_time() )
	{
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("你身上已经有一个战国号角在产生作用，你确定要覆盖它的效果吗？\n"ESC"确定\nuse ! %x#\n"ESC"取消",getoid(item))); 
		return 0;
	}
	
	iWeek = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
	if (who->get_save_2("double_time.week")!=iWeek)
	{
		who->set_save_2("double_time.week", iWeek);
		who->set_save_2("double_time.time", 0);		//双
		who->set_save_2("double_time.time1", 0);	//战国令
		who->set_save_2("double_time.time2", 0);	//战国号角
	}
	if ( who->get_save_2("double_time.time2") >= 25 )
	{
		send_user(who,"%c%s",'!',"你本周可使用战国号角已经达到了使用上限。");
		return 0;	
	}
	if ( who->get_online_rate() == 50 )
	{
		send_user(who,"%c%s",'!',"疲劳游戏时间禁止使用战国号角。");
		return 0;	
	}
	else if ( who->get_online_rate() == 0 )
	{
		send_user(who,"%c%s",'!',"不健康游戏时间禁止使用战国号角。");
		return 0;	
	}
	who->add_save_2("double_time.time2",1);
	who->set_extra_exp_time(time()+3600);
	send_user( who, "%c%w%w%c", 0x81, 9999, 3600, EFFECT_GOOD );
	return 1;
}
// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	int iWeek;
	
	iWeek = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
	if (who->get_save_2("double_time.week")!=iWeek)
	{
		who->set_save_2("double_time.week", iWeek);
		who->set_save_2("double_time.time", 0);		//双
		who->set_save_2("double_time.time1", 0);	//战国令
		who->set_save_2("double_time.time2", 0);	//战国号角
	}
	if ( who->get_save_2("double_time.time2") >= 25 )
	{
		send_user(who,"%c%s",'!',"你本周可使用战国号角已经达到了使用上限。");
		return 0;	
	}
	if ( who->get_online_rate() == 50 )
	{
		send_user(who,"%c%s",'!',"疲劳游戏时间禁止使用战国号角。");
		return 0;	
	}
	else if ( who->get_online_rate() == 0 )
	{
		send_user(who,"%c%s",'!',"不健康游戏时间禁止使用战国号角。");
		return 0;	
	}
	who->add_save_2("double_time.time2",1);
	who->set_extra_exp_time(time()+3600);
	send_user( who, "%c%w%w%c", 0x81, 9999, 3600, EFFECT_GOOD );
	return 1;
}
