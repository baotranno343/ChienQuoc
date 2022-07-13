
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <action.h>

int get_action_mode() { return 0; }

inherit SLAVE;

int picid;

int get_char_picid() {return picid; }

int set_char_picid(int pic) {return picid = pic; }

int get_max_level0() {return 1;}

int is_jiguan() {return 1;}

// 函数：获取攻击对象
object get_enemy() { return 0; }
int get_char_type() {return 160;}

// 函数：获取气血比例(不显示血条，超过50)
int get_hp_cent() { return 60; }

// 函数：构造处理
void create()
{
        set_name("Cơ Quan Bảo Thú");
        set_char_picid(4131);
        set_action_mode(0);
	set_max_hp(0);
	set_hp(0);
	set_max_mp(0);
	set_mp(0);
        setup();
}

int can_fight( object who ) {return 0;}

int can_be_fighted( object who ) {return 0;}

// --------------------------------------------------------------- 远程调用 ----

// 函数：升级处理
void upgrade_level( int level ) { __FILE__ ->upgrade_level_callout( this_object(), level ); }

// 函数：升级处理(在线更新)
void upgrade_level_callout( object me, int level )
{
        me->set_char_type(SLAVE_TYPE_1);
        me->set_attack_speed(25);
        me->set_walk_speed(3);
        me->set_walk_step(2);
}
// 函数：从场景中移除
varargs void remove_from_scene( int rm_pf, int rm_pf_2 )
{
        object me, owner;
        ::remove_from_scene(rm_pf, rm_pf_2);
        me = this_object();
        if( owner = me->get_owner() ) 
        {
        	if(owner->get_2("jg_effect_buff") && me->get("jg_effect_buff")) {
        		send_user( owner, "%c%w%w%c", 0x81, 4033, 0, 1 );
        		owner->delete_2("jg_effect_buff");
        	}
        }
}
