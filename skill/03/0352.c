
inherit SKILL;
//强化技能标志
int is_enhance_skill() {return 1;}

// 函数：构造处理
void create() 
{ 
        set_number(0352);
        set_name( "Cường Hóa Phong Ma Côn Pháp" );
}

// 函数：重计属性
void recount_char( object me ) 
{ 
//	USER_ENERGY_D->count_max_hp(me); 
	USER_ENERGY_D->count_hit_rate(me); 
}

// 函数：获取描述
string get_desc() 
{
        return "[Cường Hóa Phong Ma Côn Pháp] 提高使用棍法攻击的命中，每级提升3点命中";
}
