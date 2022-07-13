
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0355);
        set_name( "Cường Hóa Binh Pháp" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
//	USER_ENERGY_D->count_max_hp(me); 
	USER_ENERGY_D->count_pp(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "[Cường Hóa Binh Pháp] 禁卫军的特殊技能，可以掌握更多实战的技巧，并且能提升法术防御力，每级提升4点";
}
