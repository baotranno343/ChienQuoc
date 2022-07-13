
// 单体远程技能  TIPS:[PF_CAST]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0417
#define THIS_PERFORM    04170
#define PF_START       "04170"
#define PF_TIME        "04170#"
#define PF_NAME        "Thuận Thiên Pháp Chú Đao Vương"

#define SKILL_LEVEL     150
#define TIME_INTERVAL	1
#define SUB_MP          ( 0 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 5 )
#define ADD_TIME	( 10800 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 3600 )
#define ADD_RATE	( 75 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 150 * 90 )
// 函数：获取符法效果
// int get_cast_seal() { return 41100; }    // 符纸逆旋

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 150 cấp\n    Hy sinh Triệu hồi thú của bản thân để triệu hồi “Đao Vương” hỗ trợ chiến đấu. Mỗi lần tấn công Đao Vương có 100％ khả năng làm cho kẻ địch bị Choáng trong 10 giây. Đao Vương có thể duy trì xuất hiện trong 3 giờ。";
        cur_level = (level - SKILL_LEVEL)/150 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Hy sinh Triệu hồi thú của bản thân để triệu hồi “Đao Vương” hỗ trợ chiến đấu. Mỗi lần tấn công Đao Vương có %d％ khả năng làm cho kẻ địch bị Choáng trong 10 giây. Đao Vương có thể duy trì xuất hiện trong %d giây。\n " HIC"Cấp tiếp theo:\n "NOR "Võ công yêu cầu: " HIR "Cấp %d " NOR "\n    Tăng Đao Vương thêm 1000000 điểm Khí Huyết；\n    Tăng Đao Vương thêm 15000 điểm Ngoại Công；\n    Tăng Đao Vương thêm 15000 điểm Ngoại Kháng；\n    Tăng Đao Vương thêm 15000 điểm Nội Kháng；\n    Tăng Đao Vương thêm 4000 điểm Thân Thủ。\n    Mỗi lần tấn công Đao Vương có %d％ khả năng làm cho kẻ địch bị Choáng trong 10 giây. Đao Vương có thể duy trì xuất hiện trong %d giây。", 
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, ADD_RATE, ADD_TIME, cur_level*150+SKILL_LEVEL, ADD_RATE + 90,ADD_TIME + 3600 );
        return result;	        
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user, item;
        int z;
        int level, mp;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("04170")==0) return 1;
		
        if( me->get_perform(PF_START) == time() ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng “ %s ”cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

/*      if( !objectp( item = present("bùa giấy", me, 1, MAX_CARRY) ) )
        {
                printf( ECHO "您得有符纸才能使用“" PF_NAME "”。" );
                return 1;
        }       */

        who = me->get("soldier");
        if (!who) return 1;

        if( !who->is_zombie() || who->get_owner() != me )
        {
                printf( ECHO "只能对自己的召唤兽使用“" PF_NAME "”。" );
                return 1;
        }

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        me->set_enemy_2(who);    // 远程目标锁定

        me->to_front_xy(x, y);
        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
//      send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);
//      item->add_amount(-1);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 5);
         me->add_2("go_count.count2",5);
        me->set_cast_file(__FILE__);
        me->set_cast_arg( who->get_char_id() );
	send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, 0 );
        me->set_perform( PF_START, time() );
        return 1;
}

// 函数：法术处理
int cast_done( object me )
{
        object who;
        string arg;
        int z, x, y, p, x0, y0;
        int level, cp, hp;
        object npc;        

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;

        if( !objectp( who = find_char(arg) ) ) return 1;

        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 41411, 1, OVER_BODY, PF_ONCE );

	send_user( get_scene_object_2(who, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(who), get_y(who), 4176, 1, OVER_BODY, PF_ONCE );
	send_user(me, "%c%c%d", 0x2c, 0, getoid(who));
	who->remove_from_scene(FALL_ACT);
	destruct(who);	
	npc = new (sprintf("/npc/std/%d", 4138));
	if (!npc) return 2;
	level = me->get_skill(THIS_SKILL);
	npc->set_level(level);
	npc->set_name( sprintf( "Đao Vương ( %s )", me->get_name() ) );
	npc->set_max_hp(100000+(level-40)/150*50000);
	npc->set_ap(10000+(level-40)/150*5000);
	npc->set_dp(7000+(level-40)/150*7000);
	npc->set_pp(7000+(level-40)/150*7000);
	npc->set_sp(2000+(level-40)/150*200);
	npc->set_hp(npc->get_max_hp());
	npc->set_mp(npc->get_max_mp());
	me->set("soldier", npc);
	npc->upgrade_level(1);
        npc->set_owner(me);
        npc->set_level_0(level);    
        npc->set_city_name( me->get_city_name() ); 
        npc->set_manager( me->get_manager() );
        npc->set_org_name( me->get_org_name() );	
        z = get_z(me); x0 = get_x(me); y0 = get_y(me);
        p = get_valid_xy(z, x0 + random(3) - 1, y0 + random(3) - 1, IS_CHAR_BLOCK) ;
        x = p / 1000;  y = p % 1000;
        npc->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0) );                
        send_user( get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(npc), 
                41331, 1, OVER_BODY, 41332, 1, UNDER_FOOT, PF_ONCE );
        npc->set_life(ADD_TIME);
        npc->Action_Mode(1);
        send_user(me, "%c%c%d%s", 0x2c, 1, getoid(npc), npc->get_name() );
        send_user(me, "%c%c%d%w%w%w", 0x2c, 2, getoid(npc), 1, 2, 3 );
        send_user(me, "%c%c%d%c", 0x2c, 3, getoid(npc), 50 );
        send_user(me, "%c%c%d%c", 0x2c, 4, getoid(npc), 50 );
        send_user(me, "%c%c%d%c", 0x2c, 5, getoid(npc), 2 );
        send_user(me, "%c%c%d%c", 0x2c, 6, getoid(npc), 2 );
        send_user(me, "%c%c%d%w%w", 0x2c, 7, getoid(npc), get_x(npc), get_y(npc) );
        send_user(me, "%c%c%d%d", 0x2c, 8, getoid(npc), npc->get_char_picid() );
        CHAR_FIGHT_D->set_enmity1(me,30);
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        int interval;
        string name;
		if (me->get_save("04170")==0) return;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }
	name = sprintf(" %s (Cấp %d )", PF_NAME, (me->get_skill(THIS_SKILL)-SKILL_LEVEL)/20+1);
        interval = TIME_INTERVAL - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, name );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, name );
	send_user(me, "%c%w%w%c%c%c%c%c%c", 0x64, THIS_PERFORM, SUB_MP, 0, 1, MAGIC_ACT_BEGIN, 0, 5, 0);
}
