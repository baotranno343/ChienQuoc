
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit MISSILE;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Bá Vương Tiễn");
        set_picid_1(7117);
        set_picid_2(7117);

        set_level(150);
        set_value(15000);
        set_max_lasting(94099);
        set("ap+", 400);
		set("double", 500);
//		set("hp*+",1);
//		set("mp*+", 1);
		set("t!%+", 10);
        set("dp+", 200);
        set("pp+", 200);
        set("sp+", 200);
	//	set_item_color(3);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_07; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}

string get_tail_desc()
{
	return "[Đặc tính]Mỗi lần tấn công có 20％ \nxác suất phá giáp mục tiêu.";	
}
