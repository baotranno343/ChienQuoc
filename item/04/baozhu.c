#include <item.h>
#include <effect.h>
#include <skill.h>
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

inherit "/inh/equip/equip";
int is_baozhu() { return 1; }

// 函数：叠加上限
int get_max_combined() { return 5000; }

// 函数：成品编号
//int get_fin_type() { return 1606; }

// 函数：可对目标使用的物品
int get_item_type_2() { return ITEM_TYPE_2_USABLE2; }

// 函数：构造处理
void create()
{
        set_name( "Pháo" );
        set_picid_1(9984);
        set_picid_2(9984);
        set_value(20000);
        set_amount(1);
}

// 函数：获取描述
string get_desc() 
{ 
	string color = "";
	object me = this_player();
        return  "Là loại Pháo mà mỗi năm tết đến thường dùng để chúc mừng năm mới,\ncó thể dùng nó đuổi Niên Thú và kẻ ác, mỗi lần dùng có thể gây ra ít nhất 200 sát thương.";
}

void reset()
{
        if( gone_time( get_drop_time() ) > 3000 )    // 50分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }
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
                send_user( me, "%c%s", '!', sprintf("Thời gian tái sử dụng còn %d giây", get_effect(me, EFFECT_USE_JIGUAN)) );
                return 0;
        }
        if (!who) return 0;

        damage = 200+random(200);
        send_user( me, "%c%c%c%w", 0x30, get_item_type_2(), 0, 1 );    // 更新使用间隔
        set_effect(me, EFFECT_USE_JIGUAN, 1);
        z = get_z(who), x = get_x(who), y = get_y(who);
        char = get_range_object(z, x, y, 3, USER_TYPE) + get_range_object(z, x, y, 3, CHAR_TYPE) - ({ me });
        for (i=0;i<sizeof(char);i++) if (who= char[i])
        {        
	        if( !CHAR_FIGHT_D->attack_action(me, who, 1000, 10) ) continue;	        	        
	        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(who), 9600, 1, OVER_BODY, 9601, 1, OVER_BODY, 9602, 1, OVER_BODY, PF_ONCE );	        
	        if( who->is_npc() )    // 抄自 /sys/user/fight
	        {
	                if( who->get_enemy_4() == me )
	                        who->set_attack_time( time() );    // 同一个人：更新持续时间
	                else if( gone_time( who->get_attack_time() ) > 12 )
	                {
	                        who->set_enemy_4(me);
	                        who->set_attack_time( time() );    // 不同的人：更新持续敌手
	                }
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
