#include <item.h>
#include <effect.h>
#include <skill.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

inherit "/inh/equip/equip";

#define ADD_DAMAGE      500

int get_item_value() {return 20 ;}
int get_item_value_2() {return 20 ;}
int get_item_color() { return 1; }

// 函数：叠加上限
int get_max_combined() { return 30; }

// 函数：成品编号
int get_fin_type() { return 1613; }

// 函数：可对目标使用的物品
int get_item_type_2() { return ITEM_TYPE_2_USABLE2; }

// 函数：构造处理
void create()
{
        set_name( "Công Thành Tạc Đạn" );
        set_picid_1(4186); 
        set_picid_2(4186); 
        set_value(1000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return  "Gây sát thương 500 điểm cho toàn bộ địch thủ trong phạm vi 3x3 ô.";
}

// 函数：使用效果
int get_use_effect( object me, object who ) { return __FILE__ ->get_use_effect_callout(me, who); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object who )
{
        int damage;
        object user, owner, *char;      
        int z, x, y, i;  
        if (get_effect(me, EFFECT_USE_JIGUAN))
        {
                send_user( me, "%c%s", '!', sprintf("Thời gian đóng băng của vật phẩm còn %d giây", get_effect(me, EFFECT_USE_JIGUAN)) );
                return 0;
        }
        if (!who) return 0;
        z = get_z(who), x = get_x(who), y = get_y(who);
        damage = ADD_DAMAGE;
	if (who->is_nianshou())
	{
                send_user( me, "%c%s", '!', "你的伎俩对年兽是不起作用的。");
		damage =0;
	}
        send_user( me, "%c%c%c%w", 0x30, get_item_type_2(), 0, 15 );    // 更新使用间隔
        set_effect(me, EFFECT_USE_JIGUAN, 15);        
        char = get_range_object(z, x, y, 3, USER_TYPE) + get_range_object(z, x, y, 3, CHAR_TYPE) - ({ me });
        for (i=0;i<sizeof(char);i++) if (who= char[i])
        {        
	        if( !CHAR_FIGHT_D->attack_action(me, who, 1000, 10) ) continue;
	        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 42422, 1, OVER_BODY, PF_ONCE );
	        if( who->is_npc() )    // 抄自 /sys/user/fight
	        {
	                if( who->get_enemy_4() == me )
	                        who->set_attack_time( time() );    // 同一个人：更新持续时间
	                else if( gone_time( who->get_attack_time() ) > 12 )
	                {
	                        who->set_enemy_4(me);
	                        who->set_attack_time( time() );    // 不同的人：更新持续敌手
	                }
	//              if( !who->get_max_damage() ) who->init_enemy_damage(me, 0);    // 记录最强伤害(NPC)
	                if( damage >= who->get_max_damage() ) who->init_enemy_damage(me, damage);    // 记录最强伤害(NPC)
	        }
	
	        if (who->is_user()) user = who;
	        else user = who->get_owner();
		if (user) send_user( user, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage, get_d(who), 0, HIT_BLADE, 1 );
		send_user( me, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage, get_d(who), 0, HIT_BLADE, 1 );        
	        CHAR_DIE_D->is_enemy_die(me, who, damage);
	}
        return 1;
}

