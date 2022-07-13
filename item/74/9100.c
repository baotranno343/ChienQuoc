
#include <equip.h>
#include <ansi.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Lục Thần Thương");
        set_picid_1(6894);
        set_picid_2(6894);

        set_level(100);
		set_bind(1);
        set_value(20000);
        set_max_lasting(16099);
        set("ap+", 420);
        set("hp+", 100);
        set("!%+", 300);
        set("?%+", 200);
 	set_item_color(3);	//紫色
        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return 100; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}

//
string get_tail_desc()
{
	return "[Đặc tính]Mỗi lần tấn công có 15% xác suất giảm 160 Phòng Thủ của mục tiêu.";		
}