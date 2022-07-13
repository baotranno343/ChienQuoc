#include <item.h>
#include <effect.h>
#include <skill.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

inherit "/inh/equip/equip";

#define SKILL_LEVEL     55

// 函数：叠加上限
int get_max_combined() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1618; }

// 函数：可对目标使用的物品
int get_item_type_2() { return ITEM_TYPE_2_USABLE2; }

// 函数：构造处理
void create()
{
        set_name( "Khốn Địch Tác" );
        set_picid_1(4194);
        set_picid_2(4194);
        set_value(1900);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        string color = "";
	object me = this_player();
	if (me->get_skill(660)<SKILL_LEVEL) color = HIR + sprintf("Yêu cầu Cơ quan cấp bậc： %d\n", SKILL_LEVEL);
	else color = sprintf("Yêu cầu Cơ quan cấp bậc： %d\n", SKILL_LEVEL);
        return  color + "Phóng ra cái võng khiến mục tiêu không thể di động \nNếu kĩ thuật ko cao có thể sẽ tự trói chính mình";
}

// 函数：使用效果
int get_use_effect( object me, object who ) { return __FILE__ ->get_use_effect_callout(me, who); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object who )
{
        int damage;
        object user, owner;      
        int rate;  
        int z, x, y, interval;
        if (get_effect(me, EFFECT_USE_JIGUAN))
        {
                send_user( me, "%c%s", '!', sprintf("道具冷冻时间还剩%d秒", get_effect(me, EFFECT_USE_JIGUAN)) );
                return 0;
        }
        if (me->get_skill(660)<SKILL_LEVEL)
        {
                send_user( me, "%c%s", '!', sprintf("你的机关等级不够%d，无法使用%s", SKILL_LEVEL, get_name()) );
                return 0;
        }
        if (!who) return 0;
        if( !CHAR_FIGHT_D->attack_action(me, who, 1000, 10) ) return 0;
        send_user( me, "%c%c%c%w", 0x30, get_item_type_2(), 0, 60 );    // 更新使用间隔
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 34821, 1, OVER_BODY, PF_ONCE );
        set_effect(me, EFFECT_USE_JIGUAN, 60);
	rate = 80 * (me->get_level()+10)/(who->get_level()+10);
	CHAR_FIGHT_D->attack_done(me, who, HIT_UNARMED, 100, 0, -100);
	if (random(100)<rate)
	{
                z = get_z(who);  x = get_x(who);  y = get_y(who);
                who->set_save( "pf.chan", sprintf( "%d:(%d,%d)", z, x, y ) );
		interval = 8;
                set_effect(who, EFFECT_CHAR_CHAN, interval);

                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%w%c%c%c", 0x4f, x, y, 
                        21151, interval, OVER_TILE, 21152, interval, OVER_TILE, PF_ONCE );
		
	}
        return 1;
}
