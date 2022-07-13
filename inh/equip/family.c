//门派信物
#include <ansi.h>
#include <map.h>
#include <effect.h>
#include <equip.h>

inherit ITEM;
inherit "/inh/equip/equip";

private
string FamilyName;

int get_equip_type() { return FAMILY_TYPE; }
string set_family_name(string family) { return FamilyName = family; }
string get_family_name() { return FamilyName; }

int get_hide() { return 0; }

//初始化师门信物的属性
void init_familyobj()
{
	string name;
	int level;
	object item = this_object();

	level = item->get_item_level();
	item->set_hide(0);
	name = item->get_family_name();
	if (level > 10)
		level = 10;
	switch (name)
	{
	case "Đào Hoa Nguyên":
		item->set("hp%", range_value(3 * level, 3, 15));
		//item->set("!%", range_value(300 * level, 300, 1500));
		//	item->set("ap%", range_value(2 * level, 2, 10));

		break;
	case "Cấm Vệ Quân":
		item->set("ap%", range_value(3 * level, 3, 15));
		//item->set("!%", range_value(200 * level, 200, 1500));

		break;
	case "Thục Sơn":
		item->set("cp%", range_value(3 * level, 3, 15));
		item->set("ap%", range_value(3 * level, 3, 15));
		//item->set("!%",range_value(3*level,300,1500));
		//item->set("c!%",range_value(3*level,3,1500));

		break;
	case "Đường Môn":
		//	item->set("ap%", range_value(3 * level, 3, 15));
		item->set("?%", range_value(300 * level, 300, 1500));

		break;
	case "Côn Luân":
		item->set("cp%", range_value(3 * level, 3, 15));
		//	item->set("c!%", range_value(2 * level, 2, 1000));

		break;
	case "Mao Sơn":
		item->set("mp%", range_value(3 * level, 3, 15));
		item->set("hp%", range_value(3 * level, 3, 15));

		break;
	case "Vân Mộng Cốc":
		//	item->set("cp%", range_value(3 * level, 3, 15));
		item->set("mp%", range_value(3 * level, 3, 15));
		item->set("trilieu", range_value(4 * level, 4, 40));
		break;
	}
}

// 函数：使用效果
int get_use_effect(object me)
{
	__FILE__->get_use_effect_callout(me, this_object());
	return 0;
}

// 函数：使用效果(在线更新)
int get_use_effect_callout(object me, object item)
{
	object map, npc;
	int z, x, y, p;

	if (gone_time(me->get_save_2("familyuse")) < 2) // 时间限制
	{
		return 1;
	}

	if (objectp(map = get_map_object(get_z(me))) && map->get_map_type() == BATTLE_MAP && map->is_changping())
	{
		send_user(me, "%c%s", '!', "Không thể sử dụng ở chiến trường.");
		return 0;
	}
	if (get_z(me) == 704)
	{
		notify("Trong Nhà Ngục không thể sử dụng");
		return 0;
	}
	if (present("Vật Phẩm Quý Bấu", me, 1, MAX_CARRY * 4))
	{
		send_user(me, "%c%s", '!', "Mang theo vật phẩm quý bấu không thể sử dụng.");
		return 0;
	}
	if (present("Ngân Phiếu", me, 1, MAX_CARRY * 4))
	{
		send_user(me, "%c%s", '!', "Mang theo Ngân Phiếu không thể sử dụng.");
		return 0;
	}
	if (objectp(npc = me->get_quest("escort.robber#")) && npc->is_escort_robber()) // 寻找蒙面人
	{
		send_user(me, "%c%s", '!', "Kẻ lạ xuất hiện, hành đọng bị ảnh hưởng.");
		return 0;
	}
	if (me->is_store_open())
	{
		send_user(me, "%c%s", '!', "Đang bán hàng rong, không thể sử dụng");
		return 0;
	}
	if (item->get_family_name() != "")
	{
		if (me->get_cash() < 50)
		{
			send_user(me, "%c%s", '!', "Sử dụng tín vật phải trả 50 lượng");
			return 0;
		}
		me->add_cash(-50);
		"sys/sys/count"->add_use("family_use", 50);
	}
	me->set_save_2("familyuse", time());
	switch (me->get_fam_name())
	{
	default:
		p = me->get_latest_city();
		if (p == 0)
			p = 110;
		z = p / 100;
		p = get_jumpin(z, p % 100);
		break;
	case "Đào Hoa Nguyên":
		z = 289;
		p = get_jumpin(z, 20);
		break;
	case "Thục Sơn":
		z = 273;
		p = get_jumpin(z, 20);
		break;
	case "Cấm Vệ Quân":
		z = 080;
		p = get_jumpin(z, 20);
		break;
	case "Đường Môn":
		z = 324;
		p = get_jumpin(z, 20);
		break;
	case "Mao Sơn":
		z = 269;
		p = get_jumpin(z, 20);
		break;
	case "Côn Luân":
		z = 054;
		p = get_jumpin(z, 20);
		break;
	case "Vân Mộng Cốc":
		z = 165;
		p = get_jumpin(z, 20);
		break;
	}

	if (p)
	{
		x = p / 1000;
		y = p % 1000;
		send_user(me, "%c%c%w%s", 0x5a, 0, 10, "Đang di chuyển……");
		send_user(me, "%c%c%c%w", 0x30, 0, 8, 60);
		//	        send_user( me, "%c%w%c%w", 0x50, 61, 0xff, 0 );
		me->set_2("travel.z", z);
		me->set_2("travel.p", p);
		me->set_2("travel.money", 0);
		set_effect(me, EFFECT_TRAVEL, 10);
		me->set("familyuse", 1);
		return 1;
	}
	else
	{
		write_user(me, ECHO "Không có hiệu quả.");
		return 0;
	}
}
