
#include <equip.h>
#include <ansi.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Bích Hỏa Hàn Nguyệt Hoàn");
        set_picid_1(7813);
        set_picid_2(7813);

        set_level(75);
		set_bind(1);
        set_value(20000);
        set_max_lasting(14099);
        set("ap+", 305);
        set("dp+", 20);
        set("pp+", 50);
        set("!%+", 100);
        set("?%+", 100);
 	set_item_color(3);	//紫色
        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return 75; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}

//
string get_tail_desc()
{
	return "\"Bảo vật của kẻ giết người, giết người vô hình\"\n Khi tấn công có thể làm mục tiêu trúng 100 sát thương Độc Tố trong 20 giây.";	
}