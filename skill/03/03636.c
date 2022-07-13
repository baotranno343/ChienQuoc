
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

#define THIS_SKILL      0363
#define THIS_PERFORM    03636
#define PF_START       "03636"
#define PF_NAME        "Tích Độc"

#define SKILL_LEVEL     3
#define TIME_INTERVAL   2
#define SUB_MP          20
#define ADD_EFFECT      ( 300 + (me->get_skill(THIS_SKILL) - SKILL_LEVEL)/10 * 30 ) 

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return sprintf(HIR " %s \n Võ công yêu cầu: Cấp 3\n Vật phẩm tiêu hao: Thuốc Độc\n Tẩm thuốc độc vào vũ khí của đồng đội, khiến cho mỗi lần tấn công đều có 40%% khả năng làm cho kẻ địch bị Trúng Độc.", PF_NAME);
        cur_level = (level - SKILL_LEVEL)/10 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Vật phẩm yêu cầu : Thuốc Độc \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n Tẩm thuốc độc vào vũ khí của đồng đội, khiến cho mỗi lần tấn công đều có 40%% khả năng làm cho kẻ địch bị Trúng Độc.\n", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL );     	
        return result;
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        object item;
        string file, name;
        int z, poison, act, pf;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( gone_time( me->get_perform(PF_START) ) < TIME_INTERVAL ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

        if( !objectp( item = me->get_equip(HAND_TYPE) ) || !item->is_poison() ) 
        {
                printf( ECHO "Sử dụng \" %s \"phải có Độc Dược.",PF_NAME );
                return 1;
        }
	name = item->get_name();
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
        	return 1;
        }
        if (who!=me)
        {
        	if (who->is_npc() || !me->get_leader() || (me->get_leader()!=who->get_leader()) )
        	{
	                printf( ECHO "\"" PF_NAME "\" chỉ có thể sử dụng cho đồng đội" );
	                return 1;        		
        	}
        }
	if ("/sys/user/attack"->can_use_help(me, who)==0)
	{				
		printf( ECHO "Đối với đối phương không thể sử dụng " PF_NAME );
		return 1;				
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

        poison = item->get_poison();
        file = get_file_name(item);

        me->add_mp(-mp);
        item->add_amount(-1);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->add_2("go_count.count2",9);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d,%s,%d,%s", who->get_char_id(), level, file, poison, name ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        object who, item;
        string arg, file, name;
        int z, x, y;
        int level, rate, poison;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%s,%d,%s,%d,%s", arg, level, file, poison, name) != 5 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 3636, 1, OVER_BODY, PF_ONCE );

	item = who->get_equip(WEAPON_TYPE);
	if (item)
	{
		item->set_poison(poison);
		item->set("poison_time", time() + ADD_EFFECT);
		send_user( who, "%c%d%c", 0x31, getoid(item), 0 );
		if (who!=me)
		{
			write_user( me, ECHO "Bạn đem %s tẩm độc ở vũ khí của %s", name, who->get_name() );
			write_user( who, ECHO "%s đem %s tẩm độc ở vũ khí của bạn", me->get_name(), name );
		}
		else
			write_user( me, ECHO "Bạn đem %s tẩm độc ở vũ khí chính mình", name );
	}
        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_CHAR; }

// 函数:能否使用特技
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
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 1, 10, 6, 60, 9, 0);
}
