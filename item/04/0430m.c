#include <ansi.h>
#include <effect.h>
#include <skill.h>

inherit ITEM;
inherit USABLE;

// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

// 函数：构造处理
void create()
{
        set_name("智慧巧克力");
        set_picid_1(0057);
        set_picid_2(0057);
        set_unit("块");
        set_value(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return ("寓意：天生才子\n使用后法术防御增加30%，持续60分钟\n"HIR"使用者需为男性");
}

// 函数：使用效果
int get_use_effect( object me ) {return __FILE__ ->get_use_effect_callout(me,this_object());}

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me , object item )
{
	if(me->get_gender()!=1)
	{
		send_user(me,"%c%s",';',"对不起，您不能使用该道具。");
		return 0;
	}
	write_user(me,ECHO"您得到"+item->get_user_id()+"的真情祝福，法术防御增加30％。");
	send_user( me, "%c%w%w%c", 0x81, 0430, 3600, EFFECT_GOOD );
        set_effect(me, EFFECT_ITEM_9165, 3600);
	me->set_save( "9165#", 30 );
        USER_ENERGY_D->count_pp(me);
        return 1;
}

void effect_done(object me)
{
        send_user( me, "%c%w%w%c", 0x81, 0430, 0, EFFECT_GOOD );
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        return "一小时内增加法术防御力30％。\n";
}