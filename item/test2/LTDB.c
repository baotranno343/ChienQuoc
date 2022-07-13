#include <item.h>
#include <ansi.h>
#include <equip.h>
inherit ITEM;

int get_item_value() { return 50; }
int get_item_value_2() { return 50; }
int get_item_color() { return 2; }
// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_PET; }
//宠物物品
int is_pet_item() { return 1; }
// 修理道具
int is_specal_move() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Linh Thuỷ Đặc Biệt");
	set_picid_1(3210);
	set_picid_2(3210);
	set_value(2);
	set_record(1);
}

// 函数：获取描述
string get_desc()
{
	return "Dùng để hóa giải trạng thái Khóa của các vật phẩm thấp hơn hoặc bằng cấp 150.\n Sử dụng đối với Bảo Thú sẽ giúp Bảo Thú xoá bỏ trạng thái Phong ấn để có thể giao dịch, mua bán.";
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
	//	if (equip->get_level()>150) return 0;
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
	result = sprintf("Mở khoá trang bị %s , %d , %s, %s @ %s %s %s %d %s %d _ %d _ %d ", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
	//"/sys/user/cmd"->log_item(result);
	item->remove_from_user();
	destruct(item);
	return 1;
}
// 函数：使用效果
int get_use_effect(object me) { return __FILE__->get_use_effect_call(me, this_object()); }

int get_use_effect_call(object me, object item)
{
	object owner;
	if (!me->is_pet())
		return 0;
	owner = me->get_owner();
	if (!me->get_save("no_give") && !me->get_save("no_sell"))
	{
		send_user(owner, "%c%s", '!', me->get_name() + " không bị Phong ấn");
		return 0;
	}
	write_user(owner, me->get_name() + " đã mất đi trạng thái Phong ấn");
	me->set_save("no_give", 0);
	me->set_save("no_sell", 0);
	send_user(owner, "%c%c%d%d", 0xA1, 28, getoid(me), 0);
	return 1;
}