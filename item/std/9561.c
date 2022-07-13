
#include <ansi.h>
#include <npc.h>
#include <skill.h>
#include <effect.h>

inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 60; }

// 函数：生效时间
int get_time_interval() { return 180; }

// 函数：法宝识别
int get_talisman_type() { return 7; }

// 函数：构造处理
void create()
{
        set_name( "撼天钟" );
        set_picid_1(9561);
        set_picid_2(9561);
        set_unit( "个" );

        set_level(1);
        set_value(5000);
        set_max_lasting(1099);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "压制对方法宝，使其在一段时间内失去效用";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：征状结束效果
void effect_suppress_done( object me )    // 顺势推舟(自用)
{
        object *user;

        user = get_scene_object_2(me, USER_TYPE);
        send_user( me, "%c%w%w%c", 0x81, 9561, 0, EFFECT_GOOD );
        send_user( user - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9561, 0, EFFECT_GOOD );
        send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(me), 9561, 1, OVER_BODY, PF_STOP );
}

// 函数：使用法宝效果
int get_use_effect_2( object me, object who, string arg ) { return __DIR__ "9561" ->get_use_effect_2_callout( me, who, this_object(), arg ); }

// 函数：使用法宝效果(在线更新)
int get_use_effect_2_callout( object me, object who, object item, string arg )
{
        object *user;

        if( !objectp(who) ) return 1;

        if( !who->is_user() ) return 1;    // 必须是玩家

        if( who->get_login_flag() < 3 ) return 1;    // 没有准备就绪

        if( who->is_die() || who->is_store_open() || who->get_no_fight() ) return 1;    // 死亡，摆摊，安全区

        if( me == who ) return 1;    // 不能是自己

        item->add_lasting(-1);    // 使用减少耐久

        me->set_char_type( PK_TYPE );    // 主动ＰＫ状态
        set_effect(me, EFFECT_USER_PK, 120);

        if( get_effect(who, EFFECT_CHAR_SUPPRESS) ) return 1;    // 已被压制

        if( random(100) < item->get_active_rate() )    // 成功率
        {
                user = get_scene_object_2(who, USER_TYPE);
                set_effect( who, EFFECT_CHAR_SUPPRESS, item->get_time_interval() );
                send_user( who, "%c%w%w%c", 0x81, 9561, get_effect_3(who, EFFECT_CHAR_SUPPRESS), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9561, 1, EFFECT_BAD );
                CHAR_CHAR_D->init_loop_perform(who);
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9569, 1, OVER_BODY, PF_ONCE );
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9561, 1, OVER_BODY, PF_LOOP );

                write_user( me, ECHO "%s的法宝被您用" HIY "威撼" ECHO "吓着了，不敢异动。", who->get_name() );
                write_user( who, ECHO "您的法宝被%s用" HIY "威撼" ECHO "吓着了，不敢异动。", me->get_name() );
        }
        else    write_user( me, ECHO "您对%s使用" HIY "威撼" ECHO "失败了。", who->get_name() );

        return 1;
}
