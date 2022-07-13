
#include <ansi.h>
#include <item.h>

inherit ITEM;
inherit USABLE;
inherit COMBINED;
private
int Z, X, Y;

int get_item_value() { return 30; }
int get_item_value_2() { return 30; }
//int get_item_number() {return 10001072 ;}
int get_item_color() { return 2; }
// 函数：藏宝图
// int is_treasure() { return 1; }

// 函数：藏宝图
int get_item_type() { return ITEM_TYPE_TREASURE; }

// 函数：获取Ｚ坐标
int get_map_z() { return Z; }

// 函数：设置Ｚ坐标
int set_map_z(int z) { return Z = z; }

// 函数：获取Ｘ坐标
int get_map_x() { return X; }

// 函数：设置Ｘ坐标
int set_map_x(int x) { return X = x; }

// 函数：获取Ｙ坐标
int get_map_y() { return Y; }

// 函数：设置Ｙ坐标
int set_map_y(int y) { return Y = y; }

// 函数：构造处理
void create()
{
	set_name("Trục Kim Tình Báo");
	set_picid_1(9813);
	set_picid_2(9813);
	set_unit("张");
	set_value(100);
	set_amount(1);
}

// 函数：获取描述
string get_desc()
{
	object map;
	int p;
	if (!clonep())
		return "Quyển trục khi lại tin tức nhận được từ người tình báo của Chu Vương. Hãy đến vị trí sau và mở trục tình báo ngươi sẽ có được gì đó";
	if (!(map = get_map_object(Z)))
	{
		if (p = XY_D->get_city_point(-1, IS_ITEM_BLOCK))
		{
			set_map_z(p / 1000000);
			set_map_x((p % 1000000) / 1000);
			set_map_y(p % 1000);
		}
	}
	return "Quyển trục khi lại tin tức nhận được từ người tình báo của Chu Vương.";
}

// 函数：使用效果
int get_use_effect(object me) { return __FILE__->get_use_effect_callout(me, this_object()); }

// 函数：使用效果(在线更新)
int get_use_effect_callout(object me, object item)
{
	object map, *monster, npc, ben;
	string name, file, result = "";
	int level, level2, pic, gold, p, i, size, u;
	int z0, x0, y0, z, x, y;

	if (get_z(me) != item->get_map_z()
		/*   ||      abs( get_x(me) - item->get_map_x() ) > 999
        ||      abs( get_y(me) - item->get_map_y() ) > 999*/
	)
	{
		send_user(me, "%c%s", '!', "Vị trí không đúng !");
		return 0;
	}
	if (USER_INVENTORY_D->get_free_count(me) < 5)
	{
		send_user(me, "%c%s", '!', "Hành trang không đủ 2 chỗ trống.");
		return 0;
	}
	item->add_amount(-1);
	//	item->remove_from_user();
	//	destruct(item);
	if (random100() < 30)
	{
		ben = new ("item/event/vattu/vattu1");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		ben = new ("item/event/vattu/vattu3");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		send_user(me, "%c%s", ';', "Bạn nhận được Vật Tư (1) và Vật Tư (3) !");
	}
	else if (random100() < 45)
	{
		ben = new ("item/event/vattu/vattu2");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		ben = new ("item/event/vattu/vattu4");
		p = ben->move2(me, -1);
		ben->add_to_user(p);

		send_user(me, "%c%s", ';', "Bạn nhận được Vật Tư (2) !");
	}
	else if (random100() < 60)
	{
		ben = new ("item/event/vattu/vattu2");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		ben = new ("item/event/vattu/vattu3");
		p = ben->move2(me, -1);
		ben->add_to_user(p);

		send_user(me, "%c%s", ';', "Bạn nhận được Vật Tư (3) !");
	}
	else if (random100() < 75)
	{
		ben = new ("item/event/vattu/vattu1");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		ben = new ("item/event/vattu/vattu5");
		p = ben->move2(me, -1);
		ben->add_to_user(p);

		send_user(me, "%c%s", ';', "Bạn nhận được Vật Tư (4) !");
	}
	else if (random100() < 90)
	{
		ben = new ("item/event/vattu/vattu4");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		ben = new ("item/event/vattu/vattu5");
		p = ben->move2(me, -1);
		ben->add_to_user(p);

		send_user(me, "%c%s", ';', "Bạn nhận được Vật Tư (5) !");
	}
	else
	{
		ben = new ("item/event/vattu/vattu1");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		ben = new ("item/event/vattu/vattu2");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		ben = new ("item/event/vattu/vattu3");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		ben = new ("item/event/vattu/vattu4");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		ben = new ("item/event/vattu/vattu5");
		p = ben->move2(me, -1);
		ben->add_to_user(p);
		send_user(me, "%c%s", ';', "Bạn nhận được Vật Tư (1), Vật Tư (2), Vật Tư (3), Vật Tư (4), Vật Tư (5) !");
	}
	return 0;
}
