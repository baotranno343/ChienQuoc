
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0445);
        set_name( "Cường Hoá Đại Thừa Đao Pháp" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
	USER_ENERGY_D->count_max_hp(me); 
	USER_ENERGY_D->count_max_mp(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "［Cường Hoá Đại Thừa Đao Pháp］Gia tăng Pháp Lực mỗi cấp 6 điểm. Gia tăng Khí Huyết mỗi cấp 1.5 điểm.";
}
