
#include <equip.h>
#include <ansi.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 9; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Thần Bảo Kiếm");
        set_picid_1(6872);
        set_picid_2(6872);

        set_level(75);
		set_bind(1);
        set_value(20000);
        set_max_lasting(14099);
        set("ap+", 190);
        set("cp+", 380);
        set("dp+", 15);
        set("hp+", 50);
        set("double", 100);
        set("?%+", 100);
	set_item_color(3);	//紫色
        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 75; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}

//
string get_tail_desc()
{
	return "\"Pháp Thuật bảo kiếm mà Thái Thượng Ngọc Thần sử dụng\"\n Kết quả làm tổn hại\n và kết quả Trị Liệu bệnh trong quá trình nâng cấp bảo kiếm, nhiều nhất là 50 điểm";		
}