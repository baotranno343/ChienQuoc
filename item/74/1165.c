
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Bá Vương Bổng");
        set_picid_1(7505);
        set_picid_2(7505);

        set_level(150);
        set_value(37000);
        set_max_lasting(83099);
        set("ap+", 400);
		set("double", 500);
//		set("hp*+", 1);
//		set("mp*+", 1);
		set("!%+", 5000);
        set("dp+", 200);
        set("pp+", 300);
        set("sp+", 100);
	//	set_item_color(3);

        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_11; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}

string get_tail_desc()
{
	return "[Đặc tính]Mỗi lần tấn công có 20％ \nxác xuất giảm phòng thủ đối phương.";		
}