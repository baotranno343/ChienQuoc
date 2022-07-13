#include <item.h>
#include <ansi.h>
#include <equip.h>
inherit ITEM;

int get_item_value() { return 100; }
int get_item_value_2() { return 100; }
//int get_item_number() {return 10001029 ;}
int get_item_color() { return 1; }

// 修理道具
int is_repair() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Dầu Chúc Phúc");
	set_picid_1(3154);
	set_picid_2(3154);
	set_value(50);
	set_record(1);
}

// 函数：获取描述
string get_desc()
{
	return "Có thể hóa giải các trang bị đã bị Phong Ấn về trạng thái ban đầu (để có thể giao dịch, trao đổi cho người khác).";
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
	if (equip->get_bind() != 2)
	{
		result = "Trang bị không có trạng thái phong ấn.";
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
		result = sprintf("Bạn muốn giải trừ Phong ấn của %s không ?\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", equip->get_name(), 1, getoid(item), get_d(equip));
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip->set_bind(1);
	send_user(me, "%c%d%c", 0x31, getoid(equip), 0);
	result = sprintf("合成消失 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
	//"/sys/user/cmd"->log_item(result);
	item->remove_from_user();
	destruct(item);
	return 1;
}