#include <item.h>
#include <ansi.h>
#include <equip.h>
inherit ITEM;

int get_item_value() { return 100; }
int get_item_value_2() { return 100; }
int get_item_color() { return 1; }

// 修理道具
int is_repair() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Dầu Chúc Phúc Đặc Biệt");
	set_picid_1(3154);
	set_picid_2(3154);
	set_value(50);
	set_record(1);
}

// 函数：获取描述
string get_desc()
{
	return "Có thể hóa giải các trang bị đã bị Nhặt Phong Ấn về trạng thái ban đầu (để có thể giao dịch, trao đổi cho người khác).";
}

int move_item(object me, object item, object equip)
{
	return __FILE__->move_item_callout(me, item, equip, 1);
}

int move_item2(object me, object item, object equip)
{
	return __FILE__->move_item_callout(me, item, equip, 2);
}

int move_item_callout(object me, object item, object equip, int type)
{
	string result;
	if (!equip->is_equip())
		return 0;
	if (equip->get_bind() != 4)
	{
		result = "Trang bị không ở trạng thái Nhặt Phong Ấn。";
		send_user(me, "%c%s", '!', result);
		return 1;
	}
	if (equip->is_huyenthu())
	{
		result = "Không thể giải phong ấn Huyễn Thú.";
		send_user(me, "%c%s", '!', result);
		return 1;
	}
	if (type == 1)
	{
		result = sprintf("Bạn có muốn đem %s trở lại trạng thái không phong ấn không？\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", equip->get_name(), 1, getoid(item), get_d(equip));
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip->set_bind(1);
	send_user(me, "%c%d%c", 0x31, getoid(equip), 0);
	result = sprintf("Giải trừ phong ấn %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
	//"/sys/user/cmd"->log_item(result);
	item->remove_from_user();
	destruct(item);
	return 1;
}