
#include <ansi.h>
#include <npc.h>
#include <skill.h>
#include <effect.h>

inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 40; }

// 函数：法宝识别
int get_talisman_type() { return 8; }

// 函数：构造处理
void create()
{
        set_name( "极乐木鱼" );
        set_picid_1(9571);
        set_picid_2(9571);
        set_unit( "只" );

        set_level(1);
        set_value(5000);
        set_max_lasting(699);

        setup();
}

// 函数：获取描述
string get_desc() 
{ 
        return "使等待救援的死亡玩家直接复活，相当于“自动复活”";
}

// 函数：可使用法宝
int is_usable_2() { return 1; }

// 函数：使用法宝效果
int get_use_effect_2( object me, object who, string arg ) { return __DIR__ "9571" ->get_use_effect_2_callout( me, who, this_object(), arg ); }

// 函数：使用法宝效果(在线更新)
int get_use_effect_2_callout( object me, object who, object item, string arg )
{
        if( !objectp(who) ) return 1;

        if( !who->is_user() ) return 1;    // 必须是玩家

        if( who->get_login_flag() < 3 ) return 1;    // 没有准备就绪

        if( !who->is_die() ) return 1;

        if( me == who ) return 1;    // 不能是自己

        item->add_lasting(-1);    // 使用减少耐久

        me->set_char_type( PK_TYPE );    // 主动ＰＫ状态
        set_effect(me, EFFECT_USER_PK, 120);

        if( random(100) < item->get_active_rate() )    // 成功率
        {
                set_effect(who, EFFECT_USER_DIE, 1);

                write_user( me, ECHO "您对%s进行" HIY "亡魂超度" ECHO "，%s得到了解脱。", who->get_name(), who->get_name() );
                write_user( who, ECHO "%s对您进行" HIY "亡魂超度" ECHO "，您得到了解脱。", me->get_name() );
        }
        else    write_user( me, ECHO "您对%s使用" HIY "亡魂超度" ECHO "失败了。", who->get_name() );

        return 1;
}
