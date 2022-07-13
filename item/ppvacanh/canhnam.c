#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <time.h>
#include <equip.h>
inherit "/inh/equip/back";
int get_item_color() { return 2; }
int get_item_value() {return 1000 ;}
int get_item_value_2() {return 1000 ;}
int is_nangcap() {return 1;}
inherit BACK;
// 函数：构造处理
void create()
{
        set_name("Thánh Linh Chi Dực·Vàng Nhạt");
        set_picid_1(3031);
        set_picid_2(3031);

        set_level(1);
		set_bind(1);
        set_value(1000);
		set_save("qsvst",1500);
        set_max_lasting(21599);
        set("cp", 300);
        set("dp", 300);
        set("hp", 800);
		set("mp", 800);
		set("sp", 100);
        set_no_give(1);

        setup();

        set_gender(1);
        set_back_type(7);
		set_back2_type(7);
		set_back_color(0xdf0c);
		set_back2_color(0xdf0c);
}

// 函数：获取描述
string get_desc()
{
        return "Thánh vật của sứ giả Quang Minh, dùng để ngăn cản lực lượng tà ác uy hiếp.";
}
string get_tail_desc(object me)
{
	if (get("cp") == 1050)
	{
		return "【Đặc tính】 Khi bị tấn công nếu khí huyết bản thân thấp hơn 30% sẽ có tỷ lệ hồi phục một lượng khí huyết nhất định.";
	}
	else
	{
		return;
	}
}