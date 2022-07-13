#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
#include <time.h>
int main(object me, string arg)
{
	int a, b, c, d, p, z, x, y;
	string action;

	// notify("Tính Năng Này Đang Tạm Khóa");
	// return 1;
	if (sscanf(arg, "%d %d", a, b) == 2)
	{

		switch (a)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			notify("Chỉ có thể sử dụng Gói Auto loại 5");
			return 1;
			break;
		case 5:
			if (b < 1 || b > 5)
			{
				notify("Chỉ có thể mua tối đa 5 giờ");
				return 1;
			}
			c = (b * 60 * 60) / 2;
			d = 25 * b;

			if ("/sys/sys/test_db"->get_yuanbao(me) < d)
			{
				notify("Không đủ Kim Nguyên Bảo");
				return 1;
			}
			"/sys/sys/test_db"->add_yuanbao(me, -d);
			set_effect_2(me, EFFECT_XUESHI_HP, c, 2);
			me->set_save("stone_hp", 90);
			send_user(me, "%c%w%w%c", 0x81, 2, c * 2, EFFECT_GOOD);
			set_effect_2(me, EFFECT_FALISHI_MP, c, 2);
			me->set_save("stone_mp", 90);
			send_user(me, "%c%w%w%c", 0x81, 4, c * 2, EFFECT_GOOD);
			// auto
			send_user(me, "%c%c%c%d", 0xb1, 1, 1, 3600 * b);
			me->set_save_2("timeAuto.timeNow", time());
			me->set_save_2("timeAuto.timeChoose", 3600 * b);
			send_user(me, "%c%s", ';', sprintf("Bạn đã sử dụng gói Auto loại 5 trong %d giờ, bạn bị trừ đi %d ngân bảo !", b, d));
			break;
		}
		return 1;
	}
	else if (sscanf(arg, "%s %d", action, b) == 2)
	{
		if (action == "open")
		{
			if (me->get_attack_mode() != 1)
			{
				notify("Chỉ có trạng thái Hòa Bình mới có thể bật Auto");
				return 1;
			}
			if (MAP_D->is_inside_city(get_z(me), get_x(me), get_y(me)))
			{
				notify("Bạn đang ở trong thành, không thể sử dụng Auto");
				return 1;
			}
			send_user(me, "%c%c%c", 0xb1, 2, 1);
			me->set("autoRun", 1);
		}
		if (action == "proof")
		{
			send_user(me, "%c%c%c", 0xb1, 2, 1);
			if (gone_time(me->get_save_2("timeAuto.timeNow")) > me->get_save_2("timeAuto.timeChoose"))
			{
				notify("Đã Hết Thời Gian Sử Dụng Auto");

				me->delete_save_2("timeAuto");
				me->delete ("autoRun");
				if ((p = efun::get_xy_point(80, IS_CHAR_BLOCK)))
				{
					x = p / 1000;
					y = p % 1000;
					me->add_to_scene(80, x, y);
				}
				send_user(me, "%c%c%c", 0xb1, 1, 0);
			}
		}
	}
	else if (sscanf(arg, "%s", action) == 1)
	{
		if (action == "close")
		{
			send_user(me, "%c%c%c", 0xb1, 2, 0);
			me->delete ("autoRun");
		}
	}
	return 1;
}