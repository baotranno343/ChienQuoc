#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

// 函数：成品编号
int get_fin_type() { return 1525; }
int get_item_color() {return 5 ;}

// 函数：镶嵌识别
int get_item_type() { return ITEM_TYPE_DAKHAM; }

// 函数：构造处理
void create()
{
        set_name("Bảo thạch Ngoại kháng - Cấp 3");
        set_unit("dp3");
        set_picid_1(12093);
        set_picid_2(12093);
        set_value(100);
        set("dp3", 240);
}

// 函数：获取描述
string get_desc()
{
        return "Một loại bảo thạch kì bí\n Dùng để khảm nạm vào trang bị, gia tăng 240 điểm ngoại kháng cho nhân vật.";
}
