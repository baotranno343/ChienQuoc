
#include <ansi.h>

// 函数：命令处理
int main( object me, string arg )
{
        object *char, who = me;
        int i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( arg && !( who = find_any_char(arg) ) ) 
        {
                notify( "您无法找到这个人。" );
		return 1;
        }

        who->stop_fight();

        char = get_range_object_2(who, 5, CHAR_TYPE) + get_range_object_2(who, 5, USER_TYPE) - ({ who });
        for( i = 0, size = sizeof(char); i < size; i ++ )
                if( char[i] && char[i]->get_enemy() == who ) char[i]->stop_fight();

        if( who == me )
        {
                tell_user( me, HIY "您强行中止了涉及您的战斗。" );
        }
        else
        {
                tell_user( me, HIY "您强行中止了涉及%s的战斗。", who->get_name() );
                write_user( who, HIY "%s强行中止了涉及您的战斗。", me->get_name() );
        }

        return 1;
}
