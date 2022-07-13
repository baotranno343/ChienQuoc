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
        int rd = random(1000000);
        set_name("Ảo Hóa Phù");
        set_picid_1(0210);
        set_picid_2(0210);
        set_value(100);
        set("aohoa", 1);
        set("backtype1", 7);
        set("backtype2", 7);
        set("backcolor1", rd);
        set("backcolor2", rd);
}

// 函数：获取描述
string get_desc()
{
        return "Có thể thay đổi ngoại hình trang bị vai thành Thánh Linh Chi Dực - Đơn Sắc trong 14 ngày";
}
