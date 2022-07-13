#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;

int get_max_combined() { return 1000; }
int get_item_color() { return 3; }
int is_food_huyenthu() { return 1; }

// 函数：构造处理
void create()
{
        set_level(1);
        set_name("Thiên Hỏa Thạch Bàn Đơn");
        set_picid_1(4051);
        set_picid_2(4051);
        set("exp", 10000);
        set_amount(1);
        set_value(50);
        set_no_give(1);
}

// 函数：获取描述
string get_desc()
{
        return "Viên đá toát lên bề mặt hơi nóng như lửa, nghe nói Thất quốc tổng quản biết cách sử dụng loại đá này\n Sử dụng vào Huyễn thú sẽ trực tiếp gia tăng 1000 điểm kinh nghiệm.";
}
