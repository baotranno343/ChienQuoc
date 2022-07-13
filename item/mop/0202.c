#include <equip.h>
#include <ansi.h>
inherit USABLE;
inherit ITEM;

int is_key() {return 1;}

int get_item_color() {return 2 ;}

// 函数：构造处理
void create()
{
        set_name("紫金钥匙");
        set_picid_1(6705);
        set_picid_2(6705);
        set_level(3);
        set_value(160000);
}

// 函数：获取描述
string get_desc()
{
        return "传闻能开启周王藏匿宝藏的宝箱。\n将钥匙拖放于放大状态的宝箱之上，便可将"HIR"紫金宝箱"NOR"打开。";
}
