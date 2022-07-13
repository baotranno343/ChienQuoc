
// 召唤技能  TIPS:[PF_CALL]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0531
#define THIS_PERFORM    05312
#define PF_START       "05312"
#define PF_NAME        "Rải Đậu Thành Binh"

#define SKILL_LEVEL     15
#define TIME_INTERVAL	2
#define SUB_MP          ( 20 + ( me->get_skill(THIS_SKILL)-SKILL_LEVEL) / 10 * 20 )

#define INIT_HP         me->get_pf_value(THIS_SKILL, SKILL_LEVEL_SQUARE, 264, 4)    // 警告：me 得准备好
#define INIT_AP         me->get_pf_value(THIS_SKILL, SKILL_LEVEL_SQUARE, 89, 20)    // 警告：me 得准备好
#define INIT_DP         me->get_pf_value(THIS_SKILL, SKILL_LEVEL_SQUARE, 45, 30)    // 警告：me 得准备好
#define INIT_PP         me->get_pf_value(THIS_SKILL, SKILL_LEVEL_SQUARE, 71, 34)    // 警告：me 得准备好
#define INIT_SP         me->get_pf_value(THIS_SKILL, SKILL_LEVEL_SQUARE, 72, 34)    // 警告：me 得准备好

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

#define MAX_ZOMBIE      1

// 函数：获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        int cur_level;
        string result;
        if (level<SKILL_LEVEL)
        	return HIR + PF_NAME +"\n Võ công yêu cầu: 15 cấp\n Vật phẩm tiêu hao: Đậu Nành\n    Rắc đậu niệm chú để gọi 1 Đậu Binh ra trợ chiến. Đậu Binh sẽ tự thu hút quái vật tấn công";
        cur_level = (level - SKILL_LEVEL)/10 + 1;
        result = sprintf(HIC" %s (Cấp %d )\n " NOR "Võ công yêu cầu: Cấp %d \n Vật phẩm tiêu hao: Đậu Nành\n Pháp Lực tiêu hao: %d điểm\n Tái sử dụng sau: %d giây\n    Rắc đậu niệm chú để gọi 1 Đậu Binh ra trợ chiến. Đậu Binh sẽ tự thu hút quái vật tấn công\n " HIC"Cấp tiếp theo:\n "NOR"Võ công yêu cầu: " HIR "Cấp %d " NOR"\n    Tăng Đậu Binh thêm 500 điểm Khí Huyết；\n    Tăng Đậu Binh thêm 80 điểm Ngoại Công；\n    Tăng Đậu Binh thêm 100 điểm Ngoại Kháng；\n    Tăng Đậu Binh thêm 80 điểm Nội Kháng；\n    Tăng Đậu Binh thêm 30 điểm Thân Thủ.",
        	PF_NAME, cur_level, SKILL_LEVEL, SUB_MP, TIME_INTERVAL, cur_level*10+SKILL_LEVEL );
	return result;
}

// 函数：命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *zombie, item, item2;
        int level, mp, size;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;

        if( me->get_perform(PF_START) == time() ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 me
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

/*      if( !objectp( item = present("阵旗", me, 1, MAX_CARRY) ) )
        {
                printf( ECHO "您得有阵旗才能使用\"" PF_NAME "\"." );
                return 1;
        }       */
        if( !objectp( item2 = present("Đậu Nành", me, 1, MAX_CARRY*4) ) )
        {
                printf( ECHO "Phải có Đậu Nành mới có thể sử dụng \"" PF_NAME "\"." );
                return 1;
        }

        if (objectp( me->get("soldier")))
        {
                printf( ECHO "Bạn đã gọi Đậu Binh về hoặc Mê hồn quái vật" );
                return 1;
        }

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );

        me->add_mp(-mp);
//      item->add_amount(-1);
        item2->add_amount(-1);

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
        object npc;
        string arg;
        int z, x, y, x0, y0, p;
        int level, cp, pp, i, size;

        if( !stringp( arg = me->get_cast_arg() ) ) return 1;
        me->set_perform( PF_START, time() );
        level = to_int(arg);
        
        send_user(me, "%c%c%w%s", 0x5a, 0, 3, "Gọi Đậu Binh……");	                
        me->set_2("conjure.type", 4135);
        me->set_2("conjure.level", level);
        set_effect(me, EFFECT_CONJURE, 3);                

/*
        z = get_z(me);  x0 = get_x(me);  y0 = get_y(me);

        if( p = get_valid_xy(z, x0 + random(3) - 1, y0 + random(3) - 1, IS_CHAR_BLOCK) )
        {
                npc = new( "/npc/std/4135" );
                npc->set_name( sprintf( "豆兵(%s)", me->get_name() ) );
                npc->set_max_hp( INIT_HP );    // 小心准备 me
                npc->set_ap( INIT_AP );
                npc->set_dp( INIT_DP );
                npc->set_pp( INIT_PP );
                npc->set_sp( INIT_SP );
                npc->upgrade_level(1);
                cp = me->get_cp();
                pp = me->get_pp();
                npc->add_max_hp( (cp + pp) / 2 );
                npc->add_ap( cp * 3 / 100 );
                npc->add_dp( pp / 4 );

                npc->set_owner(me);
                npc->set_level_0(level);    // 布阵图
//              npc->set_action(1);

                npc->set_city_name( me->get_city_name() );    // 用于战场
                npc->set_manager( me->get_manager() );
                npc->set_org_name( me->get_org_name() );

                x = p / 1000;  y = p % 1000;
                npc->add_to_scene( z, x, y, get_front_xy(x, y, x0, y0) );
                send_user( get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(npc), 
                        59111, 1, OVER_BODY, 59112, 1, UNDER_FOOT, PF_ONCE );
                me->add("zombie", ({ npc }) );

                set_effect(npc, EFFECT_NPC_ZOMBIE_2, 10);

                NPC_SLAVE_D->find_enemy(npc);    // 寻找敌人
        }
*/
        return 2;    // 执行成功
}

// 函数：获取特技类型
int get_perform_type() { return ON_ME; }

// 函数：能否使用特技
void can_perform( object me )
{
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), 1, 0, PF_NAME );
	send_user(me, "%c%w%w%c%c%c%c%c%s", 0x64, THIS_PERFORM, SUB_MP, 0,1, MAGIC_ACT_BEGIN, 0, 9, "Đậu Nành");
}
