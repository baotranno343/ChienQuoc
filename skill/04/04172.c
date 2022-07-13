
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0417
#define THIS_PERFORM    04172
#define PF_START       "04172"
#define PF_NAME        "Lưu Huyết Thuật"

#define SKILL_LEVEL     5
#define TIME_INTERVAL	2
#define SUB_MP          ( 20 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 5 * 10 )
#define ADD_HP          ( 10 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 5 * 10 )

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数：获取符法效果
// int get_cast_seal() { return 41100; }    // 符纸逆旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 5 cấp\n    Liên tục trong 8 giây hồi phục Khí Huyết của Triệu hồi thú, mỗi 2 giây hồi phục 10 điểm Khí Huyết.";
        cur_level = (level - SKILL_LEVEL)/5 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Liên tục trong 8 giây hồi phục Khí Huyết của Triệu hồi thú, mỗi 2 giây hồi phục %d điểm Khí Huyết.\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Liên tục trong 8 giây,mỗi 2 giây hồi phục %d điểm Khí Huyết.", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, 2, ADD_HP, cur_level*5+SKILL_LEVEL, ADD_HP + 10 );
        return result;	
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user, item;
        int z;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( me->get_perform(PF_START) == time() ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

/*      if( !objectp( item = present("bùa giấy", me, 1, MAX_CARRY) ) )
        {
                printf( ECHO "您得有符纸才能使用\"" PF_NAME "\"." );
                return 1;
        }       */

        who = me->get("soldier");
        if (!who) return 1;

        if( !who->is_zombie() || who->get_owner() != me )
        {
                printf( ECHO "Chỉ đối với thú của mình mới có thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }
        if( !inside_screen_2(me, who) ) return 1;

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(get_x(who), get_y(who));
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
//      send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);
//      item->add_amount(-1);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
        me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( sprintf( "%s,%d,%d", who->get_char_id(), level, me->get_cp() ) );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object who;
        string arg;
        int z, x, y;
        int level, cp, hp;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( sscanf(arg, "%d,%d,%d", z, x, y) == 3 )
        {
                send_user( get_scene_object(z, x, y, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x, y, 41411, 1, OVER_BODY, PF_ONCE );

                return 1;    // 打到空地
        }
        if( sscanf(arg, "%s,%d,%d", arg, level, cp) != 3 ) return 1;
        if( !objectp( who = find_char(arg) ) ) return 1;

        hp = ADD_HP;    // 小心准备 me, cp

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 41721, 1, OVER_BODY, 41722, 1, OVER_BODY, PF_ONCE );

//      if( !who->can_be_fighted(me) || !me->can_fight(who) ) return 2;    // 执行成功

        if (!who->no_recover() && !get_effect_3(who, EFFECT_USER_BURN))
        {      
        	set_effect_2(who, EFFECT_CON_RECOVER, 4, 2);
        	who->set("05115", hp);         	
        }
        CHAR_FIGHT_D->set_enmity2(me,who,50+hp);
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
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 10, MAGIC_ACT_BEGIN, 0, 5, 0);
}
