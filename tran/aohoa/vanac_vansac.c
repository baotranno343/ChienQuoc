#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit USABLE;

// 函数：成品编号
int get_fin_type() { return 1525; }
int is_aohoa() { return 1; }
int get_item_color() { return 2; }
// 函数：镶嵌识别

// 函数：构造处理
void create()
{
        int rd = random(1000000), rd2 = random(1000000);
        set_name("Ảo Hóa Phù");
        set_picid_1(0210);
        set_picid_2(0210);
        set_value(100);
        set("aohoa", 4);
        set("backtype1", 8);
        set("backtype2", 8);
        set("backcolor1", rd);
        set("backcolor2", rd2);
}

// 函数：获取描述
string get_desc()
{
        return "Có thể thay đổi ngoại hình trang bị vai thành Vạn Ác Chi Dực - Vạn Sắc trong 14 ngày";
}
