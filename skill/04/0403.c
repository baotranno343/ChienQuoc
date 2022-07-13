
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0403);
        set_name( "Thiền Định" );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_pp(me); }

// 函数：获取描述
string get_desc() 
{
        return "［Thiền Định］Phương pháp tu luyện tinh thần, mỗi cấp gia tăng 1 điểm Nội Kháng.\n";
}
