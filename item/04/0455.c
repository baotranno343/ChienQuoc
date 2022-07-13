inherit ITEM;
inherit COMBINED;

int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name("装着坏小猴的神奇葫芦");
        set_picid_1(4271);
        set_picid_2(4271);
	set_amount(1);
        set_value(50);
}

// 函数：获取描述
string get_desc() 
{ 
        return "神奇的葫芦，\n里面装着妄图偷抢西瓜的坏小猴，\n将它交给西瓜伯伯教训吧。"; 
}
