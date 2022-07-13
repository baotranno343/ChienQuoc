
#include <equip.h>
#include <ansi.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }
int is_thanbinh() { return 1; }
int is_thanbinh4() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Phá Thiên Thương");
        set_picid_1(6890);
        set_picid_2(6890);

        set_level(115);
        set_bind(1);
        set_value(20000);
        set_max_lasting(36099);
        set("ap+", 470);
        set("hp+", 100);
        set("!%+", 300);
        set("?%+", 200);
        set_item_color(5); //紫色
        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return 115; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}

//
string get_tail_desc()
{
        return "【Đặc tính】Mỗi lần tấn công có xác suất giảm 320 Phòng Thủ của mục tiêu.\n"
               "Đồng thời có tỷ lệ nhất định thi triển Xích Long Phệ Hỏa tấn công\n"
               "làm mục tiêu choáng trong 3 giây.";
}