
#include <equip.h>
#include <ansi.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Ngọc La Quyền Thủ");
        set_picid_1(6834);
        set_picid_2(6834);

        set_level(100);
		set_bind(1);
        set_value(20000);
        set_max_lasting(16099);
        set("ap+", 430);
        set("hp+", 100);
        set("double", 200);
        set("!%+", 300);
 	set_item_color(3);	//紫色
        setup();

        set_weapon_type(UNARMED);
}

// 函数：获取武器级别
int get_weapon_level() { return 100; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Quyền Pháp\"";
}

//
string get_tail_desc()
{
	return "[Đặc tính]Mỗi lần tấn công có 20% xác suất gây Choáng trong 2 giây.";	
}