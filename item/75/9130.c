
#include <equip.h>
#include <ansi.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }
int is_thanbinh() { return 1; }
int is_thanbinh5() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Hoả Thiên Côn");
        set_picid_1(6851);
        set_picid_2(6851);

        set_level(115);
        set_bind(1);
        set_value(20000);
        set_max_lasting(36099);
        set("ap+", 465);
        set("hp+", 100);
        set("double", 200);
        set("?%+", 200);
        set_item_color(5); //紫色
        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return 115; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}

//
string get_tail_desc()
{
        return "【Đặc tính】Mỗi lần tấn công có xác suất gây Choáng trong 3 giây.\n"
               "Đồng thời có tỷ lệ nhất định thi triển Hoả Diệm Liên Kích tấn công\n"
               "làm phá vỡ 300 phòng thủ của mục tiêu trong 30 giây.";
}