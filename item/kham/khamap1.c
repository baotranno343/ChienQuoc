#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

// 函数：成品编号
int get_fin_type() { return 1525; }
int get_item_color() {return 3 ;}

// 函数：镶嵌识别
int get_item_type() { return ITEM_TYPE_DAKHAM; }

// 函数：构造处理
void create()
{
        set_name("Bảo thạch Ngoại công - Cấp 1");
        set_unit("ap3");
        set_picid_1(12095);
        set_picid_2(12095);
        set_value(100);
        set("ap3", 100);
}

// 函数：获取描述
string get_desc()
{
        return "Một loại bảo thạch kì bí\n Dùng để khảm nạm vào trang bị, gia tăng 100 điểm ngoại công cho nhân vật.";
}
