#include <item.h>
#include <ansi.h>
#include <equip.h>
inherit ITEM;

int get_item_value() { return 200; }
int get_item_value_2() { return 200; }
int get_item_number() { return 10001025; }
int get_item_color() { return 1; }

// 修理道具
int is_repair() { return 1; }

// 函数：构造处理
void create()
{
	set_name("魔力锤");
	set_picid_1(3411);
	set_picid_2(3411);
	set_value(50);
	set_record(1);
	// -- 与原装备相比增加绑定属性
	set_no_give(1);
	set_no_sell(1);
	//
}

// 函数：获取描述
string get_desc()
{
	return "外表怎么看都是一把普通的木锤子，但却蕴含了奇异的魔力。\n（将魔力锤拖放至目标装备上便可使用）\n可修复指定装备原有的耐久上限，\n同时不会对装备造成任何的损耗。";
}

// 函数：获取简短描述
string get_short()
{
	return "将魔力锤拖放至目标装备上便可修复该装备原有的耐久上限。";
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
	string file, result;
	int maxlast, last, number;
	file = get_file_name(equip);
	if (!equip->is_equip())
		return 0;
	//        if( equip->get_weapon_code() == THROWING ) return 0;
	//        if( equip->get_equip_type() == HAND_TYPE ) return 0;
	if (equip->get_equip_type() == FAMILY_TYPE)
		return 0;
	maxlast = file->get_max_lasting();
	if (maxlast == equip->get_max_lasting() && equip->get_equip_type() != HAND_TYPE)
	{
		result = sprintf("该装备耐久上限已经达到了%d点的最大值，无法再修复了。", equip->get_max_lasting() / 100);
		send_user(me, "%c%s", '!', result);
		return 1;
	}
	number = equip->get_item_number();
	//if (number==10001023||number==10001024 || number==10001078 )
	if (equip->get_no_repair())
	{
		result = "不能修复该物品！";
		send_user(me, "%c%s", '!', result);
		return 1;
	}
	last = equip->get_lasting();
	if (type == 1)
	{
		result = sprintf("%s的耐久度为%d/%d，你确定要使用魔力锤恢复其耐久上限吗？\n" ESC "%c\n" ESC "\nmove ! %x# %d\n", equip->get_name(), last / 100, equip->get_max_lasting() / 100, 1, getoid(item), get_d(equip));
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	last = equip->get_max_lasting();
	last = maxlast;
	equip->set_max_lasting(last);
	equip->set_lasting(last);
	result = sprintf("合成消失 %s,%d,%s,%s @%s %s %s %d %s %d_%d_%d", me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), "", item->get_name(), "/sys/item/item"->get_pawn_save_string(item), 1, item->get_user_id(), get_z(me), get_x(me), get_y(me));
	//"/sys/user/cmd"->log_item(result);
	item->remove_from_user();
	destruct(item);
	result = sprintf("你成功地加强了%s。", equip->get_name());
	send_user(me, "%c%s", '!', result);
	return 1;
}