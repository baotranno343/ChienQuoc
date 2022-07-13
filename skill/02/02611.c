
// 暗器技能  TIPS:[PF_THROWING]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <equip.h>
#include <effect.h>

#define THIS_SKILL      0261
#define THIS_PERFORM    02611
#define PF_START       "02611"
#define PF_NAME        "Đầu Xạ"

// 函数：获取描述
string get_desc( object me )
{
        return "[ " PF_NAME " ] 单体远程攻击，再次使用需间隔 1 秒\n";
}
int main( object me, object who, int x, int y, string arg )
{
	"/cmd/std/kill"->main(me, who->get_char_id() );
}

// 函数：命令处理
int perform_action( object me, object who )
{
        int z, act, pf, x, y;
        string arg;

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 0;

                x = get_x(who);  y = get_y(who);
        }
        else 
        {
        	return 0;
        }

//        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
//        me->set_time( "pf", time() );
        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 1;
        me->set_enemy_2(who);    // 远程目标锁定
        me->set_enemy(who);

        pf = 60;    // 抄自 /sys/user/fight

        if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
        {
	        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	}
	if( get_effect(me, EFFECT_CHAR_INVISIBLE) ) set_effect_2(me, EFFECT_CHAR_INVISIBLE, 1, 1 ); 
        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), act, 0, get_d(me), getoid(who) );

	me->set_perform_file(__FILE__);
        me->set_perform_enable_time(time());
        return 2;
}

int perform_done( object me, object who )
{
        string arg;
        object item;
        int z, x, y, level, color, magic, ap, oldap;
//        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );    
        me->set_perform( PF_START, time() );    
//      send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 26121, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功
        if( objectp( item = me->get_equip(WEAPON_TYPE) ))
        {
        	if (item->get_weapon_type()!=THROWING)
        		ap = item->get("ap");
        }
        else ap = 1;        
        if (me->get_fam_name()=="Đường Môn") ap = me->get_ap();
        
//	set_heart_count_2(me, 10);
/*
        item = me->get_equip(WEAPON_TYPE);
        if (item)
        {
        	color = item->get_item_color();
        	level = item->get_level();
        	if (color>=2)
        	{
        		if (color==2)
        		{
        			if (level<80) magic = 23155;
        			else magic = 23135;
        		}
        		else magic = 23115;
        		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), magic, 1, OVER_BODY, PF_ONCE );
        	}
        }
*/        
	oldap = me->get_ap();
	me->set_ap(ap);
        CHAR_FIGHT_D->throwing_done(me, who, HIT_NONE);	
        me->set_ap(oldap);
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
