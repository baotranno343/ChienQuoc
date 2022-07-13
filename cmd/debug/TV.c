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

		if ( who->get_fam_name() == "" )
		{
		item = new("item/09/0908");
		who->restore_equip(item);
		}
		else if ( who->get_fam_name() == "Đào Hoa Nguyên" )
		{
		item = new("item/09/0901");
		item->set_item_level(1);
		who->restore_equip(item);
		"/sys/user/energy"->count_all_prop(who);
		}
		else if ( who->get_fam_name() == "Thục Sơn" )
		{
		item = new("item/09/0902");
		item->set_item_level(1);
		who->restore_equip(item);
		"/sys/user/energy"->count_all_prop(who);
		}
		else if ( who->get_fam_name() == "Cấm Vệ Quân" )
		{
		item = new("item/09/0903");
		item->set_item_level(1);
		who->restore_equip(item);
		"/sys/user/energy"->count_all_prop(who);
		}
		else if ( who->get_fam_name() == "Đường Môn" )
		{
		item = new("item/09/0904");
		item->set_item_level(1);
		who->restore_equip(item);
		"/sys/user/energy"->count_all_prop(who);
		}
		else if ( who->get_fam_name() == "Mao Sơn" )
		{
		item = new("item/09/0905");
		item->set_item_level(1);
		who->restore_equip(item);
		"/sys/user/energy"->count_all_prop(who);
		}
		else if ( who->get_fam_name() == "Côn Luân" )
		{
		item = new("item/09/0906");
		item->set_item_level(1);
		who->restore_equip(item);
		"/sys/user/energy"->count_all_prop(who);
		}
		else if ( who->get_fam_name() == "Vân Mộng Cốc" )
		{
		item = new("item/09/0907");
		item->set_item_level(1);
		who->restore_equip(item);
		"/sys/user/energy"->count_all_prop(who);
		}
			
	tell_user(me, sprintf("%s (%d) đã nhận được Tín Vật Môn Phái", who->get_name(), who->get_number()));
	tell_user(who, "Bạn đã nhận được Tín Vật Môn Phái");
        return 1;
}
