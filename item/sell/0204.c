#include <equip.h>
#include <ansi.h>
inherit USABLE;
inherit ITEM;
inherit COMBINED;

int is_key() { return 1; }

int get_item_value() { return 32; }
int get_item_value_2() { return 32; }
int get_item_number() { return 10001068; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Chìa Khóa May Mắn");
        set_picid_1(6705);
        set_picid_2(6705);
        set_level(5);
        set_value(50);
        set_amount(1);
}

// 函数：获取描述
string get_desc()
{
        return "Vật phẩm dùng để kích hoạt Hộp May Mắn. \n Khi tra chìa khóa vào, có thể làm " HIY "Hộp May Mắn" NOR " mở ra.";
}
