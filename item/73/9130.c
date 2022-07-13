
#include <equip.h>
#include <ansi.h>

inherit WEAPON;

// 函数:适用门派
int get_family() { return 9; }
int is_thanbinh() { return 1; }
int is_thanbinh6() { return 1; }
// 函数:构造处理
void create()
{
        set_name("Huyết Lệ");
        set_picid_1(6868);
        set_picid_2(6868);

        set_level(115);
        set_bind(1);
        set_value(20000);
        set_max_lasting(36099);
        set("cp+", 500);
        set("hp+", 100);
        set("double", 400);
        set("?%+", 200);
        set_item_color(5); //紫色
        setup();

        set_weapon_type(SWORD);
}

// 函数:获取武器级别
int get_weapon_level() { return 115; }

// 函数:获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}

//
string get_tail_desc()
{
        return "【Đặc tính】Tăng sát thương pháp thuật 200-300 hoặc tăng hiệu quả trị liệu y thuật.\n"
               "Đồng thời có tỷ lệ bộc phát kỹ năng Thủy Long Nghịch Thể\n"
               "khiến tấn công làm mục tiêu bị choáng trong 6 giây hoặc gây hỗn loạn 2 giây.";
}