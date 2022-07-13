
// 飞行技能  TIPS:[PF_FLY]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <map.h>

#define THIS_SKILL      0418
#define THIS_PERFORM    04181
#define PF_START       "04181"
#define PF_NAME        "Định Tiêu"

#define SKILL_LEVEL     16
#define SUB_MP          15
#define TIME_INTERVAL 	2
#define MAX_COUNT	( 1 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 10 )

// 函数：获取符法效果
// int get_cast_seal() { return 41100; }    // 符纸逆旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 16 cấp\n    Thiết lập 1 định vị. Sau đó sử dụng pháp thuật Xuyên Không Hành sẽ có thể lập tức đến vị trí này. Hiện tại chỉ có thể thiết lập 1 định vị.";
        cur_level = (level - SKILL_LEVEL)/10 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Thiết lập 1 định vị. Sau đó sử dụng pháp thuật Xuyên Không Hành sẽ có thể lập tức đến vị trí này. Hiện tại chỉ có thể thiết lập %d định vị.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Có thể thiết đặt %d định vị.",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, MAX_COUNT, cur_level*10+SKILL_LEVEL, MAX_COUNT + 1 );
	return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user, map, item;
        string result, fly;
        int p, z, i, size;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( me->get_perform(PF_START) == time() ) return 1;

        if( MAP_D->is_inside_city( get_z(me), get_x(me), get_y(me) ) )
        {
                printf( ECHO "Trong thành không thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }
		if ( get_z(me)==704 )
		{
				notify("Trong Nhà Ngục không thể sử dụng");
                return 1;	
		}
		if ( objectp( item = present("Cờ Hiệu Vô Song Thành", me, 1, MAX_CARRY*4) ) )
		{
				notify("Mang theo Cờ Hiệu không thể sử dụng");
                return 1;
		}
        if( objectp( map = get_map_object( get_z(me) ) ) )
        {
                switch( map->get_map_type() )
                {
        case CAVE_MAP : printf( ECHO "Nơi này không thể sử dụng \"" PF_NAME "\"." );
                        return 1;
      case BATTLE_MAP : printf( ECHO "Chiến Trường không thể sử dụng \"" PF_NAME "\"." );
                        return 1;
                }
        }
        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

/*      if( !objectp( item = present("Bùa Giấy", me, 1, MAX_CARRY) ) )
        {
                printf( ECHO "Phải có Bùa Giấy mới có thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }       */

        size = MAX_COUNT;

        if( sscanf(arg, "%d", p) )
        {
                if( !me->get_fly( sprintf( "%d", p ) ) && me->sizeof_fly_dbase() >= size )
                {
                        printf( ECHO "Bạn có thể định tiêu nhiều nhất là %d chỗ", size );
                        return 1;
                }
                
                send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
                me->set_time( "pf", time() );

                user = get_scene_object_2(me, USER_TYPE);
                send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
//              send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

                me->add_mp(-mp);
//              item->add_amount(-1);

                set_heart_state(me, MAGIC_STAT);
                set_heart_count_2(me, 5);
                me->add_2("go_count.count2",5);
                me->set_cast_file(__FILE__);
                me->set_cast_arg( sprintf( "%d", p ) );
        }
        else
        {
                result = sprintf( "Bạn muốn định tiêu ở chỗ này? (Nhiều nhất %d địa điểm)\n", size );
                for( i = 0; i < MAX_POSITION; i ++ )
                {
                        fly = me->get_fly( sprintf( "%d", i + 1 ) );
                        if( stringp(fly) && sscanf(fly, "%d,%d,%d", z, x, y) == 3 ) 
                        {
                                if( objectp( map = get_map_object(z) ) )
                                        fly = sprintf("%s(%d,%d)\npf 4181.%d\n", map->get_name(), x, y, i + 1);
                                else    fly = sprintf("(Định tiêu)\npf 4181.%d\n", i + 1);
                        }
                        else    fly = sprintf("(Định tiêu)\npf 4181.%d\n", i + 1);
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
                41811, 1, OVER_BODY, 41812, 1, UNDER_FOOT, PF_ONCE );

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        me->set_fly( sprintf( "%d", p ), sprintf("%d,%d,%d", z, x, y) );

        if( objectp( map = get_map_object(z) ) )
                name = map->get_name();
        else    name = "Bản đồ vô danh";

        send_user( me, "%c%s", '!', sprintf("Bạn ở " HIY " %s(%d,%d) " NOR " thiết lập dấu hiệu", name, x, y) );

        // main( me, 0, 0, 0, "" );

        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;

        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/10+1);
        interval = 2 - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 2, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 2, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 5, 0);
}
