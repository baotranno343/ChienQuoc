
// 飞行技能  TIPS:[PF_FLY]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <map.h>
#include <city.h>

#define BASIC_SKILL_1   0401
#define BASIC_SKILL_2   0411
#define BASIC_SKILL_3   0421
#define THIS_SKILL      0409
#define THIS_PERFORM    04091
#define PF_START       "04091"
#define PF_NAME        "神游"

#define SKILL_LEVEL     151
#define SKILL_LEVEL_2   151
#define SUB_MP          16

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        return sprintf( "［" PF_NAME "］快速移动到其他人身边，对方法力越低成功率越高。消耗法力：%d，%s%d 级可用\n基础技能要求：道家学说\n",
                SUB_MP, level < SKILL_LEVEL ? HIR : "", SKILL_LEVEL );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )    // 同步更改“灵犀环”
{
        object map, item;
        string name;
        int level, mp;

        if( to_int(arg) ) me->set_save( "fly", to_int(arg) );    // 记录前次飞的人

        if( !me->get_skill(BASIC_SKILL_1) && !me->get_skill(BASIC_SKILL_2) && !me->get_skill(BASIC_SKILL_3) )
        {
                printf( ECHO "使用“" PF_NAME "”得先学会道家学说。" );
                return 1;
        }
        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( me->get_perform(PF_START) == time() ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

/*      if( !objectp( item = present("bùa giấy", me, 1, MAX_CARRY) ) )
        {
                printf( ECHO "您得有符纸才能使用“" PF_NAME "”。" );
                return 1;
        }       */

        if( present("钱票", me, 1, MAX_CARRY) )
        {
                printf( ECHO "带着钱票不能使用“" PF_NAME "”。" );
                return 1;
        }
        if( present("贵重物品", me, 1, MAX_CARRY) )
        {
                printf( ECHO "带着贵重物品不能使用“" PF_NAME "”。" );
                return 1;
        }
        if( objectp( who = me->get_quest("escort.robber#") ) && who->is_escort_robber() )    // 寻找蒙面人
        {
                printf( ECHO "蒙面人出现，您的行动受到影响。" );
                return 1;
        }

        if( !arg || arg == "" )
        {
                send_user( me, "%c%c%d%d%s", '?', 3, 0, me->get_save("fly"), "您想移动到哪位玩家身边？请输入对方的数字ＩＤ：\n"
                        ESC "pf 4091.%s\n" );
                return 1;
        }
        else if( arg == "0" )
        {
                notify( "没有这个人物。" );
		return 1;
        }
        else
        {
                if( !objectp( who = find_player(arg) ) )
                {
                        notify( "您找不到这位玩家。" );
                        return 1;
                }
                if (!is_player(who) && is_player(me))
                {
                        notify( "您无法飞到对方身边。" );
                        return 1;                	
                }
                if( who->get_no_fly() )
                {
                        printf( ECHO "对方设置了禁飞开关。" );
                        return 1;
                }
                if( MAP_D->is_inside_city( get_z(who), get_x(who), get_y(who) ) )
                {
                        printf( ECHO "对方在城内，不能使用“" PF_NAME "”。" );
                        return 1;
                }
                if( objectp( map = get_map_object( get_z(who) ) ) )
                {
                        switch( map->get_map_type() )
                        {
                case CAVE_MAP : printf( ECHO "对方在地下，不能使用“" PF_NAME "”。" );
                                return 1;
              case BATTLE_MAP : printf( ECHO "对方在战场，不能使用“" PF_NAME "”。" );
                                return 1;
                        }
                }
                if( who->get_login_flag() < 3 )
                {
                        printf( ECHO "对方还没有准备就绪呢。" );
                        return 1;
                }
                if( who->is_die() )
                {
                        printf( ECHO "对方已死亡，不能使用“" PF_NAME "”。" );
                        return 1;
                }
        }

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        me->add_mp(-mp);
//      item->add_amount(-1);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d,%d,%d,%d", who->get_char_id(), level, get_z(who), get_x(who), get_y(who) ) );

        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object who;
        string arg;
        int z, x, y, x0, y0, p;
        int level;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        if( !stringp( arg = me->get_cast_arg() ) || sscanf(arg, "%s,%d,%d,%d,%d", arg, level, z, x, y) != 5 ) return 1;
//      if( !objectp( who = find_char(arg) ) ) return 1;

        if( me->is_die() ) return 1;

        x0 = x;  y0 = y;

        if( arg[<1] == '#' )    // 本帮总管(NPC)
        {
                if(   ( p = 18 - level / 10 ) > 0
                &&    ( p = get_valid_xy( z, x0 + random(p) - p / 2, y0 + random(p) - p / 2, IS_CHAR_BLOCK) ) )
                {
                        x = p / 1000;  y = p % 1000;
                        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 0, 1, OVER_BODY, PF_ONCE );
                        me->add_to_scene( z, x, y, get_d(me), 40911, 0, 40911, 0 );    // get_front_xy(x, y, x0, y0)
                }
                else    return 1;

                return 2;    // 执行成功
        }

        if( !objectp( who = find_char(arg) ) ) return 1;

        if(     random(100) < 5 + level * 75 / 100 * me->get_mp() / ( who->get_mp() + who->get_max_mp() )
        &&    ( p = 18 - level / 10 ) > 0
        &&    ( p = get_valid_xy( z, x0 + random(p) - p / 2, y0 + random(p) - p / 2, IS_CHAR_BLOCK) ) )
        {
                x = p / 1000;  y = p % 1000;
                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 0, 1, OVER_BODY, PF_ONCE );

                me->set_login_flag(2);    // 跳转保护
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 4);

                me->add_to_scene( z, x, y, get_d(me), 40911, 0, 40911, 0 );    // get_front_xy(x, y, x0, y0)
        }
        else    return 1;

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        if( !me->get_skill(BASIC_SKILL_1) && !me->get_skill(BASIC_SKILL_2) && !me->get_skill(BASIC_SKILL_3) )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
        else if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
}
