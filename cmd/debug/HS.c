
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main( object me, string arg )
{
	object who;
        int i, size, a1, a2, a3, a4;
        if( is_player(me) ) 
        {
                notify( "Ngươi không đủ quyền hạn" );
		return 1;
        }
        if( arg && !( who = find_any_char(arg) ) )
        {
                notify( "Không tìm thấy người này" );
		return 1;
        } 
		else if ( arg==0 )
		{
			return 1;
		}
		if( who->is_die() )
        {
                set_effect(who, EFFECT_USER_DIE, 0);
                who->set_die(0);
                who->set_hp( who->get_max_hp() );
                who->set_mp( who->get_max_mp() );
				who->set_yuan( who->get_max_yuan() );

                who->set_login_flag(2);  
                set_invisible(who, 1);
                set_effect(who, EFFECT_USER_LOGIN, 2);
				tell_user(me, sprintf("%s (%d) đã hồi sinh tại chỗ", who->get_name(), who->get_number()));
				tell_user(who, "Bạn đã hồi sinh tại chỗ");	
        }
        return 1;
}
