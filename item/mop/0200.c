#include <equip.h>
#include <ansi.h>
inherit USABLE;
inherit ITEM;

int is_key() {return 1;}

int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("红木钥匙");
        set_picid_1(6701);
        set_picid_2(6701);
        set_level(1);
        set_value(40000);
}

// 函数：获取描述
string get_desc()
{
        return "传闻能开启周王藏匿宝藏的宝箱。\n将钥匙拖放于放大状态的宝箱之上，便可将"HIR"红木宝箱"NOR"打开。";
}
