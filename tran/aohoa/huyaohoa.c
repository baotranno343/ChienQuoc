#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

// 函数：成品编号
int get_fin_type() { return 1525; }
int is_aohoa_rm() { return 1; }
// 函数：镶嵌识别

// 函数：构造处理
void create()
{

        set_name("Hủy Ảo Hóa");
        set_picid_1(0210);
        set_picid_2(0210);
        set_value(100);
}

// 函数：获取描述
string get_desc()
{
        return "Dùng Để Hủy Ảo Hóa";
}
