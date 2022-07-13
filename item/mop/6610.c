
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("勇敢者之冠");
        set_picid_1(6610);
        set_picid_2(6610);
	
        set_level(0);
        set_value(1);
        set_max_lasting(1099);
        set("dp", 10);
        set("pp", 0);
	set_no_give(1);
        setup();

        set_gender(2);
        set_head_code(50);
}

// 函数：获取描述
string get_desc()
{
        return "供勇敢者使用，无等级限制、无门派限制。";
}
