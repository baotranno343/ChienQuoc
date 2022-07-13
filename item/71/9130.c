
#include <equip.h>
#include <ansi.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }
int is_thanbinh() { return 1; }
int is_thanbinh2() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Đoạt Mệnh Ma Khí");
        set_picid_1(7809);
        set_picid_2(7809);

        set_level(115);
        set_bind(1);
        set_value(20000);
        set_max_lasting(36099);
        set("ap+", 450);
        set("hp+", 100);
        set("!%+", 300);
        set("double", 200);
        set_item_color(5); //紫色
        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return 115; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}

//
string get_tail_desc()
{
        return "【Đặc tính】Khi tấn công có thể gây 300 sát thương Độc Tố cho mục tiêu trong 20 giây.\n"
               "Đồng thời có tỷ lệ nhất định thi triển Độc Long Ám Xạ làm cho mục tiêu\n"
               "mù loà 6 giây hoặc phá vỡ 100 phòng thủ của mục tiêu.";
}