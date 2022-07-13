
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Thanh Đồng Hộ Thủ");
        set_picid_1(7005);
        set_picid_2(7005);
        set_unit("双");

        set_level(50);
        set_value(12000);
        set_max_lasting(13599);
        set("ap", 78);
        set("!%", 15);

        setup();

        set_weapon_type(UNARMED);
}

// 函数：获取武器级别
int get_weapon_level() { return 5; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Quyền Pháp\"";
}
