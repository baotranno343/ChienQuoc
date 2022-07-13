
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0402);
        set_name( "Tụng Kinh" );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_cp(me); }

// 函数：获取描述
string get_desc() 
{
        return "［Tụng Kinh］Đọc kinh văn tụng kinh niệm phật đến mức trở thành Như Lai, mỗi cấp tăng 1 điểm Nội Công.\n";
}
