
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0401);
        set_name( "Đạo Gia Học Thuyết" );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_max_mp(me); }

// 函数：获取描述
string get_desc() 
{
        return "［Đạo Gia Học Thuyết］Ẩn chứa triết lý học thuyết, gia tăng Pháp Lực cao nhất 5 điểm mỗi cấp.\n";
}
