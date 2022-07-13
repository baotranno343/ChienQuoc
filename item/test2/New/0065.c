#include <item.h>
#include <ansi.h>
#include <equip.h>
inherit ITEM;

int get_item_value() { return 30; }
int get_item_value_2() { return 30; }
int get_item_color() { return 2; }

// 修理道具
int is_specal_move() { return 1; }

//宠物物品
int is_pet_item() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Siêu Cấp Linh Thủy");
	set_picid_1(3210);
	set_picid_2(3210);
	set_value(2);
	set_record(1);
}

// 函数：获取描述
string get_desc()
{
	return "Dùng để hóa giải trạng thái Khóa của các trang bị từ cấp 91-120.\n(Bao gồm các loại Bảo thú và Thần thú).";
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
	if (equip->get_level() < 91 || equip->get_level() > 120)
		return 0;
	if (equip->get_bind() != 5)
	{
		result = "Vật phẩm này không bị khóa";
		send_user(me, "%c%s", '!', result);
		return 1;
	}
	if (type == 1)
	{
		result = sprintf("Bạn có muốn hóa giải trang thái khóa của %s không?\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", equip->get_name(), 1, getoid(item), get_d(equip));
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip->set_bind(1);
	send_user(me, "%c%d%c", 0x31, getoid(equip), 0);
	result = sprintf("Hoá giải trạng thái khoá %s , %d , %s, %s @ %s %s %s %d %s %d _ %d _ %d ", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
	//"/sys/user/cmd"->log_item(result);
	item->remove_from_user();
	destruct(item);
	return 1;
}
int pet_item(object me, object item, object pet)
{
	return __FILE__->pet_item_callout(me, item, pet, 1);
}

int pet_item2(object me, object item, object pet)
{
	return __FILE__->pet_item_callout(me, item, pet, 2);
}

int pet_item_callout(object me, object item, object pet, int type)
{
	string result;
	if (pet->get_save("no_give") < 1)
		return 1;
	if (pet->get_save("no_sell") < 1)
		return 1;
	if (type == 1)
	{
		result = sprintf("%s đang trong trạng thái Phong ấn, bạn muốn huỷ bỏ trạng thái đó không ?.\n" ESC "%c\n" ESC "\npet %x# phongan 1\n", pet->get_name(), 1, getoid(pet));
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	pet->set_save("no_give", 0);
	pet->set_save("no_sell", 0);
	pet->save();
	result = sprintf("Hoá giải phong ấn bảo thú %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
	//"/sys/user/cmd"->log_item(result);
	item->remove_from_user();
	destruct(item);
	return 1;
}