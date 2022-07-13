
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Bá Vương Quyền Thủ");
        set_picid_1(7020);
        set_picid_2(7020);

        set_level(150);
        set_value(37000);
        set_max_lasting(82599);
        set("ap+", 400);
		set("double", 500);
		set("!%+", 6000);
//		set("hp*+", 1);
//		set("mp*+", 1);
        set("dp+", 200);
        set("pp+", 200);
        set("sp+", 100);
	//	set_item_color(3);

        setup();

        set_weapon_type(UNARMED);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_00; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Quyền Pháp\"";
}

string get_tail_desc()
{
	return "[Đặc tính]Khi bị tấn công có 20％ \nxác suất tạo giáp hộ thể.";		
}