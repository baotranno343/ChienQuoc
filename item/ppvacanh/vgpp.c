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
        set_name("Vương Giả Phi Phong");
        set_picid_1(3020);
        set_picid_2(3020);

        set_level(1);
		set_bind(1);
        set_value(1000);
		set_save("qsvst",1500);
        set_max_lasting(21599);
        set("ap", 300);
        set("pp", 300);
        set("hp", 800);
		set("mp", 800);
		set("double", 500);
		set_no_give(1);
		set_hide(0);
        setup();

        set_gender(1);
		set_back_type(1);
}

// 函数：获取描述
string get_desc()
{
        return "Một chiếc áo choàng thần bí kiêu hùng, mặc áo choàng này lên, sẽ hiện lên phong cách của Vương Giả.";
}
string get_tail_desc(object me)
{
	if (get("ap") == 1050)
	{
		return "【Đặc tính】 Khi bị tấn công nếu khí huyết bản thân thấp hơn 30% sẽ có tỷ lệ hồi phục một lượng khí huyết nhất định.";
	}
	else
	{
		return;
	}
}