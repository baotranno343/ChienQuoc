
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0384);
        set_name( "Cường Hoá Lạc Tuyết Vô Ngân" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
	USER_ENERGY_D->count_max_hp(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "［Cường Hoá Lạc Tuyết Vô Ngân］Gia tăng Khí Huyết, mỗi cấp tăng lên 3 điểm.";
}
