
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

// 函数：命令处理
int main( object me, string arg )
{
        string result, arg2;
	int type, i, size;
	object *inv, item;

        if( is_player(me) )
        {
                notify( "Ngươi không đủ quyền hạn" );
		return 1;
        }


        if( arg ==0  )
        {
        	result = sprintf("Hãy lựa chọn :\n");
        	if (me->get_save("no_hurt"))
        		result += ESC "Hủy bỏ vô địch\ngmset battu 0\n";
        	else
        		result += ESC "Vô địch\ngmset battu 1\n";
		if (me->get_save("no_visible"))
			result += ESC "Hủy bỏ ẩn thân\ngmset tanghinh 0\n";        	
		else
			result += ESC "Ẩn thân\ngmset tanghinh 1\n"; 
		result += ESC "Xoá đồ hành trang\ngmset xoado\n"; 
		result += ESC "Gấp đôi thuộc tính\ngmset gapdoi\n"; 
		result += ESC "Khí Huyết khôi phục bình thường\ngmset binhthuong\n"; 
	//	result += ESC "Hồi máu\nrecover\n"; 
		result += ESC "Hủy bỏ\n"; 
		send_user( me, "%c%s", ':', result);
                return 1;
        }
        if (arg=="xoado")
        {
        	inv = all_inventory(me, 1, MAX_CARRY*4);
        	for( i = 0, size = sizeof(inv); i < size; i ++ ) if( objectp( item = inv[i] ) )
        	{
        		item->remove_from_user();
        		destruct(item);
        	}
        	notify( "Đã xoá sạch hành trang" );
        	return 1;
        }
        if (arg=="gapdoi")
        {
        	me->set_max_hp(me->get_max_hp()*2);
        	me->set_hp(me->get_max_hp());
        	return 1;
        }
        if (arg=="binhthuong")
        {
        	"/sys/user/energy"->count_max_hp(me);
        	return 1;
        }        
        if (sscanf(arg, "%s %d", arg2, type)!=2) return 1;
        switch(arg2)
        {
        case "battu":
        	me->set_save("no_hurt", type);
        	if (type==1) notify( "Đã thiết lập Bất Tử" );
        	else notify( "Đã huỷ bỏ Bất Tử" );
        	break;
        case "tanghinh":
        	if (type==1)
        	{
	        	set_effect_2( me, EFFECT_CHAR_INVISIBLE, 3000, 10 );    // 每十秒减血
        		CHAR_CHAR_D->init_loop_perform(me);
	        	send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9000, 1, UNDER_FOOT, PF_LOOP );    // 半透明
			set_invisible(me, 1);
			me->set_save("no_visible", 1);
			send_user( me, "%c%c%c", 0x3d, 241, 2 );
		}
		else
		{
			set_effect_2( me, EFFECT_CHAR_INVISIBLE, 0, 0);
			me->set_save("no_visible", 0);
			set_invisible(me, 0);
			CHAR_CHAR_D->init_loop_perform(me);
			send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9000, 1, UNDER_FOOT, PF_STOP );			
		}
		break;
        }
        return 1;
}
