#include <equip.h>
#include <ansi.h>
inherit USABLE;
inherit ITEM;

int is_key() {return 1;}

int get_item_value() {return 10 ;}
int get_item_value_2() {return 10 ;}
int get_item_color() {return 2 ;}

// 函数：构造处理
void create()
{
        set_name("Chìa Khóa Thanh Đồng");
        set_picid_1(6703);
        set_picid_2(6703);
        set_level(2);
        set_value(50);
		set_save("knb",20);
}

// 函数：获取描述
string get_desc()
{
        return "Thiên hạ đồn rằng Chu Vương cất giữ kho tàng trong các bảo hộp. \n Nhấn chuột phải để phóng lớn rương, kéo chìa khóa thả vào là có thể mở "HIR"Thanh Đồng Bảo Hộp "NOR"rồi.";
}
