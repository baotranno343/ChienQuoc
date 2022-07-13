#include <npc.h>
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

// 函数：命令处理
int main( object me, string arg )
{
	object who, item;
        int i, size, a1, a2, a3, a4, p;
        if( is_player(me) ) 
        {
                notify( "Ngươi không đủ quyền hạn" );
		return ;
        }
        if( arg && !( who = find_any_char(arg) ) )
        {
                notify( "Không tìm thấy người này" );
		return ;
        }
		else if ( arg==0 )
		{
			return 1;
		}
        if(USER_INVENTORY_D->get_free_count(who) < 1 )
		{
				notify( "Hành trang đối phương không đủ 1 chỗ trống" );
		return ;
		}
		item = new("item/01/0203");	
		p = item->move2(who,-1);
		item->add_to_user(p);
			
	tell_user(me, sprintf("%s (%d) đã nhận được Hộp Xổ Số", who->get_name(), who->get_number()));
	tell_user(who, "Bạn đã nhận được Hộp Xổ Số");
        return ;
}
