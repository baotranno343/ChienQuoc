
#include <npc.h>
#include <ansi.h>
#include <effect.h>
#include <task.h>
#include <equip.h>
#include <time.h>

inherit OFFICER;

void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 9312; } 

// 函数：构造处理
void create()
{
        set_name( "伯乐" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));    
        setup();     
}

void do_look( object who )
{
        object me = this_object();
        send_user( who, "%c%c%w%s", ':', 3, 9312,
        	sprintf("%s：\n    看到周国的那些骑宠没？都是从我这租出去的，你想租吗？这租金对您来说，不过是九牛拔一毛，不过你得记得，你坐上这骑宠后，就不能出周国，不然我咋知道你将我心爱的骑宠拐去哪了，如果你出了周国，我会马上将他召唤回来的！\n"
                ESC "我要租借\ntalk %x# welcome.1\n"
                ESC "免费试乘\ntalk %x# welcome.2\n"
                ESC "关闭\nCLOSE\n", me->get_name(), getoid(me), getoid(me) ) );
}

void do_welcome( string arg )
{
        object who, me;
        string result;
        int flag, id, iTime, iDay;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);     
	iDay = mxTime[TIME_YDAY];
        me = this_object();
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        id = getoid(me);
        switch(flag)
        {
        case 1:
        	result = me->get_name()+"：\n    自己挑个喜欢的吧！10000金可以让你骑5分钟，可别累坏了我的宝贝！\n";
        	result += sprintf(ESC"小乖\ntalk %x# welcome.11\n", id);
        	result += sprintf(ESC"叮当\ntalk %x# welcome.12\n", id);
        	result += sprintf(ESC"驼驼\ntalk %x# welcome.13\n", id);
        	result += sprintf(ESC"独角\ntalk %x# welcome.14\n", id);
        	result += sprintf(ESC"胖胖\ntalk %x# welcome.15\n", id);
        	result += sprintf(ESC"紫毛\ntalk %x# welcome.16\n", id);
        	result += sprintf(ESC"笨笨\ntalk %x# welcome.17\n", id);
                send_user( who, "%c%c%w%s", ':', 3, 9312, result );
                break;
	case 2:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:	
		if (get_effect(who, EFFECT_RIDE) )
		{
			result = me->get_name()+"：\n    你已经在试骑宠了。\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		} 	
		if (who->get_fam_name()=="")
		{
			result = me->get_name()+"：\n    使用骑宠必须拜入某个门派。\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		} 	
		if( get_effect(who, EFFECT_MAGIC_4243) || get_effect(who, EFFECT_MAGIC_CARD) || who->get_save("temp_act") || who->get("temp_act") )
		{
			result = me->get_name()+"：\n    变身状态下不能使用骑宠。\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		} 		
		if (who->get_save_2("fride.count")>=7)
		{
			result = me->get_name()+"：\n    你已经免费试乘过七次了。\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		}          
		if (who->get_save_2("fride.day")==iDay)
		{
			result = me->get_name()+"：\n    你今天已经免费试乘了。\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		} 
		if (flag==2)
		{
	        	result = me->get_name()+"：\n    自己挑个喜欢的吧！每天一次，每次最多30分钟，可别累坏了我的宝贝！\n";
	        	result += sprintf(ESC"小乖\ntalk %x# welcome.21\n", id);
	        	result += sprintf(ESC"叮当\ntalk %x# welcome.22\n", id);
	        	result += sprintf(ESC"驼驼\ntalk %x# welcome.23\n", id);
	        	result += sprintf(ESC"独角\ntalk %x# welcome.24\n", id);
	        	result += sprintf(ESC"胖胖\ntalk %x# welcome.25\n", id);
	        	result += sprintf(ESC"紫毛\ntalk %x# welcome.26\n", id);
	        	result += sprintf(ESC"笨笨\ntalk %x# welcome.27\n", id);
	                send_user( who, "%c%c%w%s", ':', 3, 9312, result );
	                return;			
		}		
		who->add_save_2("fride.count", 1);
		who->set_save_2("fride.day", iDay);
		who->set_ride(flag-20);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
		set_effect(who, EFFECT_RIDE, 1800);
		break;		     
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		if (who->get_cash()<10000)
		{
			result = me->get_name()+"：\n    您身上的金钱不够支付本次租金\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		}       
		if (who->get_ride()>0)
		{
			result = me->get_name()+"：\n    你已经有骑宠了。\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		} 
		if (get_effect(who, EFFECT_RIDE) )
		{
			result = me->get_name()+"：\n    你已经在试骑宠了。\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		} 		
		if (who->get_fam_name()=="")
		{
			result = me->get_name()+"：\n    使用骑宠必须拜入某个门派。\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		} 	
		if( get_effect(who, EFFECT_MAGIC_4243) || get_effect(who, EFFECT_MAGIC_CARD) || who->get_save("temp_act") || who->get("temp_act") )
		{
			result = me->get_name()+"：\n    变身状态下不能使用骑宠。\n";
			send_user( who, "%c%c%w%s", ':', 3, 9312, result );
			return;
		} 		
		who->add_cash(-10000);
		who->log_money("试骑宠", -10000);		        
		"/sys/sys/count"->add_use("试骑宠", 10000);
		who->set_ride(flag-10);
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
		set_effect(who, EFFECT_RIDE, 300);
		break;
        }
}

void into_effect(object who)
{
	who->set_ride(0);
	who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
}