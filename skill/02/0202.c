
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0202);
        set_name( "Chiêu Giá Chi Thuật" );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_dp(me); }

// 函数：获取描述
string get_desc() 
{
        return "［Chiêu Giá Chi Thuật］Tư thế phòng thủ căn bản, gia tăng 1 điểm Ngoại Kháng mỗi 1 cấp.\n";
}
