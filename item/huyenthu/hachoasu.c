#include <item.h>
#include <npc.h>
#include <ansi.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;
inherit "/inh/equip/equip";
private
int EXP;
private
int diem_add_exp = 5;
private
int time_add_exp = 5;
private
int ap;
private
int cp;
private
int dp;
private
int pp;
private
int doubl;

int get_item_value() { return 100; }
int get_item_value_2() { return 100; }

#define PICID 9031

int get_item_color()
{
	return 3;
};

int set_exp(int i) { return EXP = i; }
int get_max_exp()
{
	switch (get("lv"))
	{
	case 1:
		return 50000;
		break;
	case 2:
		return 120000;
		break;
	case 3:
		return 220000;
		break;
	case 4:
		return 380000;
		break;
	}
}
void set_chi_so()
{
	switch (get("lv"))
	{
	case 1:
		ap = 8;
		cp = 8;
		dp = 1;
		pp = 1;
		doubl = 3;
		break;
	case 2:
		ap = 9;
		cp = 9;
		dp = 2;
		pp = 2;
		doubl = 4;
		break;
	case 3:
		ap = 10;
		cp = 10;
		dp = 3;
		pp = 3;
		doubl = 5;
		break;
	case 4:
		ap = 11;
		cp = 11;
		dp = 4;
		pp = 4;
		doubl = 6;
		break;
	case 5:
		ap = 14;
		cp = 14;
		dp = 7;
		pp = 7;
		doubl = 9;
		break;
	}
}
int get_exp() { return EXP; }
int add_exp(int i) { return EXP += i; }
int is_huyenthu() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Huyễn Thú - Hắc Hỏa Sư");
	set_picid_1(101);
	set_picid_2(101);
	set("lv", 1);
	set_bind(2);
	set_hide(0);
	set_no_sell(1);
	set_no_drop(1);
	set_no_get(1);
	set_no_give(1);
	setup();
}

// 函数：获取描述
string get_desc()
{

	string exp = "", color = HIG;
	//	object me = this_object();
	set_chi_so();
	if (get("lv") < 5)
	{
		exp = sprintf("Kinh nghiệm: %d/%d", get_exp(), get_max_exp());
	}

	else
	{
		exp = sprintf("Kinh nghiệm đã đạt giới hạn");
	}

	return sprintf(" Huyễn Thú trong truyền thuyết, sinh ra từ những ngọn lửa tăm tối.\nCấp %d \n" + exp + "\n" PPM "Ngoại công: +%d%% \n" PPM "Nội công: +%d%% \n" PPM "Ngoại kháng: +%d%%\n" PPM "Nội kháng: +%d%% \n" PPM "Bạo kích : +%d%%\n" NOR HIG "Huyễn Thú đạt cấp 4 trở lên có thể cưỡi. Có thể tìm thấy mệnh lệnh trong giao diện kỹ năng" NOR "\n \nKhông thể giao dịch \nKhông thể bán cho NPC \nKhông thể vứt bỏ", get("lv"), ap, cp, dp, pp, doubl);
}

// 函数：使用效果
int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

// 函数：使用效果(在线更新)
int get_use_effect_callout(object me, object item)
{
	object *obj, zombie, npc;
	int size, index, p, z, x, y;
	set_chi_so();
	//处理时间控制上面的。

	obj = me->get("zombie2");
	size = sizeof(obj);

	if (size)
	{
		for (index = 0; index < size; index++)
		{
			zombie = obj[index];
			//printf(zombie);
			if (!objectp(zombie))
				continue;
			send_user(get_scene_object_2(zombie, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(zombie), get_y(zombie), 9414, 1, OVER_BODY, PF_ONCE);
			send_user(me, "%c%c%d", 0x2c, 0, getoid(zombie));
			zombie->remove_from_scene();
			destruct(zombie);
		}

		me->delete ("zombie2");
		me->delete_2("jiguan_huyenthu");
		remove_call_out("auto_add_exp");
		if (item->get_exp() >= item->get_max_exp() || item->get_exp() + diem_add_exp >= item->get_max_exp())
		{
			item->add_exp(diem_add_exp);
			item->set("lv", (item->get("lv") + 1));
			send_user(me, "%c%d%c", 0x31, getoid(item), 0);
		}
		if (me->get("chuyenhuyenthu") == 1 && item->get("lv") >= 4)
		{
			me->set_ride(0);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		}

		USER_ENERGY_D->count_all_prop(me);
		return 0;
	}

	if (item->get("lv") >= 4)
	{
		if (me->get("chuyenhuyenthu") == 1)
		{
			me->set_ride(18);
			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
		}
		else
		{
			npc = new ("/npc/std/jiguan_huyenthu");
			npc->set_name(get_name());
			npc->set_char_picid(PICID);
			npc->set_head_color(0x0020);
			npc->upgrade_level(1);
			npc->set_owner(me);
			npc->set_action_mode(2);
			z = get_z(me);
			x = get_x(me);
			y = get_y(me);
			p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK);
			x = p / 1000;
			y = p % 1000;
			npc->add_to_scene(z, x, y, 3);
		}
	}
	else
	{
		npc = new ("/npc/std/jiguan_huyenthu");
		npc->set_name(get_name());
		npc->set_char_picid(PICID);
		npc->set_head_color(0x0020);
		npc->upgrade_level(1);
		npc->set_owner(me);
		npc->set_action_mode(2);
		z = get_z(me);
		x = get_x(me);
		y = get_y(me);
		p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK);
		x = p / 1000;
		y = p % 1000;
		npc->add_to_scene(z, x, y, 3);
	}
	call_out("auto_add_exp", time_add_exp, me, item);
	me->add("zombie2", ({npc}));

	me->delete_2("jiguan_huyenthu");
	me->set_2("jiguan_huyenthu.ap", ap);
	me->set_2("jiguan_huyenthu.dp", dp);
	me->set_2("jiguan_huyenthu.cp", cp);
	me->set_2("jiguan_huyenthu.pp", pp);
	me->set_2("jiguan_huyenthu.do", doubl * 100);

	//	me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
	USER_ENERGY_D->count_all_prop(me);
	return 0;
}
void auto_add_exp(object me, object item)
{
	remove_call_out("auto_add_exp");
	if (objectp(item))
	{
		if (item->get_exp() >= item->get_max_exp() || item->get_exp() + diem_add_exp >= item->get_max_exp())
		{
			// item->add_exp(5);
			// item->set("lv", (item->get("lv") + 1));
			// send_user(me, "%c%d%c", 0x31, getoid(item), 0);
			send_user(me, "%c%s", '!', "Huyễn Thú Chuẩn Bị Thăng Cấp, Hãy Thu Hồi Huyễn Thú.");
			send_user(me, "%c%s", ';', "Huyễn Thú Chuẩn Bị Thăng Cấp, Hãy Thu Hồi Huyễn Thú.");
			call_out("auto_add_exp", time_add_exp, me, item);
			return 0;
		}
		item->add_exp(diem_add_exp);
		send_user(me, "%c%d%c", 0x31, getoid(item), 0);
		call_out("auto_add_exp", time_add_exp, me, item);
		return 0;
	}
	return 0;
}
//
string get_tail_desc()
{
	object item = this_object();
	string desc;

	return desc;
}