
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0335);
        set_name( "Cường Hoá Đao Kiếm Tâm Pháp" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
	USER_ENERGY_D->count_dp(me); 
	USER_ENERGY_D->count_hit_rate(me);
}

// 函数：获取描述
string get_desc() 
{
        return "［Cường Hoá Đao Kiếm Tâm Pháp］Gia tăng lực phòng ngự khi sử dụng đao và kiếm,mỗi cấp tăng 1.5 điểm.Gia tăng bạo kích,mỗi cấp tăng 0.08％";
}
