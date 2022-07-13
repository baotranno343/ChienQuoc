
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main( object me, string arg )
{
	object who,map;
        int i, size, a1, a2, a3, a4;
        if( is_player(me) ) 
        {
                notify( "Ngươi không đủ quyền hạn" );
		return 1;
        }
        if( arg && !( who = find_any_char(arg) ) )// find_any_object
        {
                notify( "Không tìm thấy người này" );
		return 1;
        }
		else if ( arg==0 )
		{
			return 1;
		}
		if ( who->is_die() )
		{
			write_user(me, ECHO"Đối phương đã chết rồi.");
			return 1;
		}
		map = get_map_object(get_z(who));
if ( map )
{	
	if ( who->is_user() )
	{	
			if ( map->get_no_fight() )
			{
		who->set_hp(0);
		who->set_die(6);
			}
			else if ( map->is_changping() )
			{
		who->set_hp(0);
		who->set_die(9);
			}
			else if ( get_z(who) < 885 || map->is_org_map() || map->is_copy_scene() || map->is_pvp() )
			{
		who->set_hp(0);	
		who->set_die(1);	
			}
			else if( map->get_client_id() == 885 || map->get_client_id() == 887 || map->get_client_id()==891 || map->is_wushuang() )
			{
		who->set_hp(0);	
		who->set_die(5);	
			}
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 25163, 1, OVER_BODY, PF_ONCE );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 25164, 1, OVER_BODY, PF_ONCE );
		write_user(me, sprintf(ECHO"Bạn đã tấn công %s (%d) !", who->get_name(), who->get_number()));
		//CHAT_D->rumor_channel( 0, CHAT+sprintf(HIM"%s (%d) đã bị thế lực đen tối dùng Ngũ Lôi Áp Đỉnh đánh chết !!", who->get_name(), who->get_number() ));
	}
	else
	{
		write_user(me, sprintf(ECHO"Bạn đã tấn công %s !", who->get_name()));
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 25163, 1, OVER_BODY, PF_ONCE );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 25164, 1, OVER_BODY, PF_ONCE );
		CHAR_DIE_D->is_enemy_die( me, who, who->get_hp() );		
	}
}
else
{
		if ( who->is_user() )
		{
		write_user(me, ECHO"Không thể sử dụng ở Bản đồ này !");
		}
		else {
		write_user(me, sprintf(ECHO"Bạn đã tấn công %s !", who->get_name()));
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 25163, 1, OVER_BODY, PF_ONCE );
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 25164, 1, OVER_BODY, PF_ONCE );
		CHAR_DIE_D->is_enemy_die( me, who, who->get_hp() );
		}
		//return 1;
}		
        return 1;
}
