#include <ansi.h>
#include <skill.h>
inherit COMBINED;
inherit ITEM;

int get_item_value() {return 450 ;}
int get_item_value_2() {return 380 ;}
int get_item_number() {return 10001006 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("Chiến Quốc Lệnh");
        set_picid_1(0096);
        set_picid_2(0096);
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
        return "神奇的令牌，使用后持续一个小时内消灭的怪物可获得双倍的经验奖励。\n（令牌的效果无法叠加，每周最多只能使用25个。）"; 
}
// 函数：获取描述(持续)加血
string get_loop_desc( object me )
{
	return "一小时内可获得双倍经验奖励。";
}
int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	int i,iWeek;
	if ( gone_time( who->get_login_time() )+ who->get_game_time()<who->get_double_time())
	{
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("你身上已经有双倍时间存在，你确定要累加它的效果吗？\n"ESC"确定\nuse ! %x#\n"ESC"取消",getoid(item))); 
		return 0;
	}
	iWeek = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
	if (who->get_save_2("double_time.week")!=iWeek)
	{
		who->set_save_2("double_time.week", iWeek);
		who->set_save_2("double_time.time", 0);		//双
		who->set_save_2("double_time.time1", 0);	//战国令
		who->set_save_2("double_time.time2", 0);	//战国号角
		who->set_save_2("double_time.time3", 0);	//战国号角
		who->set_save_2("double_time.freeze", 0);	//冻结的双倍时间		
	}
	if ( who->get_save_2("double_time.time1") >= 25 )
	{
		send_user(who,"%c%s",'!',"你本周可使用战国令已经达到了使用上限。");
		return 0;	
	}
	if ( who->get_online_rate() == 50 )
	{
		send_user(who,"%c%s",'!',"疲劳游戏时间禁止使用战国令。");
		return 0;	
	}
	else if ( who->get_online_rate() == 0 )
	{
		send_user(who,"%c%s",'!',"不健康游戏时间禁止使用战国令。");
		return 0;	
	}
	if (who->get_save_2("double_time.freeze")>3600*18)
	{
		send_user(who,"%c%s",'!',"您冻结的双倍时间超过了18小时");
		return 0;		
	}
	i = gone_time( who->get_login_time() );		
	who->add_save_2("double_time.time1",1);
	
	if (who->get_save_2("double_time.freeze")>0)
	{
		who->add_save_2("double_time.freeze", 3600);
		send_user( who, "%c%c%d%s", 0x43, 10, 0, HIY "你的双倍经验时间已经寄存到神仙爷爷处。" );
	        "/inh/user/mail"->sys_mail(who->get_id(), who->get_number(), "因为你已经使用了双倍经验的冻结，因此使用战国令后得到的双倍经验时间也会一并寄存在"HIR"周国（291，175）或新手村（91，164）的神仙爷爷"NOR"处。请你务必记得在"HIR"周日的23：59分前解除双倍时间的冻结"NOR"，否则寄存的双倍经验时间会被系统回收掉。");
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,0001,"游戏辅助" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "双倍时间" );
		"/sys/task/task"->send_task_intro(who, 1, 1, 1);				        
		return 1;
	}	
	if ( i+ who->get_game_time()<who->get_double_time())
		who->set_double_time(who->get_double_time()+3600);
	else
		who->set_double_time(i+ who->get_game_time()+3600);	
	send_user( who, "%c%w%w%c", 0x81, 9998, 3600, EFFECT_GOOD );
	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,0001,"游戏辅助" ); 
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "双倍时间" ); 
	"/sys/task/task"->send_task_intro(who, 1, 1, 1);		
	return 1;
}

// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	int i,iWeek;

	iWeek = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
	if (who->get_save_2("double_time.week")!=iWeek)
	{
		who->set_save_2("double_time.week", iWeek);
		who->set_save_2("double_time.time", 0);		//双
		who->set_save_2("double_time.time1", 0);	//战国令
		who->set_save_2("double_time.time2", 0);	//战国号角
		who->set_save_2("double_time.time3", 0);	//战国号角
		who->set_save_2("double_time.freeze", 0);	//冻结的双倍时间
	}
	if ( who->get_save_2("double_time.time1") >= 25 )
	{
		send_user(who,"%c%s",'!',"你本周可使用战国令已经达到了使用上限。");
		return 0;	
	}
	if ( who->get_online_rate() == 50 )
	{
		send_user(who,"%c%s",'!',"疲劳游戏时间禁止使用战国令。");
		return 0;	
	}
	else if ( who->get_online_rate() == 0 )
	{
		send_user(who,"%c%s",'!',"不健康游戏时间禁止使用战国令。");
		return 0;	
	}
	who->add_save_2("double_time.time1",1);
	if (who->get_save_2("double_time.freeze")>0)
	{
		who->add_save_2("double_time.freeze", 3600);
	        send_user(who, "%c%s", '!', "你的双倍经验时间已经寄存到神仙爷爷处。");
	        "/inh/user/mail"->sys_mail(who->get_id(), who->get_number(), "因为你已经使用了双倍经验的冻结，因此使用战国令后得到的双倍经验时间也会一并寄存在"HIR"周国（291，175）或新手村（91，164）的神仙爷爷"NOR"处。请你务必记得在"HIR"周日的23：59分前解除双倍时间的冻结"NOR"，否则寄存的双倍经验时间会被系统回收掉。");
		send_user( who, "%c%c%c%w%s", 0x51, 1, 1,0001,"游戏辅助" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "双倍时间" );
		"/sys/task/task"->send_task_intro(who, 1, 1, 1);				        
		return 1;
	}	
	i = gone_time( who->get_login_time() );	
	if ( gone_time( who->get_login_time() )+ who->get_game_time()<who->get_double_time())
		who->set_double_time( who->get_double_time()+3600);
	else
		who->set_double_time(i+ who->get_game_time()+3600);
	send_user( who, "%c%w%w%c", 0x81, 9998, who->get_double_time() - i - who->get_game_time(), EFFECT_GOOD );
	send_user( who, "%c%c%c%w%s", 0x51, 1, 1,0001,"游戏辅助" ); 
	send_user( who, "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 1, "双倍时间" ); 
	"/sys/task/task"->send_task_intro(who, 1, 1, 1);
	return 1;
}