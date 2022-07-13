
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Bá Vương Kiếm");
        set_picid_1(7303);
        set_picid_2(7303);

        set_level(150);
        set_value(17000);
        set_max_lasting(86599);
		set("c!%+", 10);
		set("double", 500);
//		set("hp*+",1);
//		set("mp*+", 1);
        set("dp+", 300);
		set("pp+", 300);
        set("cp+", 400);
        set("sp+", 100);
	//	set_item_color(3);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_07; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}

string get_tail_desc()
{
	return "[Đặc tính]Khi tấn công có 20％ \nxác suất phá Giáp Nội mục tiêu.";		
}