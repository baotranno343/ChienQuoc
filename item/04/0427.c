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
        set_name("怡情蓝玫瑰");
        set_picid_1(0050);
        set_picid_2(0050);
        set_unit("枝");
        set_value(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return ("花语：敦厚善良\n使用后物理防御增加30%，持续60分钟\n"HIR"使用者需为女性");
}

// 函数：使用效果
int get_use_effect( object me ) {return __FILE__ ->get_use_effect_callout(me,this_object());}

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me , object item )
{
	if(me->get_gender()==1)
	{
		send_user(me,"%c%s",';',"对不起，您不能使用该道具。");
		return 0;
	}
	write_user(me,ECHO"您得到"+item->get_user_id()+"的真情祝福，物理防御增加30％。");
	send_user( me, "%c%w%w%c", 0x81, 0426, 3600, EFFECT_GOOD );
	me->set_save("03291#", me->get_dp()*30/100);
        set_effect(me, EFFECT_USER_DP, 3600);
        USER_ENERGY_D->count_dp(me);
        return 1;
}

void effect_done(object me)
{
        send_user( me, "%c%w%w%c", 0x81, 0426, 0, EFFECT_GOOD );
}

// 函数：获取描述(持续)
string get_loop_desc( object me )
{
        return "一小时内增加物理防御力30％。\n";
}