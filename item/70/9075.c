
#include <equip.h>
#include <ansi.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Anh Kiệt Quyền Nhẫn");
        set_picid_1(6833);
        set_picid_2(6833);

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

        set_weapon_type(UNARMED);
}

// 函数：获取武器级别
int get_weapon_level() { return 75; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Quyền Pháp\"";
}

//
string get_tail_desc()
{
	return "\"Đại Anh Kiệt lưu truyền\" \nKhi bị công kích \ncó tỷ lệ tự tạo giáp hộ thể";	
}