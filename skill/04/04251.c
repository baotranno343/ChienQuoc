
// 自用持续技能  TIPS:[PF_SELF_LOOP]

#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

#define THIS_SKILL      0425
#define THIS_PERFORM    04251
#define PF_START       "04251"
#define PF_TIME        "04251#"
#define PF_NAME        "Vận Chuyển Càn Khôn"

#define SKILL_LEVEL     150
#define TIME_INTERVAL   0
#define SUB_MP          50

int SKILL_LEVEL_SQUARE = SKILL_LEVEL * (SKILL_LEVEL - 1);

// 函数:获取符法效果
// int get_cast_seal() { return 42100; }    // 符纸顺旋

// 函数:获取描述
string get_desc( object me )
{
        int level = me->get_skill(THIS_SKILL);
        return sprintf( HIY"［" PF_NAME "］\nTiêu hao pháp lực: %d \nTái sử dụng sau: %d giây \nVõ công yêu cầu: cấp %s%d \nDùng nội lực hùng hậu hộ thể bản thân tránh khỏi những sát chiêu của đối phương.\n",
                SUB_MP, TIME_INTERVAL, level < SKILL_LEVEL ? HIR : "", SKILL_LEVEL );
}

// 函数:获取描述(持续)
string get_loop_desc( object me )
{
        if( me->get_perform(PF_START) )
                return sprintf( PF_NAME ":\n　　Chuyển hoá %d%% sát thương thành tiêu hao pháp lực.\n", me->get("pf.change%") );
        else    return sprintf( PF_NAME ":\n　　Chuyển hoá %d%% sát thương thành tiêu hao pháp lực.\n", me->get("pf.change%") );
}

// 函数:命令处理
int main( object me, object who, int x, int y, string arg )
{
        object *user, item;
        int level, mp, interval;

        if( ( level = me->get_skill(THIS_SKILL) ) < SKILL_LEVEL ) return 1;
		if (me->get_save("04251")==0) return 1;

        interval = me->get_perform(PF_TIME) + TIME_INTERVAL;

        if( gone_time( me->get_perform(PF_START) ) < interval ) return 1;

        if( me->get_mp() < ( mp = SUB_MP ) )    // 小心准备 level
        {
                printf( ECHO "Sử dụng \" %s \"cần %d điểm Pháp Lực.", PF_NAME, mp );
                return 1;
        }

/*      if( !objectp( item = present("bùa giấy", me, 1, MAX_CARRY) ) )
        {
                printf( ECHO "您得有符纸才能使用\"" PF_NAME "\"." );
                return 1;
        }       */

        send_user( me, "%c%w%c%w", 0x50, 0, 0xff, 2 );    // 所有出招２秒后能使用
        me->set_time( "pf", time() );

        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
//      send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        me->add_mp(-mp);
//      item->add_amount(-1);

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
//      me->set_cast_arg( sprintf( "%d", level ) );

        return 1;
}

// 函数:法术处理
int cast_done( object me )
{
        object *user;
        int level, interval;

        level = me->get_skill(THIS_SKILL);
        interval = 120;
    //    interval = 20 + level * 15 / 10 + random(level * 15 / 10);

        me->set_perform( PF_START, time() );
        me->set_perform( PF_TIME, interval );
        send_user( me, "%c%w%c%w", 0x50, THIS_PERFORM, 0xff, interval );

        user = get_scene_object_2(me, USER_TYPE);
        set_effect(me, EFFECT_CHAR_CHANGE, interval);
        send_user( me, "%c%w%w%c", 0x81, 4251, get_effect_3(me, EFFECT_CHAR_CHANGE), EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 4251, 1, EFFECT_GOOD );
        send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 42511, 1, OVER_BODY, PF_ONCE );

    //    me->set("pf.change%", 20 + level / 3);
        me->set("pf.change%", 70);
        me->set_change_hurt( me->get("pf.change%") );    // 没放入 USER_ENERGY_D

        // 效果见 energy_d.c

        return 2;    // 执行成功
}

// 函数:命令处理
int perform_action_npc( object me, object who )
{
        object *user;

        user = get_scene_object_2(me, USER_TYPE);
        send_user( user, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_BEGIN );
//      send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), get_cast_seal(), 2, UNDER_FOOT, PF_LOOP );

        set_heart_state(me, MAGIC_STAT);
        set_heart_count_2(me, 9);
        me->set_cast_file(__FILE__);
//      me->set_cast_arg( sprintf( "%d", level ) );

        return 1;
}

// 函数:法术处理
int cast_done_npc( object me )
{
        object *user;
        int level, interval;

        level = me->get_skill(THIS_SKILL);
        interval = 20 + level * 15 / 10 + random(level * 15 / 10);

        me->set_perform( PF_START, time() );
        me->set_perform( PF_TIME, interval );

        user = get_scene_object_2(me, USER_TYPE);
        set_effect(me, EFFECT_CHAR_CHANGE, interval);
        send_user( me, "%c%w%w%c", 0x81, 4251, get_effect_3(me, EFFECT_CHAR_CHANGE), EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 4251, 1, EFFECT_GOOD );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 42511, 1, OVER_BODY, PF_ONCE );

        me->set_change_hurt(20 + level / 3);    // 没放入 USER_ENERGY_D

        // 效果见 energy_d.c

        return 2;    // 执行成功
}

// 函数:获取特技类型
int get_perform_type() { return ON_ME; }

// 函数:能否使用特技
void can_perform( object me )
{
        int interval;
		if (me->get_save("04251")==0) return;
        if( me->get_skill(THIS_SKILL) < SKILL_LEVEL ) 
        {
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, 0, 1, 0, PF_NAME );
                return;
        }

        interval = me->get_perform(PF_TIME) - gone_time( me->get_perform(PF_START) );
        if( interval < 0 )
                send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, 0, PF_NAME );
        else    send_user( me, "%c%w%c%w%w%s", 0x50, THIS_PERFORM, get_perform_type(), TIME_INTERVAL, interval, PF_NAME );
}
