
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
		if ( who->get_save("no_hurt") < 1 ) {
			who->set_save("no_hurt",1);
			tell_user(me, sprintf("%s (%d) đã thiết lập Bất Tử", who->get_name(), who->get_number()));
			tell_user(who, "Bạn đã thiết lập Bất Tử");
		}	
		else {
			who->set_save("no_hurt",0);
			tell_user(me, sprintf("%s (%d) đã huỷ bỏ Bất Tử", who->get_name(), who->get_number()));
			tell_user(who, "Bạn đã huỷ bỏ Bất Tử");
		}	
	
        return 1;
}
