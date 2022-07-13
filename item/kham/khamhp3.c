#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

// 函数：成品编号
int get_fin_type() { return 1524; }
int get_item_color() { return 5; }

// 函数：镶嵌识别
int get_item_type() { return ITEM_TYPE_DAKHAM; }

// 函数：构造处理
void create()
{
        set_name("Bảo thạch Khí huyết - Cấp 3");
        set_unit("hp3");
        set_picid_1(12091);
        set_picid_2(12091);
        set_value(100);
        set("hp3", 3);
}

// 函数：获取描述
string get_desc()
{
        return "Một loại bảo thạch kì bí\n Dùng để khảm nạm vào trang bị, gia tăng 6% điểm khí huyết cho nhân vật.";
}
