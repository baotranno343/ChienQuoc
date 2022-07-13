inherit ITEM;
inherit COMBINED;

int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name("西瓜伯伯的西瓜");
        set_picid_1(3280);
        set_picid_2(3280);
        set_amount(1);
        set_value(50);
}

void reset()
{
        if( gone_time( get_drop_time() ) > 6000 )    // 100分钟
        {
                remove_from_scene();
                destruct( this_object() );
        }
}

// 函数：获取描述
string get_desc() 
{ 
        return "又香又甜的大西瓜，\n不过可不准吃哦，\n这是西瓜伯伯辛苦种植的。"; 
}
