
#include <cmd.h>
#include <ansi.h>

inherit ITEM;

int get_item_value() { return 500; }
int get_item_value_2() { return 500; }
int get_item_color() { return 2; }
// 函数：构造处理
void create()
{
        set_name("Tù Và Đế Vương");
        set_picid_1(0095);
        set_picid_2(0095);
        set_unit("只");
        set_value(150);
}

// 函数：获取描述
string get_desc()
{
        return "Vật phẩm dùng để Sáng lập Bang phái";
}
