#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
#include <time.h>

int main(object me, string arg)
{

	int p, cap, exist, exist2, i, size, iTime, gt, gt2, mau, mau2, nhat, nhat1, nhat2, nhat3, nhat4, nhat5;
	string result, arg2, arg3, arg4, *line, *data, id, ben, ben1, ben2, ben3, ben4, ben5;
	object item, item1, who, *objs, target, *inv;
	mixed *mixTime;
	iTime = time();
	mixTime = localtime(iTime);
	if (!arg)
		return 1;
	if (arg == 0)
		return 1;
	if (sscanf(arg, "+ %s %s", arg2, arg3) == 2)
	{
		if (!objectp(who = find_player(arg2)))
			return 1;
		if (who != me)
			return 1;
		if (arg3 == "1")
		{
			gt = who->get_gender() == 1 ? 1 : 1001;
			if (me->get_hair() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Kiểu tóc này vẫn đang là kiểu tóc hiện tại của ngươi !\n" ESC "Trở về \ndoitoc2 999\n");
				return 1;
			}
			ben = "Vô Môn Phái";
			nhat = 100;
		}
		else if (arg3 == "2")
		{
			gt = who->get_gender() == 1 ? 2 : 1002;
			if (me->get_hair() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Kiểu tóc này vẫn đang là kiểu tóc hiện tại của ngươi !\n" ESC "Trở về \ndoitoc2 999\n");
				return 1;
			}
			ben = "Đào Hoa Nguyên";
			nhat = 200;
		}
		else if (arg3 == "3")
		{
			gt = who->get_gender() == 1 ? 3 : 1003;
			if (me->get_hair() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Kiểu tóc này vẫn đang là kiểu tóc hiện tại của ngươi !\n" ESC "Trở về \ndoitoc2 999\n");
				return 1;
			}
			ben = "Thục Sơn";
			nhat = 300;
		}
		else if (arg3 == "4")
		{
			gt = who->get_gender() == 1 ? 4 : 1004;
			if (me->get_hair() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Kiểu tóc này vẫn đang là kiểu tóc hiện tại của ngươi !\n" ESC "Trở về \ndoitoc2 999\n");
				return 1;
			}
			ben = "Cấm Vệ Quân";
			nhat = 400;
		}
		else if (arg3 == "5")
		{
			gt = who->get_gender() == 1 ? 5 : 1005;
			if (me->get_hair() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Kiểu tóc này vẫn đang là kiểu tóc hiện tại của ngươi !\n" ESC "Trở về \ndoitoc2 999\n");
				return 1;
			}
			ben = "Đường Môn";
			nhat = 500;
		}
		else if (arg3 == "6")
		{
			gt = who->get_gender() == 1 ? 6 : 1006;
			if (me->get_hair() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Kiểu tóc này vẫn đang là kiểu tóc hiện tại của ngươi !\n" ESC "Trở về \ndoitoc2 999\n");
				return 1;
			}
			ben = "Côn Luân";
			nhat = 600;
		}
		else if (arg3 == "7")
		{
			gt = who->get_gender() == 1 ? 7 : 1007;
			if (me->get_hair() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Kiểu tóc này vẫn đang là kiểu tóc hiện tại của ngươi !\n" ESC "Trở về \ndoitoc2 999\n");
				return 1;
			}
			ben = "Vân Mộng Cốc";
			nhat = 700;
		}
		else if (arg3 == "8")
		{
			gt = who->get_gender() == 1 ? 8 : 1008;
			if (me->get_hair() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Kiểu tóc này vẫn đang là kiểu tóc hiện tại của ngươi !\n" ESC "Trở về \ndoitoc2 999\n");
				return 1;
			}
			ben = "Mao Sơn";
			nhat = 800;
		}
		else
			return 1;

		send_user(me, "%c%c%s", 0x56, 0, sprintf("%s(%d)\n%s\n%s\n%s\n%s\n", who->get_name(), who->get_number(), who->get_city_name() == "" ? "－－" : who->get_city_name(), who->get_fam_name() == "" ? "－－" : who->get_fam_name(), who->get_org_name() == "" ? "－－" : who->get_org_name(), who->get_title()));
		send_user(me, "%c%c%d%w%w%w%w%w%w%w%w%w%w%s", 0x56, 0xfe,
				  who->get_armor_code(), who->get_armor_color_1(), gt,
				  who->get_hair_color(), who->get_back(), who->get_back_color(), who->get_back2(), who->get_back2_color(),
				  who->get_weapon_code_2(), who->get_weapon_color(), who->get_weapon_color_2(),
				  USER_RANK_D->get_rank(who));
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần :\n Ngươi muốn thay đổi kiểu tóc sang kiểu tóc của " + ben + " phải không ?\n" ESC "Xác nhận thay đổi kiểu tóc \ndoitoc2 %d\n" ESC "Trở về \ndoitoc2 999\n", nhat));
	}
	/*	else if( sscanf(arg, "- %s %s", arg2, arg3 ) == 2 ) 
		{
			if( !objectp( who = find_player(arg2) )	) return 1;
			if ( who!=me ) return 1;
			if ( arg3=="1" ) 
			{
			mau = 0x0981;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Xanh Lục"; nhat1 = 1000;	
			}
			else if ( arg3=="2" ) 
			{
			mau = 0x00c0c0c0;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Đỏ"; nhat1 = 2000;
			}
			else if ( arg3=="3" ) 
			{
			mau = 0x00800080;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Đen"; nhat1 = 3000;
			}
			else if ( arg3=="4" ) 
			{
			mau = 0x18cc;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Xanh Nhạt"; nhat1 = 4000;
			}
			else if ( arg3=="5" ) 
			{
			mau = 0x6006;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Hồng"; nhat1 = 5000;
			}
			else if ( arg3=="6" ) 
			{
			mau = 0xe6fefd;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Trắng"; nhat1 = 6000;
			}
			else if ( arg3=="7" ) 
			{
			mau = 0x00DDA0DD;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Tím"; nhat1 = 7000;
			}
			else if ( arg3=="8" ) 
			{
			mau = 0x6300;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Vàng"; nhat1 = 8000;
			}
			else if ( arg3=="9" ) 
			{
			mau = 0x0186;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Olive"; nhat1 = 9000;
			}
			else if ( arg3=="10" ) 
			{
			mau = 0x5140;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Cam"; nhat1 = 10000;
			}
			else if ( arg3=="11" ) 
			{
			mau = 0x00FFFFE0;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện đang sử dụng màu tóc này, xin chọn màu khác !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Hoàng Kim"; nhat1 = 11000;
			}
			else if ( arg3=="12" ) 
			{
			mau = 0;
				if ( me->get_hair_color() == mau )
				{
				send_user(me,"%c%c%w%s",':',3,9958,"Ảo Diện Thần :\n Ngươi hiện chưa có màu tóc, xin chọn màu tóc !\n"
				ESC"Trở về \ndoitoc2 998\n");
				return 1;
				}
			ben1 = "Vô Sắc"; nhat1 = 12000;
			}
			else return 1;

			send_user( me, "%c%c%s", 0x56, 0, sprintf( "%s(%d)\n%s\n%s\n%s\n%s\n",
			who->get_name(), who->get_number(),
			who->get_city_name() ==	"" ? "－－" : who->get_city_name(),
			who->get_fam_name() == "" ? "－－" : who->get_fam_name(),
			who->get_org_name() == "" ? "－－" : who->get_org_name(),
			who->get_title() ) );
			send_user( me, "%c%c%d%w%w%w%w%w%w%w%w%w%w%s", 0x56, 0xfe,
				who->get_armor_code(), who->get_armor_color_1(), me->get_hair(),
				mau, who->get_back(), who->get_back_color(), who->get_back2(), who->get_back2_color(),
				who->get_weapon_code_2(), who->get_weapon_color(), who->get_weapon_color_2(), 
				USER_RANK_D->get_rank(who) );	
			send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần :\n Ngươi muốn chọn màu tóc của mình là màu "+ben1+" không? \n"
			ESC"Xác nhận thay đổi màu tóc \ndoitoc2 %d\n"
			ESC"Trở về \ndoitoc2 998\n",nhat1));	
		}*/
	else if (sscanf(arg, "@ %s", arg3) == 1)
	{
		if (arg3 == "1")
		{
			gt = me->get_gender() == 1 ? 1 : 1001;
			if (me->get_photo() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Ngươi hiện đang sử dụng Khuôn mặt này, xin chọn Khuôn mặt khác !\n" ESC "Trở về \ndoitoc2 997\n");
				return 1;
			}
			me->set_save("doiphoto", 15);
			if (!me->get_save("old_photo"))
				me->set_save("old_photo", me->get_photo());
			me->set_photo(gt);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Khuôn mặt đã được hiển thị ở ảnh Avatar để ngươi xem trước. \nNgươi muốn chọn Khuôn mặt này làm Khuôn mặt chính thức không ? \n" ESC "Xác nhận thay đổi khuôn mặt \ndoitoc2 111\n" ESC "Trở về \ndoitoc2 996\n");
		}
		else if (arg3 == "2")
		{
			gt = me->get_gender() == 1 ? 2 : 1002;
			if (me->get_photo() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Ngươi hiện đang sử dụng Khuôn mặt này, xin chọn Khuôn mặt khác !\n" ESC "Trở về \ndoitoc2 997\n");
				return 1;
			}
			me->set_save("doiphoto", 15);
			if (!me->get_save("old_photo"))
				me->set_save("old_photo", me->get_photo());
			me->set_photo(gt);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Khuôn mặt đã được hiển thị ở ảnh Avatar để ngươi xem trước. \nNgươi muốn chọn Khuôn mặt này làm Khuôn mặt chính thức không ? \n" ESC "Xác nhận thay đổi khuôn mặt \ndoitoc2 222\n" ESC "Trở về \ndoitoc2 996\n");
		}
		else if (arg3 == "3")
		{
			gt = me->get_gender() == 1 ? 3 : 1003;
			if (me->get_photo() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Ngươi hiện đang sử dụng Khuôn mặt này, xin chọn Khuôn mặt khác !\n" ESC "Trở về \ndoitoc2 997\n");
				return 1;
			}
			me->set_save("doiphoto", 15);
			if (!me->get_save("old_photo"))
				me->set_save("old_photo", me->get_photo());
			me->set_photo(gt);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Khuôn mặt đã được hiển thị ở ảnh Avatar để ngươi xem trước. \nNgươi muốn chọn Khuôn mặt này làm Khuôn mặt chính thức không ? \n" ESC "Xác nhận thay đổi khuôn mặt \ndoitoc2 333\n" ESC "Trở về \ndoitoc2 996\n");
		}
		else if (arg3 == "4")
		{
			gt = me->get_gender() == 1 ? 4 : 1004;
			if (me->get_photo() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Ngươi hiện đang sử dụng Khuôn mặt này, xin chọn Khuôn mặt khác !\n" ESC "Trở về \ndoitoc2 997\n");
				return 1;
			}
			me->set_save("doiphoto", 15);
			if (!me->get_save("old_photo"))
				me->set_save("old_photo", me->get_photo());
			me->set_photo(gt);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Khuôn mặt đã được hiển thị ở ảnh Avatar để ngươi xem trước. \nNgươi muốn chọn Khuôn mặt này làm Khuôn mặt chính thức không ? \n" ESC "Xác nhận thay đổi khuôn mặt \ndoitoc2 444\n" ESC "Trở về \ndoitoc2 996\n");
		}
		else if (arg3 == "5")
		{
			gt = me->get_gender() == 1 ? 5 : 1005;
			if (me->get_photo() == gt)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Ngươi hiện đang sử dụng Khuôn mặt này, xin chọn Khuôn mặt khác !\n" ESC "Trở về \ndoitoc2 997\n");
				return 1;
			}
			me->set_save("doiphoto", 15);
			if (!me->get_save("old_photo"))
				me->set_save("old_photo", me->get_photo());
			me->set_photo(gt);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần :\n Khuôn mặt đã được hiển thị ở ảnh Avatar để ngươi xem trước. \nNgươi muốn chọn Khuôn mặt này làm Khuôn mặt chính thức không ? \n" ESC "Xác nhận thay đổi khuôn mặt \ndoitoc2 555\n" ESC "Trở về \ndoitoc2 996\n");
		}
		else
			return 1;
	}
	if (arg == "111")
	{
		if (me->get_cash() < 20000)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 20.000 ngân lượng ! \n" ESC "Rời khỏi.");
			return 0;
		}
		me->add_cash(-20000);
		me->delete_save("old_photo");
		me->delete_save("doiphoto");
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		me->set_photo(gt2 + 1);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức khuôn mặt mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "222")
	{
		if (me->get_cash() < 20000)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 20.000 ngân lượng ! \n" ESC "Rời khỏi.");
			return 0;
		}
		me->add_cash(-20000);
		me->delete_save("old_photo");
		me->delete_save("doiphoto");
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		me->set_photo(gt2 + 2);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức khuôn mặt mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "333")
	{
		if (me->get_cash() < 20000)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 20.000 ngân lượng ! \n" ESC "Rời khỏi.");
			return 0;
		}
		me->add_cash(-20000);
		me->delete_save("old_photo");
		me->delete_save("doiphoto");
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		me->set_photo(gt2 + 3);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức khuôn mặt mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "444")
	{
		if (me->get_cash() < 20000)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 20.000 ngân lượng ! \n" ESC "Rời khỏi.");
			return 0;
		}
		me->add_cash(-20000);
		me->delete_save("old_photo");
		me->delete_save("doiphoto");
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		me->set_photo(gt2 + 4);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức khuôn mặt mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "555")
	{
		if (me->get_cash() < 20000)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 20.000 ngân lượng ! \n" ESC "Rời khỏi.");
			return 0;
		}
		me->add_cash(-20000);
		me->delete_save("old_photo");
		me->delete_save("doiphoto");
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		me->set_photo(gt2 + 5);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức khuôn mặt mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "100")
	{
		if (me->get_hair() == 10 || me->get_hair() == 1010 || me->get_hair() == 1009)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Hãy ẩn tóc áo cưới trước khi thay đổi kiểu tóc ! \n" ESC "Rời khỏi.");
			return 0;
		}
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		if (me->get_save_2("doitoc.score") >= 2)
		{
			if ("sys/sys/test_db"->get_yuanbao(me) < 100)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 10 Kim Nguyên Bảo ! \n" ESC "Rời khỏi.");
				return 0;
			}
			"sys/sys/test_db"->add_yuanbao(me, -100);
		}
		me->add_save_2("doitoc.score", 1);
		me->set_hair(gt2 + 1);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c", 0x56, 0xff);
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức kiểu tóc mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "200")
	{
		if (me->get_hair() == 10 || me->get_hair() == 1010 || me->get_hair() == 1009)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Hãy ẩn tóc áo cưới trước khi thay đổi kiểu tóc ! \n" ESC "Rời khỏi.");
			return 0;
		}
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		if (me->get_save_2("doitoc.score") >= 2)
		{
			if ("sys/sys/test_db"->get_yuanbao(me) < 100)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 10 Kim Nguyên Bảo ! \n" ESC "Rời khỏi.");
				return 0;
			}
			"sys/sys/test_db"->add_yuanbao(me, -100);
		}
		me->add_save_2("doitoc.score", 1);
		me->set_hair(gt2 + 2);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c", 0x56, 0xff);
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức kiểu tóc mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "300")
	{
		if (me->get_hair() == 10 || me->get_hair() == 1010 || me->get_hair() == 1009)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Hãy ẩn tóc áo cưới trước khi thay đổi kiểu tóc ! \n" ESC "Rời khỏi.");
			return 0;
		}
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		if (me->get_save_2("doitoc.score") >= 2)
		{
			if ("sys/sys/test_db"->get_yuanbao(me) < 100)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 10 Kim Nguyên Bảo ! \n" ESC "Rời khỏi.");
				return 0;
			}
			"sys/sys/test_db"->add_yuanbao(me, -100);
		}
		me->add_save_2("doitoc.score", 1);
		me->set_hair(gt2 + 3);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c", 0x56, 0xff);
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức kiểu tóc mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "400")
	{
		if (me->get_hair() == 10 || me->get_hair() == 1010 || me->get_hair() == 1009)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Hãy ẩn tóc áo cưới trước khi thay đổi kiểu tóc ! \n" ESC "Rời khỏi.");
			return 0;
		}
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		if (me->get_save_2("doitoc.score") >= 2)
		{
			if ("sys/sys/test_db"->get_yuanbao(me) < 100)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 10 Kim Nguyên Bảo ! \n" ESC "Rời khỏi.");
				return 0;
			}
			"sys/sys/test_db"->add_yuanbao(me, -100);
		}
		me->add_save_2("doitoc.score", 1);
		me->set_hair(gt2 + 4);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c", 0x56, 0xff);
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức kiểu tóc mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "500")
	{
		if (me->get_hair() == 10 || me->get_hair() == 1010 || me->get_hair() == 1009)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Hãy ẩn tóc áo cưới trước khi thay đổi kiểu tóc ! \n" ESC "Rời khỏi.");
			return 0;
		}
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		if (me->get_save_2("doitoc.score") >= 2)
		{
			if ("sys/sys/test_db"->get_yuanbao(me) < 100)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 10 Kim Nguyên Bảo ! \n" ESC "Rời khỏi.");
				return 0;
			}
			"sys/sys/test_db"->add_yuanbao(me, -100);
		}
		me->add_save_2("doitoc.score", 1);
		me->set_hair(gt2 + 5);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c", 0x56, 0xff);
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức kiểu tóc mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "600")
	{
		if (me->get_hair() == 10 || me->get_hair() == 1010 || me->get_hair() == 1009)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Hãy ẩn tóc áo cưới trước khi thay đổi kiểu tóc ! \n" ESC "Rời khỏi.");
			return 0;
		}
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		if (me->get_save_2("doitoc.score") >= 2)
		{
			if ("sys/sys/test_db"->get_yuanbao(me) < 100)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 10 Kim Nguyên Bảo ! \n" ESC "Rời khỏi.");
				return 0;
			}
			"sys/sys/test_db"->add_yuanbao(me, -100);
		}
		me->add_save_2("doitoc.score", 1);
		me->set_hair(gt2 + 6);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c", 0x56, 0xff);
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức kiểu tóc mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "700")
	{
		if (me->get_hair() == 10 || me->get_hair() == 1010 || me->get_hair() == 1009)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Hãy ẩn tóc áo cưới trước khi thay đổi kiểu tóc ! \n" ESC "Rời khỏi.");
			return 0;
		}
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		if (me->get_save_2("doitoc.score") >= 2)
		{
			if ("sys/sys/test_db"->get_yuanbao(me) < 100)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 10 Kim Nguyên Bảo ! \n" ESC "Rời khỏi.");
				return 0;
			}
			"sys/sys/test_db"->add_yuanbao(me, -100);
		}
		me->add_save_2("doitoc.score", 1);
		me->set_hair(gt2 + 7);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c", 0x56, 0xff);
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức kiểu tóc mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}
	if (arg == "800")
	{
		if (me->get_hair() == 10 || me->get_hair() == 1010 || me->get_hair() == 1009)
		{
			send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Hãy ẩn tóc áo cưới trước khi thay đổi kiểu tóc ! \n" ESC "Rời khỏi.");
			return 0;
		}
		gt2 = me->get_gender() == 1 ? 0 : 1000;
		if (me->get_save_2("doitoc.score") >= 2)
		{
			if ("sys/sys/test_db"->get_yuanbao(me) < 100)
			{
				send_user(me, "%c%c%w%s", ':', 3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 10 Kim Nguyên Bảo ! \n" ESC "Rời khỏi.");
				return 0;
			}
			"sys/sys/test_db"->add_yuanbao(me, -100);
		}
		me->add_save_2("doitoc.score", 1);
		me->set_hair(gt2 + 8);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user(me, "%c%c", 0x56, 0xff);
		send_user(me, "%c%c%w%s", ':', 3, 9958, sprintf("Ảo Diện Thần:\n Hãy thưởng thức kiểu tóc mới của ngươi đi nhé!\n" ESC "Đóng lại"));
		return 1;
	}

	/*	if ( arg == "1000")
	{
		if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x0981);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "2000")
	{
       if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x00c0c0c0);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "3000")
	{
        if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x00800080);//0x0020
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "4000")
	{
        if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x18cc);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "5000")
	{
        if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x6006);//0x3000
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "6000")
	{
        if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0xe6fefd);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "7000")
	{
        if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x00DDA0DD);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "8000")
	{
        if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x6300);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "9000")
	{
        if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x0186);//0x3180
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "10000")
	{
        if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x5140);//0x4100
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "11000")
	{
        if ( me->get_cash() < 100000 )
		{
		send_user(me,"%c%c%w%s",':',3, 9958, "Ảo Diện Thần:\n Trên người ngươi không đủ 100.000 ngân lượng ! \n"ESC"Rời khỏi.");
		return 1;
		}
		me->add_cash(-100000);
		me->set_hair_color(0x00FFFFE0);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Hãy thưởng thức màu tóc mới của ngươi đi nhé!\n"
			ESC"Đóng lại"));
    return 1;
	}
	if ( arg == "12000")
	{
		me->set_hair_color(0);
		me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		send_user( me, "%c%c", 0x56, 0xff);
		send_user(me,"%c%c%w%s",':',3,9958,sprintf("Ảo Diện Thần:\n Ngươi đã xoá bỏ màu tóc thành công !\n"
			ESC"Đóng lại"));
    return 1;
	}*/

	if (arg == "996")
	{
		if (me->get_save("doiphoto") > 0 && me->get_save("old_photo"))
		{
			me->set_photo(me->get_save("old_photo"));
			me->delete_save("old_photo");
			me->delete_save("doiphoto");
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		}
		send_user(me, "%c%c", 0x56, 0xff);
		"/npc/test/aodienthan"->do_welcome("4");
		return 1;
	}
	if (arg == "997")
	{
		send_user(me, "%c%c", 0x56, 0xff);
		"/npc/test/aodienthan"->do_welcome("4");
		return 1;
	}
	if (arg == "998")
	{
		send_user(me, "%c%c", 0x56, 0xff);
		"/npc/test/aodienthan"->do_welcome("2");
		return 1;
	}
	if (arg == "999")
	{
		send_user(me, "%c%c", 0x56, 0xff);
		"/npc/test/aodienthan"->do_welcome("1");
		return 1;
	}
	return 1;
}