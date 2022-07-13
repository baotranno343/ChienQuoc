#include <item.h>
#include <ansi.h>
#include <equip.h>
inherit ITEM;

int get_item_value() { return 3; }
int get_item_value_2() { return 3; }
int get_item_number() { return 10001074; }
int get_item_color() { return 1; }

// 修理道具
int is_specal_move() { return 1; }

int get_no_lock() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Khoá Càn Khôn");
	set_picid_1(9611);
	set_picid_2(9611);
	set_value(50);
	//	set_save("knb2",20);
	set_record(1);
	set_no_give(1);
}

// 函数：获取描述
string get_desc()
{
	return "Pháp khí của nguyên thủy thiên tôn, tương truyền do hàn thiết rèn luyện ngàn năm tạo thành, có thể khoá chặt vạn vật trên thế gian \n Có thể khoá chặt phẩm vật trong 14 ngày. \n Trong thời gian này, phẩm vật không thể giao dịch, mua bán, vứt bỏ. \n Phương pháp sử dụng: Kéo và bỏ vào vật phẩm nào cần khoá.\n";
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
	if (equip->get_no_lock())
		return 0;
	if (equip->get_max_combined() >= 1)
	{
		send_user(me, "%c%s", '!', "Vật phẩm xếp chồng không thể khoá !");
		return 1;
	}
	if (type == 1)
	{
		if (equip->is_locked() > 0)
		{
			result = sprintf("%s đã khoá, bạn muốn tăng thêm thời gian khoá không ?\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", equip->get_name(), 1, getoid(item), get_d(equip));
			send_user(me, "%c%c%s", 0x59, 1, result);
			return 1;
		}
		result = sprintf("%s sẽ bị khoá thêm 14 ngày, bây giờ không thể vứt bỏ hay giao dịch.\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", equip->get_name(), 1, getoid(item), get_d(equip));
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	if (equip->is_locked() > 0)
		equip->set_lock_until(equip->get_lock_until() + 14 * 24 * 3600);
	else
		equip->set_locked(14 * 24 * 3600);
	send_user(me, "%c%d%c", 0x31, getoid(equip), 0);
	result = sprintf("加锁消失 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
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
	if (type == 1)
	{
		if (pet->get_save("locktime") > time())
		{
			result = sprintf("%s đã khoá, bạn muốn tăng thêm thời gian khoá không ?\n" ESC "%c\n" ESC "\npet %x# lock 1\n", pet->get_name(), 1, getoid(pet));
			send_user(me, "%c%c%s", 0x59, 1, result);
			return 1;
		}
		result = sprintf("%s sẽ bị khoá thêm 14 ngày, lúc đó Bảo Thú không thể giao dịch, mua bán, phóng sinh.\n" ESC "%c\n" ESC "\npet %x# lock 1\n", pet->get_name(), 1, getoid(pet));
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	if (pet->get_save("locktime") > time())
		pet->set_save("locktime", pet->get_save("locktime") + 14 * 24 * 3600);
	else
		pet->set_save("locktime", time() + 14 * 24 * 3600);
	pet->save();
	result = sprintf("宠物加锁消失 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
	//"/sys/user/cmd"->log_item(result);
	item->remove_from_user();
	destruct(item);
	return 1;
}