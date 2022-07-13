
// 飞行技能  TIPS:[PF_FLY]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <map.h>

#define BASIC_SKILL_1   0401
#define BASIC_SKILL_2   0411
#define BASIC_SKILL_3   0421
#define THIS_SKILL      0408
#define THIS_PERFORM    04081
#define PF_START       "04081"
#define PF_NAME        "定标"

#define SKILL_LEVEL     151
#define SUB_MP          15

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        return sprintf( "［" PF_NAME "］在当前站立位置设定标记，通过穿越时空可快速到达此位置。消耗法力：%d，%s%d 级可用\n基础技能要求：道家学说\n",
                SUB_MP, level < SKILL_LEVEL ? HIR : "", SKILL_LEVEL );
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object map, item;
        string result, fly;
        int p, z, i, size;
        int level, mp;

        if( !me->get_skill(BASIC_SKILL_1) && !me->get_skill(BASIC_SKILL_2) && !me->get_skill(BASIC_SKILL_3) )
        {
                printf( ECHO "使用“" PF_NAME "”得先学会道家学说。" );
                return 1;
        }
        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( me->get_perform(PF_START) == time() ) return 1;

        if( MAP_D->is_inside_city( get_z(me), get_x(me), get_y(me) ) )
        {
                printf( ECHO "城内不能使用“" PF_NAME "”。" );
                return 1;
        }
        if( objectp( map = get_map_object( get_z(me) ) ) )
        {
                switch( map->get_map_type() )
                {
        case CAVE_MAP : printf( ECHO "这里不能使用“" PF_NAME "”。" );
                        return 1;
      case BATTLE_MAP : printf( ECHO "战场不能使用“" PF_NAME "”。" );
                        return 1;
                }
        }
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

        size = level / 20 + 1;

        if( sscanf(arg, "%d", p) )
        {
                if( !me->get_fly( sprintf( "%d", p ) ) && me->sizeof_fly_dbase() >= size )
                {
                        printf( ECHO "您最多能定 %d 个时空导标。", size );
                        return 1;
                }
                
                send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                me->set_time( "pf", time() );

                send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

                me->add_mp(-mp);
//              item->add_amount(-1);

                set_heart_state(me, MAGIC_STAT);
                set_heart_count_2(me, 9);
                me->set_cast_file(__FILE__);
                me->set_cast_arg( sprintf( "%d", p ) );
        }
        else
        {
                result = sprintf( "您想把这里设成哪个时空导标？(最多 %d 个)\n", size );
                for( i = 0; i < MAX_POSITION; i ++ )
                {
                        fly = me->get_fly( sprintf( "%d", i + 1 ) );
                        if( stringp(fly) && sscanf(fly, "%d,%d,%d", z, x, y) == 3 ) 
                        {
                                if( objectp( map = get_map_object(z) ) )
                                        fly = sprintf("%s(%d,%d)\npf 4081.%d\n", map->get_name(), x, y, i + 1);
                                else    fly = sprintf("(无导标)\npf 4081.%d\n", i + 1);
                        }
                        else    fly = sprintf("(无导标)\npf 4081.%d\n", i + 1);
                        result = sprintf( "%s" ESC "%s", result, fly );
                }
                send_user(me, "%c%s", ':', result);
        }

        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object map;
        string arg, name;
        int z, x, y, p;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        p = to_int(arg);

        if( me->is_die() ) return 1;

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me), 
                40811, 1, OVER_BODY, 40812, 1, OVER_BODY, PF_ONCE );

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        me->set_fly( sprintf( "%d", p ), sprintf("%d,%d,%d", z, x, y) );

        if( objectp( map = get_map_object(z) ) )
                name = map->get_name();
        else    name = "无名地图";

        send_user( me, "%c%s", '!', sprintf("您在" HIY " %s(%d,%d) " NOR "设下标记。", name, x, y) );

        // main( me, 0, 0, 0, "" );

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
