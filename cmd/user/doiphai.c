
#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main( object me, string arg )
{
	string result, arg2;
	int type, i, size, gioitinh, p;
	object *inv, item, item1;
	gioitinh = me->get_gender();
		
		if( !objectp( item1 = present("Thuốc Trùng Sinh", me, 1, MAX_CARRY*4) ) )
        {
                write_user(me, ECHO "Bạn không có Thuốc Trùng Sinh !");
                return 1;
        }	
		if(USER_INVENTORY_D->get_free_count(me) < 10 )
			{
				write_user(me, ECHO "Hành trang của bạn không đủ 10 chỗ trống!");
				return 1;
			}	
		if ( me->get_level() < 60 )
			{
				write_user(me, ECHO "Phải đạt cấp 60 trở lên mới có thể Trùng Sinh!");
				return 1;
			}
		if ( me->get_fam_name() == "" )
			{
				write_user(me, ECHO "Bạn vẫn còn là Vô Môn Phái, không thể Trùng Sinh!");
				return 1;
			}		
		if( arg ==0  )
        {		
		result = sprintf("Bạn đang sử dụng Thuốc Trùng Sinh, bạn xác nhận muốn sử dụng không ?\n");
		result += ESC "Tôi muốn sử dụng\ndoiphai trungsinh\n";
		result += ESC "Hủy bỏ\n"; 
		send_user( me, "%c%s", ':', result);
			return 1;	
        }	
        if (arg=="trungsinh")
        {
			if ( gioitinh == 1 )
	{
		if ( me->get_fam_name() == "Đào Hoa Nguyên" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0316);
		me->delete_skill(0211);
		me->delete_skill(0212);
		me->delete_skill(0319);
		me->delete_skill(0317);
			item = new("item/60/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/65/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Thục Sơn" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0329);
		me->delete_skill(0325);
		me->delete_skill(0231);
		me->delete_skill(0221);
		me->delete_skill(0222);
			item = new("item/60/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/65/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Cấm Vệ Quân" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0349);
		me->delete_skill(0242);
		me->delete_skill(0241);
		me->delete_skill(0348);
		me->delete_skill(0251);
			item = new("item/60/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/65/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Đường Môn" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0365);
		me->delete_skill(0364);
		me->delete_skill(0368);
		me->delete_skill(0261);
		me->delete_skill(0363);
			item = new("item/60/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/65/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Mao Sơn" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0414);
		me->delete_skill(0417);
		me->delete_skill(0271);
		me->delete_skill(0413);
		me->delete_skill(0418);
			item = new("item/60/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/65/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Côn Luân" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0421);
		me->delete_skill(0423);
		me->delete_skill(0424);
		me->delete_skill(0425);
		me->delete_skill(0422);
			item = new("item/60/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/65/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Vân Mộng Cốc" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0511);
		me->delete_skill(0531);
		me->delete_skill(0501);
		me->delete_skill(0281);
		me->delete_skill(0591);
			item = new("item/60/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/65/0050");
			item->set_hide(0);	
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}	
	}
			else
	{
		if ( me->get_fam_name() == "Đào Hoa Nguyên" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0316);
		me->delete_skill(0211);
		me->delete_skill(0212);
		me->delete_skill(0319);
		me->delete_skill(0317);
			item = new("item/61/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/66/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Thục Sơn" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0329);
		me->delete_skill(0325);
		me->delete_skill(0231);
		me->delete_skill(0221);
		me->delete_skill(0222);
			item = new("item/61/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/66/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Cấm Vệ Quân" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0349);
		me->delete_skill(0242);
		me->delete_skill(0241);
		me->delete_skill(0348);
		me->delete_skill(0251);
			item = new("item/61/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/66/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Đường Môn" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0365);
		me->delete_skill(0364);
		me->delete_skill(0368);
		me->delete_skill(0261);
		me->delete_skill(0363);
			item = new("item/61/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/66/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Mao Sơn" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0414);
		me->delete_skill(0417);
		me->delete_skill(0271);
		me->delete_skill(0413);
		me->delete_skill(0418);
			item = new("item/61/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/66/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Côn Luân" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0421);
		me->delete_skill(0423);
		me->delete_skill(0424);
		me->delete_skill(0425);
		me->delete_skill(0422);
			item = new("item/61/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/66/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
		else if ( me->get_fam_name() == "Vân Mộng Cốc" )
		{
			me->set_fam_name("");
			me->set_fam_master(0);
		me->delete_skill(0511);
		me->delete_skill(0531);
		me->delete_skill(0501);
		me->delete_skill(0281);
		me->delete_skill(0591);
			item = new("item/61/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/66/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/86/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/87/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/88/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
			item = new("item/73/0050");	
			item->set_hide(0);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move2(me,-1);
			item->add_to_user(p);
			me->use_equip(item);
		item = new("item/09/0908");
		me->restore_equip(item);
		"/sys/user/energy"->count_all_prop(me);
		send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                        	me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color() );	
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			item1->add_amount(-1);
			send_user(me,"%c%s",';',"Bạn đã sử dụng \"Thuốc Trùng Sinh\"");
		}
	}
			return 1;
		}
 
        return 1;
}