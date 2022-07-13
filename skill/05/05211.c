
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define BASIC_SKILL     0501
#define THIS_SKILL      0521
#define THIS_PERFORM    05211
#define PF_START       "05211"
#define PF_NAME        "施毒"

#define SKILL_LEVEL     33
#define TIME_INTERVAL   2
#define SUB_MP          40
#define ADD_EFFECT      me->get_pf_value_2(THIS_SKILL, SKILL_LEVEL_SQUARE, poison, 100)    // 警告：me, poison 得准备好
#define SUB_EFFECT_AP   me->get_pf_value_2(THIS_SKILL, SKILL_LEVEL_SQUARE, 80, 30)    // 警告：me 得准备好

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数：获取软筋散(5215)减少攻击力
int get_sub_ap( object me ) 
{
        return SUB_EFFECT_AP;    // 小心准备 me
}

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        return sprintf( "［" PF_NAME "］对目标直接下毒，每次消耗 1 份毒药。消耗法力：%d，再次使用需间隔 %d 秒，%s%d 级可用\n基础技能要求：中医药理\n",
                SUB_MP, TIME_INTERVAL, level < SKILL_LEVEL ? HIR : "", SKILL_LEVEL );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object item;
        string file;
        int z, poison, act, pf;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( !objectp( item = me->get_equip(HAND_TYPE) ) || !item->is_poison() ) 
        {
                printf( ECHO "Sử dụng “ %s ”phải có Thạch Tín.",PF_NAME );
                return 1;
        }

        if( who )
        {
                if( !inside_screen_2(me, who) ) return 1;

                x = get_x(who);  y = get_y(who);
        }
        else if( objectp( who = me->get_enemy_2() ) && inside_screen_2(me, who) )
        {
                x = get_x(who);  y = get_y(who);
        }
        else
        {
                z = get_z(me);

                if( !inside_screen( get_x(me), get_y(me), x, y ) ) return 1;
                if( !objectp( who = get_xy_object(z, x, y, CHAR_TYPE) ) && !objectp( who = get_xy_object(z, x, y, USER_TYPE) ) ) 
                {
                        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                        me->set_time( "pf", time() );

	                pf = 60;    // 抄自 /sys/user/fight

                	if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
                	{
		                pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	                }

                        me->to_front_xy(x, y);
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), act, pf, get_d(me), 0 );
//                      send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

                        me->add_mp(-mp);
                        item->add_amount(-1);

                        set_heart_state(me, MAGIC_STAT);
                        set_heart_count_2(me, 9);
                        me->set_cast_file(__FILE__);
                        me->set_cast_arg( sprintf( "%d,%d,%d", z, x, y ) );

                        return 1;
                }
        }

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        pf = 60;    // 抄自 /sys/user/fight

        if( !( act = pf / 10 ) )    // pf: [动作序号][光影序号]
        {
	        pf = 0;  act = 1 + random(3);    // 无指定动作序号，随机
	}

        me->to_front_xy(x, y);
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), act, pf, get_d(me), getoid(who) );
//      send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        poison = item->get_poison();
        file = get_file_name(item);

        me->add_mp(-mp);
        item->add_amount(-1);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d,%s,%d", who->get_char_id(), level, file, poison ) );

        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object who;
        string arg, file;
        int z, x, y;
        int level, rate, poison;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 52111, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d,%s,%d", arg, level, file, poison) != 4 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 52111, 1, OVER_BODY, PF_ONCE );

        if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 1;

        rate = 50 * level / range_value( who->get_level(), 1, MAX_NUMBER ) + me->get_lucky() - who->get_lucky();
        if( get_effect(me, EFFECT_CHAR_BLIND) ) rate /= 2;    // 失明(命中减半)
        rate -= who->get_anti_poison();    // 毒免疫("X@%")(四类毒药)

        if(     poison
        &&     !get_effect(who, EFFECT_CHAR_POISON)
        &&     !get_effect(who, EFFECT_CHAR_9140)    // 辟毒散
        &&      random(100) < range_value(rate, 0, 95) )
        {
                poison = ADD_EFFECT;    // 小心准备 me, poison
                poison += poison * ( me->get_poison_rate() - who->get_lost_poison() ) / 100;
                file->get_poison_effect( me, who, poison / 10 );
        }
        else    file->get_poison_effect(me, who, 0);

        CHAR_DIE_D->is_enemy_die(me, who, 0);

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;

        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, PF_NAME );
}
