
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
		who->set_hp(who->get_max_hp());
		who->set_mp(who->get_max_mp());
		who->set_yuan(who->get_max_yuan());	
	tell_user(me, sprintf("%s (%d) đã hồi phục Khí Huyết và Pháp Lực", who->get_name(), who->get_number()));
//	tell_user(who, sprintf("%s (%d) đã thăng lên cấp 150", who->get_name(), who->get_number()));
	tell_user(who, "Bạn đã hồi phục toàn bộ Khí Huyết và Pháp Lực");
        return 1;
}
