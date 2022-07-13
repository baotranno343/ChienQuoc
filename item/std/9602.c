
#include <equip.h>
#include <effect.h>

inherit TALISMAN;

// 函数：法宝识别
int get_talisman_type() { return 13; }

int get_item_color() { return 2; }

int get_gender() { return 1; }

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name( "Long Trạc" );
        set_picid_1(100);
        set_picid_2(100);
        set_unit( "个" );

        set_level(1);
        set_value(50);
        set_max_lasting(25099);

        setup();
	set_no_give(1);
	set_no_sell(1);
	set_no_get(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Vòng tay duyên phận, tương truyền chỉ cần cùng người chơi đeo vòng tay phượng hoàng ,\n Khí huyết ma pháp hồi phục 2 bên sẽ tăng 10%";
}
