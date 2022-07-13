
// 自用技能  TIPS:[PF_SELF]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0418
#define THIS_PERFORM    04183
#define PF_START       "04183"
#define PF_NAME        "Thiên Lý Thần Nhãn"

#define SKILL_LEVEL     30
#define TIME_INTERVAL   2
#define SUB_MP          30
#define ADD_LOCATE	( 40 - ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 5 * 2 )


// 函数：获取符法效果
int get_cast_seal() { return 9103; }    // 符纸逆旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 30 cấp\n    Thần thông nhìn thấu 3 cõi, có thể kiểm tra tọa độ của mục tiêu nhiệm vụ. Giá trị lệch tọa độ là 35.";
        cur_level = (level - SKILL_LEVEL)/5 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Thần thông nhìn thấu 3 cõi, có thể kiểm tra tọa độ của mục tiêu nhiệm vụ. Giá trị lệch tọa độ là %d.\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: " HIR "Cấp %d " NOR"\n    Giá trị lệch tọa độ là %d.",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_LOCATE, cur_level*5+SKILL_LEVEL, ADD_LOCATE - 2 );
	return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user, npc, item, *team;
        string id;
        int level, mp;

/*      if(    !stringp( id = me->get_task("robber") ) 
        ||   !( npc = find_char(id) ) || !npc->is_robber() )    // 30 分钟
        {
                printf( ECHO "Bạn chưa nhận nhiệm vụ" );
                return 1;
        }       */

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( !objectp( item = present("Bùa Giấy", me, 1, MAX_CARRY*4) ) )
        {
                printf( ECHO "Phải có Bùa Giấy mới có thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
        send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);
        item->add_amount(-1);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2",9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%d", level ) );

        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object map, npc, *monster, *team;
        string id, name, result, arg;
        int z, x, y, p, flag;
        int level, i, size;

        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        flag = 0;
	team = me->get_team();
	if (sizeof(team)==0) team = ({ me });
        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        level = to_int(arg);

        if(     stringp( id = me->get_task("robber") ) 
        &&    ( npc = find_char(id) ) && npc->is_robber() )    // 30 分钟
        {
                z = get_z(npc);
                x = get_x(npc);
                y = get_y(npc);
                map = get_map_object( get_z(npc) );
                name = map ? map->get_name() : "Bản đồ vô danh";
                level = ADD_LOCATE / 2;
                if( level < 1 ) level = 1;

                for( i = 0; i < 100; i ++ )
                {
                        x = get_x(npc) + random(level * 2) - level;  y = get_y(npc) + random(level * 2) - level;
                        if( p = get_valid_xy(z, x, y, IS_CHAR_BLOCK) )
                        {
                                x = p / 1000;  y = p % 1000;  break;
                        }
                }
                
                tell_user( team, "Bạn dùng Thiên Lý Thần Nhãn nhìn thấy %s ở %s(%d,%d).", npc->get_name(), name, x, y );    // write_user
                flag = 1;
        }
        else if( map = get_map_object( get_z(me) ) )
        {
                if( arrayp( monster = map->get("monster") ) ) monster -= ({ 0 });

                if( arrayp(monster) && ( size = sizeof(monster) ) > 0 )
                {
                        level /= 10;
                        result = "";

                        if( level >= size )
                        {
                                for( i = 0; i < size; i ++ )
                                {
                                        name = monster[i]->get_name();
                                        x = abs( get_x( monster[i] ) + random(20) - 10 );
                                        y = abs( get_y( monster[i] ) + random(20) - 10 );
                                        if( i == 0 ) 
                                                result += sprintf(   "%s(%d,%d)", name, x, y );
                                        else    result += sprintf( "、%s(%d,%d)", name, x, y );
                                }
                        }
                        else
                        {
/*                              for( i = level; i < size; i ++ )    // 这个办法比较笨
                                {
                                        monster -= ({ monster[ random( sizeof(monster) ) ] });
                                }
                                for( i = 0, size = sizeof(monster); i < size; i ++ )
                                {
                                        name = monster[i]->get_name();
                                        x = abs( get_x( monster[i] ) + random(20) - 10 );
                                        y = abs( get_y( monster[i] ) + random(20) - 10 );
                                        if( i == 0 ) 
                                                result += sprintf(   "%s(%d,%d)", name, x, y );
                                        else    result += sprintf( "、%s(%d,%d)", name, x, y );
                                }       */

                                for( i = 0; i < level; i ++ )
                                {
                                        p = random(size);
                                        name = monster[p]->get_name();
                                        x = abs( get_x( monster[p] ) + random(20) - 10 );
                                        y = abs( get_y( monster[p] ) + random(20) - 10 );
                                        if( i == 0 ) 
                                                result += sprintf(   "%s(%d,%d)", name, x, y );
                                        else    result += sprintf( "、%s(%d,%d)", name, x, y );
                                }
                        }

                        tell_user( team, "Bạn dùng Thiên Lý Thần Nhãn nhìn thấy： %s.", result );    // write_user
                        flag = 1;
                }
//                else    tell_user( me, "Bạn dùng Thiên Lý Thần Nhãn không nhìn thấy gì" );    // write_user
        }
        if (npc=me->get("target"))
        {
        	if ( npc->get("user")==me->get_number() )
        	{
	                map = get_map_object( get_z(npc) );
	                x = get_x(npc); y = get_y(npc);
	                name = map ? map->get_name() : "Bản đồ vô danh";
	                tell_user( team, "Bạn dùng Thiên Lý Thần Nhãn nhìn thấy %s ở %s(%d,%d).", npc->get_name(), name, x, y ); 
	                flag = 1;
        	}
        }
        if (monster=me->get("targets"))
        {
        	monster -= ({ 0 });
        	me->set("targets", monster);
        	size = sizeof(monster);
        	for (i=0;i<size;i++)
        		if ( objectp(monster[i]) && monster[i]->get("user")==me->get_number() )
        		{        			
		                map = get_map_object( get_z(monster[i]) );
		                x = get_x(monster[i]); y = get_y(monster[i]);
		                name = map ? map->get_name() : "Bản đồ vô danh";
		                tell_user( team, "Bạn dùng Thiên Lý Thần Nhãn nhìn thấy %s ở %s(%d,%d).", monster[i]->get_name(), name, x, y ); 
		                flag = 1;
        		}
        } 
	id = me->get_save_2("mastertask.target");
	if ( stringp(id) )
	{

		npc = find_any_char(id);
		if ( objectp(npc) && npc->get("user") == me->get_number() )
		{
			map = get_map_object( get_z(npc) );
	                x = get_x(npc); y = get_y(npc);
	                name = map ? map->get_name() : "Bản đồ vô danh";
	                tell_user( team, "Bạn dùng Thiên Lý Thần Nhãn nhìn thấy %s ở %s(%d,%d).", npc->get_name(), name, x, y ); 
	                flag = 1;			
		}
	}         
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 41831, 1, OVER_BODY, PF_ONCE );
	if (flag==0) tell_user( me, "Bạn dùng Thiên Lý Thần Nhãn không nhìn thấy gì" ); 
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
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/5+1);
        interval = 2 - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 2, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 2, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 9, "Bùa Giấy");
}
