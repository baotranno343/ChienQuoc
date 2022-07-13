
#include <equip.h>
#include <effect.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 2111; }

// 有自己的do_look函数
int is_self_look() { return 1; }
void into_effect(object who, object me);

// 函数：构造处理
void create()
{
	set_name("Cơ Quan Tháp Thạch Sư");
	setup();
}

// 函数：对话处理
void do_look(object who)
{
	//if (who->get("mobox"))
	//	return;
	//else
	into_effect(who, this_object());
}

void into_effect(object who, object me)
{
	int rate, p, x, y, z, level, i;
	string file, *nTmp;
	object item, item1, map, *mem, npc;
	int knb, gold;
	z = get_z(me);
	map = get_map_object(z);
	level = map->get("S");
	if (!who->get("mobox"))
	{
		rate = random(100);
		if (rate < 2 * level / 50)
		{
			item = new ("item/kham/tuibaothach2");
		}
		else if (rate < 10 * level / 50)
		{
			item = new ("item/kham/tuibaothach1");
		}
		else
		{
			gold = (1000 + random(200)) * level;
		}
		if (!item && !gold)
			return;
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			if (item)
				destruct(item);
			return;
		}
		if (item)
		{
			p = item->move2(who, -1);
			send_user(who, "%c%s", '!', sprintf("Đã nhận thưởng vượt ải %s", item->get_name()));
			"cmd/base/tt"->main(who, sprintf("Đã nhận thưởng vượt ải %s", item->get_name()));
			item->add_to_user(p);
			who->set("mobox", 1);
		}
		else if (gold)
		{
			send_user(who, "%c%s", '!', sprintf("Đã nhận thưởng vượt ải %d ngân lượng", gold));
			"cmd/base/tt"->main(who, sprintf("Đã nhận thưởng vượt ải %d ngân lượng", gold));
			who->add_cash(gold);
			who->set("mobox", 1);
		}
	}
	mem = "ken/pb/map"->get_all_user(map);
	for (i = 0; i < sizeof(mem); i++)
	{
		if (!mem[i]->get("mobox"))
			return;
	}
	for (i = 0; i < sizeof(mem); i++)
	{
		mem[i]->delete ("mobox");
		send_user(mem[i], "%c%c%s", 0xA5, 1, sprintf("| TIẾN TỚI TẦNG %d", (map->get("S") + 1)));
	}
	if (map->get("S") == 50)
	{
		"ken/pb/map"->destruct_virtual_map(map, map->get_id());
		return;
	}
	map->add("S", 1);
	map->delete ("amount");

	me->goi_quai(10, map, get_z(me), me);
	map->delete ("die");
	me->remove_from_scene();
}
void goi_quai(int sec, object map, int z, object me)
{

	object npc, *mem;

	int i, x, y, p, level, size;

	mem = "ken/pb/map"->get_all_user(map);
	size = sizeof(mem);
	for (i = 0; i < size; i++)
	{
		level = level + mem[i]->get_level();
	}
	level = level / size;
	sec = sec - 1;
	if (sec > 0)
	{

		for (i = 0; i < sizeof(mem); i++)
		{
			if (mem[i])
			{
				tell_user(mem[i], "Quái vật sẽ xuất hiện sau %d giây nữa", sec);
			}
		}

		call_out("goi_quai", 1, sec, map, z, me);
	}
	else
	{
		if (map->get("S") < 50 && map->get("S") != 10 && map->get("S") != 10 && map->get("S") != 20 && map->get("S") != 30 && map->get("S") != 40)
		{

			for (i = 0; i < 20; i++)
			{
				npc = new ("ken/pb/pbquai");
				if (!npc)
				{

					continue;
				}

				else
				{
					npc->set_level(level);
					npc->init(map->get("S"));
				}

				if (!(p = efun::get_xy_point(891, IS_CHAR_BLOCK)))
				{

					continue;
				}

				x = (p % 1000000) / 1000;
				y = p % 1000;
				npc->add_to_scene(z, x, y);
				map->add("amount", 1);
			}
		}
		else
		{

			for (i = 0; i < 1; i++)
			{
				npc = new ("ken/pb/pbboss");
				if (!npc)
					continue;

				else
				{
					npc->set_level(level);
					npc->init(map->get("S"));
				}

				if (!(p = efun::get_xy_point(891, IS_CHAR_BLOCK)))
					continue;
				x = (p % 1000000) / 1000;
				y = p % 1000;
				npc->add_to_scene(z, x, y);
				map->add("amount", 1);
			}
		}
		destruct(me);
	}
}