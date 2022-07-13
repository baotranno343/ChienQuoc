
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0252);
        set_name( "Côn Pháp Cách Đương" );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_dp(me); }

// 函数：获取描述
string get_desc() 
{
        return "［Côn Pháp Cách Đương］Gia tăng lực phòng ngự khi sử dụng côn mỗi cấp 0.8 điểm.\n";
}
